#include "Tracking.h"
#include <cmath>

namespace Tracking {
    // Main state
    bool tracking = false;
    uint32_t trackingStartTime;
    Vector <float, 9> trackingState;
    
    // Accelerometer variables
    uint8_t accelCalSamples = 0;
    uint8_t accelCalThreshold = 30;
    std::array<float, 3> launchAcceleration;
    std::array<float, 3> launchGyro;
    float apoAltThresh = 100;
    float apoVelThresh = 5;
    bool apogeeReached = false;
    Quaternion::quat q = {1, 0, 0, 0};   

    // GPS variables
    uint8_t GPSCalSamples = 0;
    uint8_t GPSCalThreshold = 10;
    std::array<float, 3> launchPosition;

    // Baro variables
    uint8_t baroCalSamples = 0;
    uint8_t baroCalThreshold = 20;
    float launchPressure;
    float launchAltitude;

    float elvPos, elvVel, elvError, elvPower, aziPos, aziVel, aziError, aziPower;
    float elvIntegral = 0;
    float aziIntegral = 0;
    
    // Reference setpoints
    float elvRefPos, elvRefVel, aziRefPos, aziRefVel;
    float aziOffset = 0;
    
    float dt = 0.1;

    void startTracking(){
        tracking = true;
        trackingStartTime = micros();
        trackingState = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        KalmanFilter::init();

        //calibration samples reset
        accelCalSamples = 0;
        launchAcceleration = {0, 0, 0};
        launchGyro = {0, 0, 0};
        apogeeReached = false;
        q = {1, 0, 0, 0};

        GPSCalSamples = 0;
        launchPosition = {0, 0, 0};

        baroCalSamples = 0;
        launchPressure = 0;
        launchAltitude = 0;
        
        // TODO: reset all calibration constants (check all of them)
        // Insert other preflight initialization (e.g. zeroing baro) here
    }
    
    void stopTracking(){
        tracking = false;
    }

    inline float filterTime(){
        return ((float) (micros() - trackingStartTime)) / (1000 * 1000); 
    }

    bool accelUpdate(Comms::Packet packet, uint8_t ip){
        if(!tracking || apogeeReached) return false;

        // Insert accel callback here
        PacketLowIMUValues parsed_packet = PacketLowIMUValues::fromRawPacket(&packet);

        float accelZ = parsed_packet.m_AccelZ;
        float accelY = parsed_packet.m_AccelY;
        float accelX = parsed_packet.m_AccelX; 

        float gyroX = parsed_packet.m_GyroX;
        float gyroY = parsed_packet.m_GyroY;
        float gyroZ = parsed_packet.m_GyroZ;

        if(accelCalSamples < accelCalThreshold){
            accelCalSamples ++;
            // Do initial averaging
            launchAcceleration[0] = (1/accelCalSamples)*(launchAcceleration[0] * (accelCalSamples-1) + accelX);
            launchAcceleration[1] = (1/accelCalSamples)*(launchAcceleration[1] * (accelCalSamples-1) + accelY);
            launchAcceleration[2] = (1/accelCalSamples)*(launchAcceleration[2] * (accelCalSamples-1) + accelZ);
            launchGyro[0] = (1/accelCalSamples)*(launchGyro[0] * (accelCalSamples-1) + gyroX);
            launchGyro[1] = (1/accelCalSamples)*(launchGyro[1] * (accelCalSamples-1) + gyroY);
            launchGyro[2] = (1/accelCalSamples)*(launchGyro[2] * (accelCalSamples-1) + gyroZ);
            return false; //data validated, and we have set our launch acceleration and gyro
        }

        //reduce biases from launch accel and gyro
        accelX = (accelX - (launchAcceleration[0] - 1)) * 9.80655; 
        accelY = (accelY - launchAcceleration[1]) * 9.80655;
        accelZ = (accelZ - launchAcceleration[2]) * 9.80655;
        gyroX = (gyroX - launchGyro[0])*(PI/180);
        gyroY = (gyroY - launchGyro[1])*(PI/180);
        gyroZ = (gyroZ - launchGyro[2])*(PI/180);

        Quaternion::quat qDot;
        qDot.w = 0.5 * (-q.x * gyroX - q.y * gyroY - q.z * gyroZ);
        qDot.x = 0.5 * (q.w * gyroX + q.y * gyroZ - q.z * gyroY);
        qDot.y = 0.5 * (q.w * gyroY - q.x * gyroZ + q.z * gyroX);
        qDot.z = 0.5 * (q.w * gyroZ + q.x * gyroY - q.y * gyroX);

        q.w += qDot.w * dt;
        q.x += qDot.x * dt;
        q.y += qDot.y * dt;
        q.z += qDot.z * dt;

        q = Quaternion::normalize(q);

        Quaternion::quat accelQuat = {0, accelX, accelY, accelZ};
        Quaternion::quat qConj = Quaternion::conjugate(q);
        // rotated = q * accel * q^-1
        Quaternion::quat temp = Quaternion::multiply(q, accelQuat);
        Quaternion::quat rotated = Quaternion::multiply(temp, qConj);

        std::array<float, 3> a_world = {rotated.x - 9.80655, rotated.y, rotated.z};
        /*float ax_world = rotated.x - 9.80655;
        float ay_world = rotated.y;
        float az_world = rotated.z;*/

        KalmanFilter::accelUpdate(filterTime(), a_world);

        return true; //data validated
    }

