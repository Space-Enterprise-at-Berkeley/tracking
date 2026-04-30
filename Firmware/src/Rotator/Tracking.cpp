#include "Tracking.h"
#include <cmath>

namespace Tracking {
    // Main state
    uint32_t trackingStartTime;
    bool enable = false;
    
    // Accelerometer variables
    uint8_t accelCalSamples = 0;
    uint8_t accelCalThreshold = 30;
    uint8_t accelDataRateTotalSamples = 0;
    uint8_t accelDataRateValidSamples = 0;
    float accelAcceptanceRate = 0;
    uint32_t lastAccelDataTime = micros();
    std::array<float, 3> launchAcceleration;
    std::array<float, 3> launchGyro;
    float apoAltThresh = 100;
    float apoVelThresh = 5;
    bool apogeeReached = false;
    Quaternion::quat q = {sqrt(2.0F)/2, 0, sqrt(2.0F)/2, 0};
    uint32_t lastAccelTime = micros();

    // GPS variables
    uint8_t GPSCalSamples = 0;
    uint8_t GPSCalThreshold = 10;
    uint8_t gpsDataRateTotalSamples = 0;
    uint8_t gpsDataRateValidSamples = 0;
    uint32_t lastGPSDataTime = micros();
    float gpsAcceptanceRate = 0;
    std::array<float, 3> launchPosition;


    // Baro variables
    uint8_t baroCalSamples = 0;
    uint8_t baroDataRateTotalSamples = 0;
    uint8_t baroDataRateValidSamples = 0;
    uint32_t lastBaroDataTime = micros();
    uint8_t baroCalThreshold = 20;
    float baroAcceptanceRate = 0;
    float launchPressure;
    float launchAltitude;

    void startTracking(){
        enable = true;
        trackingStartTime = micros();
        KalmanFilter::reset();

        //calibration samples reset
        accelCalSamples = 0;
        launchAcceleration = {0, 0, 0};
        launchGyro = {0, 0, 0};
        apogeeReached = false;
        q = {sqrt(2.0F)/2, 0, -sqrt(2.0F)/2, 0};
        lastAccelTime = micros();

        GPSCalSamples = 0;
        launchPosition = {0, 0, 0};

        baroCalSamples = 0;
        launchPressure = 0;
        launchAltitude = 0;
    }
    
    void stopTracking(){
        enable = false;
    }

    bool getEnable(){
        return enable;
    }

    inline float filterTime(){
        return ((float) (micros() - trackingStartTime)) / (1000 * 1000); 
    }

