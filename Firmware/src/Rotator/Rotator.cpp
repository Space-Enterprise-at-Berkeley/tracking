#include "Rotator.h"
#include "EEPROM.h"
#include "HAL.h"
#include <cmath>

using Eigen::Vector;

namespace Rotator {
    // State flags
    bool diagnostic = false;

    // Motor state
    float elvPos, elvVel, elvError, elvPower, aziPos, aziVel, aziError, aziPower;
    float elvIntegral = 0;
    float aziIntegral = 0;
    
    // Reference setpoints
    float elvRefPos, elvRefVel, aziRefPos, aziRefVel;
    float aziOffset = 0;

    // Dynamics constants
    uint32_t updatePeriod = 5 * 1000; // microseconds
    float elvKp = 0.003;
    float elvKi = 0.0003; //0.0005;
    float elvKd = 0; //0.0006;
    float elvMaxPower = 0.1;
    float aziKp = 0.003;
    float aziKi = 0; //0.001;
    float aziMaxPower = 0.1;

    // Tracking stuff
    float rotatorPosition[] = {-860.651, -167.334, -18.1722}; // XYZ (ENU) position (m) relative to launch site

    // Diagnostic stuff
    uint8_t diagnosticStep = 0;
    float elvSequence[] = {30, 60, 90, 120, 150, 30, 30,  30, 30,  30,   30, 30, 90, 150, 30};
    float aziSequence[] = {0,   0,  0,   0,   0,  0, 90, 180, 45, -90, -150,  0, 80, -80,  0};
    uint32_t lastDiagnosticTime;
    uint32_t diagnosticDelay = 1500 * 1000;

    // Timing for data rate reporting
    uint32_t lastGPSUpdate = 0;
    uint32_t lastGPSDelay = 0;
    uint32_t lastAccUpdate = 0;
    uint32_t lastAccDelay = 0;

    void gpsToECEF(float gps[], float ecef[]) {
        const float a = 6378137.0f;           // WGS84 semi-major axis
        const float e2 = 6.69437999014e-3f;   // first eccentricity squared
        const float deg2rad = M_PI / 180.0f;

        float latRad = gps[0] * deg2rad;
        float lonRad = gps[1] * deg2rad;
        float alt = gps[2];

        float N = a / sqrtf(1.0f - e2 * sinf(latRad) * sinf(latRad));
        ecef[0] = (N + alt) * cosf(latRad) * cosf(lonRad);
        ecef[1] = (N + alt) * cosf(latRad) * sinf(lonRad);
        ecef[2] = (N * (1.0f - e2) + alt) * sinf(latRad);
    }

    // Compute local ENU separation between two GPS coordinates
    // gps1 = target point (lat, lon, alt)
    // gps2 = reference point (lat, lon, alt)
    // enu[3] = output {East, North, Up} in meters
    void gpsSeparationENU(float gps1[], float gps2[], float out[]) {
        float rocketpos[3];
        gpsToECEF(gps1, rocketpos);
        float launchpos[3];
        gpsToECEF(gps2, launchpos);

        float dx = rocketpos[0] - launchpos[0];
        float dy = rocketpos[1] - launchpos[1];
        float dz = rocketpos[2] - launchpos[2];

        // Convert ECEF delta to ENU relative to gps2
        const float deg2rad = M_PI / 180.0f;
        float lat0 = gps2[0] * deg2rad;
        float lon0 = gps2[1] * deg2rad;

        float sinLat = sinf(lat0), cosLat = cosf(lat0);
        float sinLon = sinf(lon0), cosLon = cosf(lon0);

        out[0] = -sinLon * dx + cosLon * dy;                      // East
        out[1] = -sinLat * cosLon * dx - sinLat * sinLon * dy + cosLat * dz; // North
        out[2] =  cosLat * cosLon * dx + cosLat * sinLon * dy + sinLat * dz; // Up
    }
    