    bool GPSUpdate(Comms::Packet packet, uint8_t ip){
        if (!tracking) return false;

        // Insert GPS callback here
        PacketGPSValues parsed_packet = PacketGPSValues::fromRawPacket(&packet);
        float lat = parsed_packet.m_Latitude;
        float lon = parsed_packet.m_Longitude;
        float alt = parsed_packet.m_Altitude;
        uint8_t siv = parsed_packet.m_Siv;

        if (siv < 10) return false;

        if(GPSCalSamples < GPSCalThreshold){
            GPSCalSamples++;
            //average = last * (n-1)/n + new * 1/n
            launchPosition[0] = (launchPosition[0] * (GPSCalSamples - 1) + lat) / GPSCalSamples;
            launchPosition[1] = (launchPosition[1] * (GPSCalSamples - 1) + lon) / GPSCalSamples;
            launchPosition[2] = (launchPosition[2] * (GPSCalSamples - 1) + alt) / GPSCalSamples;
            return false; //calibration
        }
        std::array<float, 3> rocketPosition = {lat,lon,alt};
        std::array<float, 3> enu = gpsSeparationENU(rocketPosition, launchPosition);
        //Update the tracker with the new position
        //Something something Kalman Filter here
        std::array<float, 3> gpsPos = {enu[0], enu[1], enu[2]};
        KalmanFilter::GPSUpdate(filterTime(), gpsPos);
        return true; //data validated
    }

    bool baroUpdate(Comms::Packet packet, uint8_t ip){
        if (!tracking) return false;

        // Insert baro callback here
        PacketBaroValues parsed_packet = PacketBaroValues::fromRawPacket(&packet);
        float altitude = parsed_packet.m_Altitude;
        float pressure = parsed_packet.m_Pressure;

        if(baroCalSamples < baroCalThreshold){
            baroCalSamples++;
            launchPressure = (launchPressure * (baroCalSamples - 1) + pressure) / baroCalSamples;
            launchAltitude = (launchAltitude * (baroCalSamples - 1) + altitude) / baroCalSamples;
            return false;
        }
        //if barometer altitude doesn't differ by a huge amount according to our last update
        if(std::abs(altitude - trackingState[6]) < 500){
            if(trackingState[6] == 0.0 && trackingState[0] == 0.0 && trackingState[3] == 0.0){
                //if GPS is bad, use the barometer to estimate vertical position
                //Kalman filter here!!!!
                trackingState[6] = altitude - launchAltitude;
                return true;
                //data validated, but we are using barometer data instead of GPS, so we only update the Z position
            }
        }
        KalmanFilter::GPSUpdate(filterTime(), {trackingState(0), trackingState(3), altitude - launchAltitude});
        return false; //data not validated
    }

    uint32_t maintenance() {
        if (tracking) {
            KalmanFilter::predict(filterTime());
            Vector<float, 9> state = KalmanFilter::extrapolate(filterTime());
            if(state(6) > apoAltThresh && state(7) < apoVelThresh){ //if vertical velocity is negative for some time, we have reached apogee
                apogeeReached = true;
            }
            
            
            
        }
        return 100 * 1000;
    }