    void accelUpdate(Comms::Packet packet, uint8_t ip){
        
        uint32_t now = micros();
        uint32_t dt_micro = now - lastAccelTime;
        lastAccelTime = now;
        if(!enable) return;
        if(apogeeReached) return;// false;

        Serial.print("Recieved accel packet: ");
        Serial.println(accelCalSamples);

        // Insert accel callback here
        PacketLowIMUValues parsed_packet = PacketLowIMUValues::fromRawPacket(&packet);

        float accelZ = parsed_packet.m_AccelZ;
        float accelY = parsed_packet.m_AccelY;
        float accelX = parsed_packet.m_AccelX; 

        float gyroX = parsed_packet.m_GyroX;
        float gyroY = parsed_packet.m_GyroY;
        float gyroZ = parsed_packet.m_GyroZ;
        accelDataRateTotalSamples++;
        if(accelCalSamples < accelCalThreshold){
            accelCalSamples ++;
            // Do initial averaging
            launchAcceleration[0] = (launchAcceleration[0] * (accelCalSamples-1) + accelX) / accelCalSamples;
            launchAcceleration[1] = (launchAcceleration[1] * (accelCalSamples-1) + accelY) / accelCalSamples;
            launchAcceleration[2] = (launchAcceleration[2] * (accelCalSamples-1) + accelZ) / accelCalSamples;
            launchGyro[0] = (launchGyro[0] * (accelCalSamples-1) + gyroX) / accelCalSamples;
            launchGyro[1] = (launchGyro[1] * (accelCalSamples-1) + gyroY) / accelCalSamples;
            launchGyro[2] = (launchGyro[2] * (accelCalSamples-1) + gyroZ) / accelCalSamples;

            return;// false; //data validated, and we have set our launch acceleration and gyro
        }
        

        if(accelCalSamples == accelCalThreshold) {
            Serial.print("Calibrated accel with ");
            Serial.print(launchAcceleration[0]);
            Serial.print(" ");
            Serial.print(launchAcceleration[1]);
            Serial.print(" ");
            Serial.print(launchAcceleration[2]);
            Serial.print(" ");
            Serial.print(launchGyro[0]);
            Serial.print(" ");
            Serial.print(launchGyro[1]);
            Serial.print(" ");
            Serial.println(launchGyro[2]);
            accelCalSamples++;
        }
        

        //reduce biases from launch accel and gyro
        accelX = (accelX - (launchAcceleration[0] - 1)) * 9.80655F; 
        accelY = (accelY - launchAcceleration[1]) * 9.80655F;
        accelZ = (accelZ - launchAcceleration[2]) * 9.80655F;
        gyroX = (gyroX - launchGyro[0])*(PI/180);
        gyroY = (gyroY - launchGyro[1])*(PI/180);
        gyroZ = (gyroZ - launchGyro[2])*(PI/180);

        Serial.print("accel/gyro XYZ: ");
        Serial.print(accelX);
        Serial.print(" ");
        Serial.print(accelY);
        Serial.print(" ");
        Serial.print(accelZ);
        Serial.print(" ");
        Serial.print(gyroX);
        Serial.print(" ");
        Serial.print(gyroY);
        Serial.print(" ");
        Serial.println(gyroZ);

        Quaternion::quat qDot;
        qDot.w = 0.5 * (-q.x * gyroX - q.y * gyroY - q.z * gyroZ);
        qDot.x = 0.5 * (q.w * gyroX + q.y * gyroZ - q.z * gyroY);
        qDot.y = 0.5 * (q.w * gyroY - q.x * gyroZ + q.z * gyroX);
        qDot.z = 0.5 * (q.w * gyroZ + q.x * gyroY - q.y * gyroX);

        float dt = ((float) dt_micro) / (1000 * 1000);
        q.w += qDot.w * dt;
        q.x += qDot.x * dt;
        q.y += qDot.y * dt;
        q.z += qDot.z * dt;

        q = Quaternion::normalize(q);

        Serial.print("Quaternion: ");
        Serial.print(q.w);
        Serial.print(" ");
        Serial.print(q.x);
        Serial.print(" ");
        Serial.print(q.y);
        Serial.print(" ");
        Serial.println(q.z);

        Quaternion::quat accelQuat = {0, accelX, accelY, accelZ};
        Quaternion::quat qConj = Quaternion::conjugate(q);
        // rotated = q * accel * q^-1
        Quaternion::quat temp = Quaternion::multiply(q, accelQuat);
        Quaternion::quat rotated = Quaternion::multiply(temp, qConj);

        Vector<float, 3> a_world = {rotated.x, rotated.y, rotated.z - 9.80655F};

        Serial.print("Rotated: ");
        Serial.print(rotated.x);
        Serial.print(" ");
        Serial.print(rotated.y);
        Serial.print(" ");
        Serial.println(a_world[2]);

        KalmanFilter::accelUpdate(filterTime(), a_world);

        Serial.print("Ran accel update with ");
        Serial.print(a_world[0]);
        Serial.print(" ");
        Serial.print(a_world[1]);
        Serial.print(" ");
        Serial.println(a_world[2]);

       accelDataRateValidSamples++;

        return;// true; //data validated
    }

    void GPSUpdate(Comms::Packet packet, uint8_t ip){
        // false;
        if (!enable) return;
        Serial.print("Recieved GPS packet: ");
        Serial.println(GPSCalSamples);

        // Insert GPS callback here
        PacketGPSValues parsed_packet = PacketGPSValues::fromRawPacket(&packet);
        float lat = parsed_packet.m_Latitude;
        float lon = parsed_packet.m_Longitude;
        float alt = parsed_packet.m_Altitude;
        uint8_t siv = parsed_packet.m_Siv;
        gpsDataRateTotalSamples++;
        Serial.print(siv);
        if (siv < 10) return;// false;

        if(GPSCalSamples < GPSCalThreshold){
            GPSCalSamples++;
            //average = last * (n-1)/n + new * 1/n
            launchPosition[0] = (launchPosition[0] * (GPSCalSamples - 1) + lat) / GPSCalSamples;
            launchPosition[1] = (launchPosition[1] * (GPSCalSamples - 1) + lon) / GPSCalSamples;
            launchPosition[2] = (launchPosition[2] * (GPSCalSamples - 1) + alt) / GPSCalSamples;
            return;// false; //calibration
        }
        if(GPSCalSamples == GPSCalThreshold) {
            Serial.print("Calibrated GPS with ");
            Serial.print(launchPosition[0]);
            Serial.print(" ");
            Serial.print(launchPosition[1]);
            Serial.print(" ");
            Serial.println(launchPosition[2]);
            GPSCalSamples++;
        }
        

        std::array<float, 3> rocketPosition = {lat,lon,alt};
        std::array<float, 3> enu = gpsSeparationENU(rocketPosition, launchPosition);
        //Update the tracker with the new position
        //Something something Kalman Filter here
        Vector<float, 3> gpsPos = {enu[0], enu[1], enu[2]};
        KalmanFilter::GPSUpdate(filterTime(), gpsPos);

        Serial.print("Ran GPS update with ");
        Serial.print(enu[0]);
        Serial.print(" ");
        Serial.print(enu[1]);
        Serial.print(" ");
        Serial.println(enu[2]);

        gpsDataRateValidSamples++;
        return;// true; //data validated
    }

