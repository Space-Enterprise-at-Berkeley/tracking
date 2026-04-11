#include "Tracking.h"
#include <cmath>

namespace Tracking {
    // Main state
    std::array<float, 9> trackingState; // Xpos, Xvel, Xaccel, Ypos, ...
    bool tracking = false;
    
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

    
    float dt = 0.1;

    void resetTracking(){
        tracking = true;
        trackingState = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Xpos, Xvel, Xaccel, Ypos, ...

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
        launchAcceleration[0] /= accelCalSamples;
        launchAcceleration[1] /= accelCalSamples;
        launchAcceleration[2] /= accelCalSamples;
        launchGyro[0] /= accelCalSamples;
        launchGyro[1] /= accelCalSamples;
        launchGyro[2] /= accelCalSamples;

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

        float ax_world = rotated.x - 9.80655;
        float ay_world = rotated.y;
        float az_world = rotated.z;

        //Kalman filter update here!!!!
        //simple integration to get velocity and position
        trackingState[7] += ax_world * dt; //since x is actually upward
        trackingState[4] += ay_world * dt; 
        trackingState[1] += az_world * dt; //since z is actually forward
        trackingState[0] += trackingState[1] * dt;
        trackingState[3] += trackingState[4] * dt;
        trackingState[6] += trackingState[7] * dt;

        if(trackingState[6] > apoAltThresh && trackingState[7] < apoVelThresh){ //if vertical velocity is negative for some time, we have reached apogee
            apogeeReached = true;
        }
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
        trackingState[0] = enu[0];
        trackingState[3] = enu[1];
        trackingState[6] = enu[2];
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
        return false; //data not validated
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
}