    void trackingUpdate(){
        Vector<float, 9> trackingState = Tracking::getState();

        float x_position = trackingState(0);
        float x_velocity = trackingState(1);
        float y_position = trackingState(3);
        float y_velocity = trackingState(4);
        float z_position = trackingState(6);
        float z_velocity = trackingState(7);
        
        float x_rotator = rotatorPosition[0];
        float y_rotator = rotatorPosition[1];
        float z_rotator = rotatorPosition[2];
        
        float delta_x = x_position-x_rotator;
        float delta_y = y_position-y_rotator;
        float delta_z = z_position-z_rotator;

        float distance_from_rocket = sqrt(pow(delta_x,2.0)+pow(delta_y,2.0));
        float total_distance_from_rocket = sqrt(pow(distance_from_rocket,2.0) + pow(delta_z,2.0));

        const float MIN_DISTANCE_THRESHOLD = 0.01;
        if (total_distance_from_rocket < MIN_DISTANCE_THRESHOLD) return;
        
        aziRefPos = 180/M_PI * atan2(delta_y,delta_x);
        elvRefPos = 180/M_PI * asin(delta_z/total_distance_from_rocket) - 3;

        aziRefPos = fmod(90 - aziRefPos, 360.0); //convert from -180 to 180 to 0 to 360
        // elvRefPos = 90 - elvRefPos;//convert from -90 to 90 to 0 to 180
        aziRefVel = -(y_velocity * delta_x - x_velocity * delta_y)/pow(distance_from_rocket,2.0);
        elvRefVel = (z_velocity * distance_from_rocket)/(pow(total_distance_from_rocket,2.0)) - delta_z * (delta_x * x_velocity + delta_y * y_velocity)/(pow(total_distance_from_rocket,2.0) * distance_from_rocket);

        aziRefVel *= 180/M_PI;
        elvRefVel *= 180/M_PI;
    }

    void startDiagnostic(){
        Serial.println("Starting diagnostic");
        diagnostic = true;
        diagnosticStep = 0;
        lastDiagnosticTime = micros();
    }

    void stopDiagnostic(){
        Serial.println("Stopping diagnostic");
        diagnostic = false;
    }

    void diagnosticUpdate(){
        // Check if enough time has passed to move to the next diagnostic position
        if ((micros() - lastDiagnosticTime) >= diagnosticDelay) {
            // Move to next diagnostic step
            if (diagnosticStep < sizeof(elvSequence)/sizeof(float)) {
                elvRefPos = elvSequence[diagnosticStep];
                aziRefPos = aziSequence[diagnosticStep];
                diagnosticStep++;
            } else {
                // End of sequence, stop diagnostic mode
                stopDiagnostic();
                return;
            }
            lastDiagnosticTime = micros();
        }
    }

    void setElvSetpoint(Comms::Packet packet, uint8_t ip){
        Tracking::stopTracking();
        stopDiagnostic();
        PacketRTSetElevation parsed_packet = PacketRTSetElevation::fromRawPacket(&packet);
        elvRefPos = parsed_packet.m_Degrees;
        Serial.print("Set elevation setpoint to ");
        Serial.println(elvRefPos);
    }

    void setAziSetpoint(Comms::Packet packet, uint8_t ip){
        Tracking::stopTracking();
        stopDiagnostic();
        PacketRTSetAzimuth parsed_packet = PacketRTSetAzimuth::fromRawPacket(&packet);
        aziRefPos = parsed_packet.m_Degrees;
        Serial.print("Set azimuth setpoint to ");
        Serial.println(aziRefPos);
    }

    void runDiagnostic(Comms::Packet packet, uint8_t ip){
        Serial.println("Beginning diagnostic");
        Tracking::stopTracking();
        startDiagnostic();
    }

    void switchTracking(Comms::Packet packet, uint8_t ip){
        stopDiagnostic();
        PacketRTEnableFlightTracking parsed_packet = PacketRTEnableFlightTracking::fromRawPacket(&packet);
        if (parsed_packet.m_Action) {
            Tracking::startTracking();
            Serial.println("Starting tracking");
        } else {
            Tracking::stopTracking();
            Serial.println("Stopping tracking");
        }
    }

    void zeroAzimuth(Comms::Packet packet, uint8_t ip){
        stopDiagnostic();
        Tracking::stopTracking();
        aziOffset = fmod(aziOffset + 360.0 - aziPos, 360.0);
        aziRefPos = 0;
        Serial.print("Set azimuth offset to ");
        Serial.println(aziOffset);
    }

    void sendRotatorState(){
        //PacketRTRotatorState newpacket = PacketRTRotatorState::writeRawPacket();
        //make packet
        uint32_t now = micros();
        uint32_t sinceAcc = now - lastAccUpdate;
        uint32_t sinceGPS = now - lastGPSUpdate;
        float accRate;
        float gpsRate;

        if (lastAccDelay == 0 || sinceAcc > 5000*1000){
            accRate = 0;
        } else {
            if (sinceAcc > lastAccDelay) lastAccDelay = sinceAcc;
            accRate = 1.0/lastAccDelay*1000*1000;
        }
        if (lastGPSDelay == 0 || sinceGPS > 5000*1000){
            gpsRate = 0;
        } else {
            if (sinceGPS > lastGPSDelay) lastGPSDelay = sinceGPS;
            gpsRate = 1.0/lastGPSDelay*1000*1000;
        }

        PacketRTRotatorState state = PacketRTRotatorState::Builder()
            .withElvPos(elvPos)
            .withElvRefPos(elvRefPos)
            .withElvVel(elvVel)
            .withElvRefVel(elvRefVel)
            .withElvPower(elvPower*100)
            .withAziPos(aziPos)
            .withAziRefPos(aziRefPos)
            .withAziVel(aziVel)
            .withAziRefVel(aziRefVel)
            .withAziPower(aziPower*100)
            .withEnableState(HAL::getMotorEnable())
            .withElvEncoderFault(HAL::getFault_0())
            .withAziEncoderFault(HAL::getFault_1())
            .withLaunchDetectState(Tracking::getApogeeReached())
            .withGpsRate(gpsRate)
            .withAccelRate(accRate)
            .build();
        Comms::Packet newpacket;
        state.writeRawPacket(&newpacket);
        //emit packet 
        Comms::emitPacketToGS(&newpacket);
        /*float rotatorState[] = {elvRefPos, aziRefPos};
        for (int i = 0; i < 2; i++) {
            Serial.print(rotatorState[i]);
            Serial.print(" ");
        }
        Serial.println();*/
    }
    