    void baroUpdate(Comms::Packet packet, uint8_t ip){
        // false;
        if (!enable) return;
        Serial.println("Recieved baro packet: ");
        Serial.println(baroCalSamples);

        // Insert baro callback here
        PacketBaroValues parsed_packet = PacketBaroValues::fromRawPacket(&packet);
        float altitude = parsed_packet.m_Altitude;
        float pressure = parsed_packet.m_Pressure;
        baroDataRateTotalSamples++;
        if(baroCalSamples < baroCalThreshold){
            baroCalSamples++;
            launchPressure = (launchPressure * (baroCalSamples - 1) + pressure) / baroCalSamples;
            launchAltitude = (launchAltitude * (baroCalSamples - 1) + altitude) / baroCalSamples;
            return;// false;
        }
        
        
        if(baroCalSamples == baroCalThreshold) {
            Serial.print("Calibrated baro with ");
            Serial.print(launchAltitude);
            baroCalSamples++;
        }

        //if barometer altitude doesn't differ by a huge amount according to our last update
        /*if(std::abs(altitude - trackingState[6]) < 500){
            if(trackingState[6] == 0.0 && trackingState[0] == 0.0 && trackingState[3] == 0.0){
                //if GPS is bad, use the barometer to estimate vertical position
                //Kalman filter here!!!!
                trackingState[6] = altitude - launchAltitude;
                return true;
                //data validated, but we are using barometer data instead of GPS, so we only update the Z position
            }
        }*/
        // TODO: better sanity check
        KalmanFilter::baroUpdate(filterTime(), altitude - launchAltitude);

        Serial.print("Ran baro update with ");
        Serial.print(altitude - launchAltitude);
        baroDataRateValidSamples++;
        return;
    }

    uint32_t maintenance() {
        if (enable) {
            Vector<float, 9> state = KalmanFilter::predict(filterTime());
            if(state(6) > apoAltThresh && state(7) < apoVelThresh){ //if vertical velocity is negative for some time, we have reached apogee
                apogeeReached = true;
            } 
        }

        return 1000 * 1000;
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

    void sendTrackingState(Vector<float, 9> trackingState){
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

uint32_t sendDataAcceptState(){
        PacketRTDataAcceptState state = PacketRTDataAcceptState::Builder()
            .withGPSAcceptRate(gpsDataRateTotalSamples != 0 ? (float)gpsDataRateValidSamples/gpsDataRateTotalSamples : 0.0f)
            .withAccelAcceptRate(accelDataRateTotalSamples != 0 ? (float)accelDataRateValidSamples/accelDataRateTotalSamples : 0.0f)
            .withBaroAcceptRate(baroDataRateTotalSamples != 0 ? (float)baroDataRateValidSamples/baroDataRateTotalSamples : 0.0f)
            .withGPSRate(gpsDataRateTotalSamples)
            .withAccelRate(accelDataRateTotalSamples)
            .withBaroRate(baroDataRateTotalSamples)
            .build();
        Comms::Packet newpacket;
        state.writeRawPacket(&newpacket);
        //emit packet 
        Comms::emitPacketToGS(&newpacket);
        gpsDataRateTotalSamples = 0;
        gpsDataRateValidSamples = 0;
        accelDataRateTotalSamples = 0;
        accelDataRateValidSamples = 0;
        baroDataRateTotalSamples = 0;
        baroDataRateValidSamples = 0;
        return 1000 * 1000;
    }

    Vector<float, 9> getState(){
        Vector<float, 9> trackingState = KalmanFilter::extrapolate(filterTime());
        sendTrackingState(trackingState);
        return trackingState;
    }
}