    std::array<float, 3> gpsToECEF(std::array<float, 3> gps) {
        const float a = 6378137.0f;           // WGS84 semi-major axis
        const float e2 = 6.69437999014e-3f;   // first eccentricity squared
        const float deg2rad = M_PI / 180.0f;

        float latRad = gps[0] * deg2rad;
        float lonRad = gps[1] * deg2rad;
        float alt = gps[2];

        float N = a / sqrtf(1.0f - e2 * sinf(latRad) * sinf(latRad));
        std::array<float, 3> ecef;
        ecef[0] = (N + alt) * cosf(latRad) * cosf(lonRad);
        ecef[1] = (N + alt) * cosf(latRad) * sinf(lonRad);
        ecef[2] = (N * (1.0f - e2) + alt) * sinf(latRad);
        return ecef;
    }

    // Compute local ENU separation between two GPS coordinates
    // gps1 = target point (lat, lon, alt)
    // gps2 = reference point (lat, lon, alt)
    // enu[3] = output {East, North, Up} in meters
    std::array<float, 3> gpsSeparationENU(std::array<float, 3> gps1, std::array<float, 3> gps2) {
        std::array<float, 3> rocketpos = gpsToECEF(gps1);
        std::array<float, 3> launchpos = gpsToECEF(gps2);

        float dx = rocketpos[0] - launchpos[0];
        float dy = rocketpos[1] - launchpos[1];
        float dz = rocketpos[2] - launchpos[2];

        // Convert ECEF delta to ENU relative to gps2
        const float deg2rad = M_PI / 180.0f;
        float lat0 = gps2[0] * deg2rad;
        float lon0 = gps2[1] * deg2rad;

        float sinLat = sinf(lat0), cosLat = cosf(lat0);
        float sinLon = sinf(lon0), cosLon = cosf(lon0);
        
        std::array<float, 3> out;
        out[0] = -sinLon * dx + cosLon * dy;                      // East
        out[1] = -sinLat * cosLon * dx - sinLat * sinLon * dy + cosLat * dz; // North
        out[2] =  cosLat * cosLon * dx + cosLat * sinLon * dy + sinLat * dz; // Up
        return out;
    }
    void trackingUpdate(){
        float x_position = trackingState(0);
        float x_velocity = trackingState(1);
        float y_position = trackingState(3);
        float y_velocity = trackingState(4);
        float z_position = trackingState(6);
        float z_velocity = trackingState(7);
        
        float x_rotator = launchPosition[0];
        float y_rotator = launchPosition[1];
        float z_rotator = launchPosition[2];
        
        float delta_x = x_position-x_rotator;
        float delta_y = y_position-y_rotator;
        float delta_z = z_position-z_rotator;

        float distance_from_rocket = sqrt(pow(delta_x,2.0)+pow(delta_y,2.0));
        float total_distance_from_rocket = sqrt(pow(distance_from_rocket,2.0) + pow(delta_z,2.0));

        const float MIN_DISTANCE_THRESHOLD = 0.01;
        if (total_distance_from_rocket < MIN_DISTANCE_THRESHOLD) return;
        
        aziRefPos = 180/M_PI * atan2(delta_y,delta_x);
        elvRefPos = 180/M_PI * asin(delta_z/total_distance_from_rocket);

        aziRefPos = fmod(90 - aziRefPos, 360.0); //convert from -180 to 180 to 0 to 360
        // elvRefPos = 90 - elvRefPos;//convert from -90 to 90 to 0 to 180
        aziRefVel = -(y_velocity * delta_x - x_velocity * delta_y)/pow(distance_from_rocket,2.0);
        elvRefVel = (z_velocity * distance_from_rocket)/(pow(total_distance_from_rocket,2.0)) - delta_z * (delta_x * x_velocity + delta_y * y_velocity)/(pow(total_distance_from_rocket,2.0) * distance_from_rocket);

        aziRefVel *= 180/M_PI;
        elvRefVel *= 180/M_PI;
    }     

    void sendTrackingState(){
        PacketRTFlightTracking state = PacketRTFlightTracking::Builder()
            .withXPos(trackingState(0))
            .withXVel(trackingState(1))
            .withXAccel(trackingState(2))
            .withYPos(trackingState(3))
            .withYVel(trackingState(4))
            .withYAccel(trackingState(5))
            .withZPos(trackingState(6))
            .withZVel(trackingState(7))
            .withZAccel(trackingState(8))
            .build();
        Comms::Packet newpacket;
        state.writeRawPacket(&newpacket);
        //emit packet 
        Comms::emitPacketToGS(&newpacket);
    }
}