    // if we are at 330, and we want to go to 0, there are two options: go forward 30 degrees, or backward 330 degrees
    // this function checks which option is shorter, and returns the target angle adjusted for wraparound
    float check_wraparound(float target_angle, float current_angle) {
        float error = target_angle - current_angle; // forward error
        
        if (error > 180) {
            return error - 360;
        } else if (error < -180) {
            return error + 360;
        } else {
            return error;
        }
    }

    inline float deadband(float in, float size){
        if (in > 0) return in > size ? in - size : 0;
        else return in < -size ? in + size : 0;
    }

    float PIDController(float error, float vel, float Kp, float Ki, float Kd, float maxPower, float &integral){
        float power = Kp * error + integral - Kd * vel;
        float clipped = max(min(power, maxPower), -maxPower);
        float antiwindup = (clipped - power) / Kp;
        integral += (error + antiwindup) * Ki * (float) updatePeriod / (1000 * 1000);
        if (!HAL::getMotorEnable()) integral = 0;
        return clipped;
    }

    void init(){
        diagnostic = false;

        Comms::registerCallback(PACKET_ID_RTSetElevation, setElvSetpoint);
        Comms::registerCallback(PACKET_ID_RTSetAzimuth, setAziSetpoint);
        Comms::registerCallback(PACKET_ID_RTRunDiagnostic, runDiagnostic);
        Comms::registerCallback(PACKET_ID_RTEnableFlightTracking, switchTracking);
        Comms::registerCallback(PACKET_ID_RTZeroAzimuth, zeroAzimuth);
        Comms::registerCallback(PACKET_ID_LowIMUValues, Tracking::accelUpdate);
        Comms::registerCallback(PACKET_ID_GPSValues, Tracking::GPSUpdate);
        Comms::registerCallback(PACKET_ID_BaroValues, Tracking::baroUpdate);
    }

    uint32_t updateAndMove(){
        if (Tracking::getEnable()) { // tracking mode
            trackingUpdate();
        } else if (diagnostic) { // diagnostic mode
            diagnosticUpdate();
        } else { // idle mode
            elvRefVel = 0;
            aziRefVel = 0;
        }

        elvRefPos = max(min(elvRefPos, HAL::maxDegrees_0), HAL::minDegrees_0);       
        elvPos = HAL::getEncoderDegrees_0();
        elvVel = HAL::getSlope_0() * 1000 * 1000;

        elvError = elvRefPos - elvPos;
        elvPower = PIDController(elvError, deadband(elvVel, 3), elvKp, elvKi, elvKd, elvMaxPower, elvIntegral) + 0.06*cos(elvPos*PI/180.0);
        elvPower = min(max(elvPower, -elvMaxPower), elvMaxPower);
        HAL::sendPower_0(elvPower); 
        
        aziRefPos = fmod(aziRefPos, 360.0);
        if (aziRefPos < 0) aziRefPos += 360; 
        aziPos = fmod(HAL::getEncoderDegrees_1() + aziOffset, 360.0);
        aziVel = HAL::getSlope_1() * 1000 * 1000;

        aziError = check_wraparound(aziRefPos, aziPos);
        aziPower = PIDController(aziError, 0, aziKp, aziKi, 0, aziMaxPower, aziIntegral); // Just PI (no D) bc I barely need I and also wraparound derivative
        HAL::sendPower_1(aziPower);

        /*Serial.print("Elv power: ");
        Serial.print(elvPower, 5);
        Serial.print(" Azi power: ");
        Serial.println(aziPower, 5);*/

        /*lastMotorTime = micros();
        elvLastPos = elvPos;
        aziLastPos = aziPos;*/

        sendRotatorState();

        return updatePeriod;
    }

    /*bool *getStateFlags(){
        bool flags[] = {tracking, diagnostic};
        return flags;
    }*/
}