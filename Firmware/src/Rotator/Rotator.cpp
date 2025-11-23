#include "Rotator.h"
#include "EEPROM.h"
#include "HAL.h"
#include <FlexCAN_T4.h>
#include <cmath>
#include <math.h>
#include <array>

namespace Rotator {
    // State flags
    bool tracking = false;
    bool diagnostic = false;

    // Motor state
    float elvPos, elvVel, elvError, elvPower, aziPos, aziVel, aziError, aziPower;
    
    // Reference setpoints
    float elvRefPos, elvRefVel, aziRefPos, aziRefVel;

    // Dynamics constants
    uint32_t updatePeriod = 5 * 1000; // microseconds
    float elvKp = 0.005;
    float elvKd = 0;
    float elvMaxPower = 0.15;
    // float elvMaxBacklash = 3.2;
    float aziKp = 0.005;
    float aziKd = 0;
    float aziMaxPower = 0.2;

    // Tracking stuff
    float trackingState[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Xpos, Xvel, Xaccel, Ypos, ...
    float rotatorPosition[] = {-500, 0, 0}; // XYZ position (m) relative to launch site

    //Rocket stuff
    float launchPosition[] = {0,0,0}; // in terms of longitude, latitude, and altitude

    // Timing for derivatives and tracking updates
    uint32_t lastTrackingUpdate, lastMotorTime;
    float elvLastPos, aziLastPos, motorDt;

    // Diagnostic stuff
    uint8_t diagnosticStep = 0;
    float elvSequence[] = {30, 60, 90, 120, 150, 30, 30,  30, 30,  30,   30, 30, 90, 150, 30};
    float aziSequence[] = {0,   0,  0,   0,   0,  0, 90, 180, 45, -90, -150,  0, 80, -80,  0};
    uint32_t lastDiagnosticTime;
    uint32_t diagnosticDelay = 1000 * 1000;

    void startTracking(){
        tracking = true;
    }

    void stopTracking(){
        tracking = false;
    }

    /*float getTrackingState_X(){
        return [trackingState[0],trackingState[1],trackingState[2]];
    }
    float getTrackingState_Y(){
        return [trackingState[3],trackingState[4],trackingState[5]];
    }
    float getTrackingState_Z(){
        return [trackingState[6],trackingState[7],trackingState[8]];
    }*/
    std::array<float, 3> gpsToECEF(float lat, float lon, float alt) {
        const float a = 6378137.0f;           // WGS84 semi-major axis
        const float e2 = 6.69437999014e-3f;   // first eccentricity squared
        const float deg2rad = M_PI / 180.0f;

        float latRad = lat * deg2rad;
        float lonRad = lon * deg2rad;

        float N = a / sqrtf(1.0f - e2 * sinf(latRad) * sinf(latRad));
        float x = (N + alt) * cosf(latRad) * cosf(lonRad);
        float y = (N + alt) * cosf(latRad) * sinf(lonRad);
        float z = (N * (1.0f - e2) + alt) * sinf(latRad);
        return {x,y,z} ;
    } // from chatgpt, I sort of fixed it

    // Compute local ENU separation between two GPS coordinates
    // gps1 = reference point (lat, lon, alt)
    // gps2 = target point (lat, lon, alt)
    // enu[3] = output {East, North, Up} in meters
    std::array<float, 3> gpsSeparationENU(float gps1[], float gps2[]) {
        std::array<float,3> rocketpos = gpsToECEF(gps1[0], gps1[1], gps1[2]);
        std::array<float,3> launchpos = gpsToECEF(gps2[0], gps2[1], gps2[2]);

        float dx = rocketpos[0] - launchpos[0];
        float dy = rocketpos[1] - launchpos[1];
        float dz = rocketpos[2] - launchpos[2];

        // Convert ECEF delta to ENU relative to gps1
        const float deg2rad = M_PI / 180.0f;
        float lat0 = gps1[0] * deg2rad;
        float lon0 = gps1[1] * deg2rad;

        float sinLat = sinf(lat0), cosLat = cosf(lat0);
        float sinLon = sinf(lon0), cosLon = cosf(lon0);

        float relx = -sinLon * dx + cosLon * dy;                      // East
        float rely = -sinLat * cosLon * dx - sinLat * sinLon * dy + cosLat * dz; // North
        float relz =  cosLat * cosLon * dx + cosLat * sinLon * dy + sinLat * dz; // Up
        return {relx, rely, relz};
    }
    
    void trackingUpdate(){
        // TODO: Assume the trackingState array is updated with the X, Y, Z positions and accelerations (all X first, then all Y, then all Z)
        float x_position = trackingState[0];
        float x_velocity = trackingState[1];
        float y_position = trackingState[3];
        float y_velocity = trackingState[4];
        float z_position = trackingState[6];
        float z_velocity = trackingState[7];
        
        float x_rotator = rotatorPosition[0];
        float y_rotator = rotatorPosition[1];
        float z_rotator = rotatorPosition[2];
        float distance_from_rocket = sqrt(pow(x_position-x_rotator,2.0)+pow(y_position-y_rotator,2.0));
        float total_distance_from_rocket = sqrt(pow(x_position-x_rotator,2.0)+pow(y_position-y_rotator,2.0) + pow(z_position-z_rotator,2.0));

        float delta_x = x_position-x_rotator;
        float delta_y = y_position-y_rotator;
        float delta_z = z_position-z_rotator;

        const float MIN_DISTANCE_THRESHOLD = 0.01;
        if (distance_from_rocket < MIN_DISTANCE_THRESHOLD) {
            aziRefVel = 0.0;
            elvRefVel = 0.0;
        }
        else { 
            aziRefPos = 180/M_PI * atan2((delta_y),(delta_x));
            elvRefPos = 180/M_PI * asin((delta_z)/sqrt(pow(distance_from_rocket,2.0)+pow(delta_z,2.0)));

            aziRefPos = fmod(aziRefPos + 360.0, 360.0); //convert from -180 to 180 to 0 to 360
            elvRefPos = 90 - elvRefPos;//convert from -90 to 90 to 0 to 180
            aziRefVel = (y_velocity * delta_x - x_velocity * delta_y)/pow(distance_from_rocket,2.0);
            elvRefVel = (z_velocity * distance_from_rocket)/(pow(total_distance_from_rocket,2.0)) - delta_z * (delta_x * x_velocity + delta_y * y_velocity)/(pow(total_distance_from_rocket,2.0) * distance_from_rocket);

            aziRefVel *= 180/M_PI;
            elvRefVel *= 180/M_PI;
        }
    }
        
     void setTrackingPoint(Comms::Packet packet, uint8_t ip){
        // Given the rotatorPosition, turn this into azimuth and elevation commands (position and velocity)
        // Make sure to update elvRefPos, aziRevPos, as well as elvRefVel and aziRefVel
        PacketGPSValues parsed_packet = PacketGPSValues::fromRawPacket(&packet);
        float lat = parsed_packet.m_Latitude;
        float lon = parsed_packet.m_Longitude;
        float att = parsed_packet.m_Altitude;

        float rocketPosition[] = {lat,lon,att};
        trackingState[0] = gpsSeparationENU(rocketPosition, launchPosition)[0];
        trackingState[3] = gpsSeparationENU(rocketPosition, launchPosition)[1];
        trackingState[6] = gpsSeparationENU(rocketPosition, launchPosition)[2];

        trackingUpdate();

        Serial.println("Updating tracking");
        Serial.println("Update azimuth reference position to ");
        Serial.println(aziRefPos);
        Serial.println("Update elevation reference position to ");
        Serial.println(elvRefPos);
        Serial.println("Update azimuth reference velocity to ");
        Serial.println(aziRefVel);
        Serial.println("Update elevation reference velocity to ");
        Serial.println(elvRefVel);
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
        stopTracking();
        stopDiagnostic();
        // TODO: Unwrap an RTSetElevation packet and update the elvRefPos variable
        PacketRTSetElevation parsed_packet = PacketRTSetElevation::fromRawPacket(&packet);
        elvRefPos = parsed_packet.m_Degrees;
        Serial.print("Set elevation setpoint to ");
        Serial.println(elvRefPos);
    }

    void setAziSetpoint(Comms::Packet packet, uint8_t ip){
        stopTracking();
        stopDiagnostic();
        // TODO: Unwrap an RTSetAzimuth packet and update the aziRefPos variable
        PacketRTSetAzimuth parsed_packet = PacketRTSetAzimuth::fromRawPacket(&packet);
        aziRefPos = parsed_packet.m_Degrees;
        Serial.print("Set azimuth setpoint to ");
        Serial.println(aziRefPos);
    }

    void runDiagnostic(Comms::Packet packet, uint8_t ip){
        Serial.println("Beginning diagnostic");
        stopTracking();
        startDiagnostic();
    }

    void switchTracking(Comms::Packet packet, uint8_t ip){
        stopDiagnostic();
        PacketRTEnableFlightTracking parsed_packet = PacketRTEnableFlightTracking::fromRawPacket(&packet);
        if (parsed_packet.m_Action) {
            startTracking();
            Serial.println("Starting tracking");
        } else {
            stopTracking();
            Serial.println("Stopping tracking");
        }
    }

    void sendRotatorState(){
        //PacketRTRotatorState newpacket = PacketRTRotatorState::writeRawPacket();
        //make packet
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

    void sendTrackingState(){
        PacketRTFlightTracking state = PacketRTFlightTracking::Builder()
            .withXPos(trackingState[0])
            .withXVel(trackingState[1])
            .withXAccel(trackingState[2])
            .withYPos(trackingState[3])
            .withYVel(trackingState[4])
            .withYAccel(trackingState[5])
            .withZPos(trackingState[6])
            .withZVel(trackingState[7])
            .withZAccel(trackingState[8])
            .build();
        Comms::Packet newpacket;
        state.writeRawPacket(&newpacket);
        //emit packet 
        //Comms::emitPacketToGS(&newpacket);
    } // TODO: emit trackingState[] as an RTTrackingState packet

    
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

    void accelUpdate(Comms::Packet packet, uint8_t ip) {

    }

    void GPSUpdate(Comms::Packet packet, uint8_t ip) {
        PacketGPSValues parsed_packet = PacketGPSValues::fromRawPacket(&packet);
        Serial.print(parsed_packet.m_Latitude);
    }

    void init(){
        tracking = false;
        diagnostic = false;

        Comms::registerCallback(PACKET_ID_RTSetElevation, setElvSetpoint);
        Comms::registerCallback(PACKET_ID_RTSetAzimuth, setAziSetpoint);
        Comms::registerCallback(PACKET_ID_RTRunDiagnostic, runDiagnostic);
        Comms::registerCallback(PACKET_ID_RTEnableFlightTracking, switchTracking);
<<<<<<< HEAD
        Comms::registerCallback(PACKET_ID_GPSValues, setTrackingPoint);
=======
        Comms::registerCallback(PACKET_ID_LowIMUValues, accelUpdate);
        Comms::registerCallback(PACKET_ID_GPSValues, GPSUpdate);
>>>>>>> fe0fb2b6fff59e6452970b185d0d2b6882546e62
    }

    uint32_t updateAndMove(){
        if (tracking) { // tracking mode
            trackingUpdate();
        } else if (diagnostic) { // diagnostic mode
            diagnosticUpdate();
        } else { // idle mode
            elvRefVel = 0;
            aziRefVel = 0;
        }

        elvRefPos = fmod(elvRefPos, 360.0);
        elvRefPos = max(min(elvRefPos, HAL::maxDegrees_0), HAL::minDegrees_0);
        aziRefPos = fmod(aziRefPos, 360.0);
        // Serial.println("done with updates");
        
        motorDt = ((float) (micros() - lastMotorTime)) / 1000000; // Time since last motor update (not tracking)

        elvPos = HAL::getEncoderDegrees_0();
        elvVel = HAL::getSlope_0() * 1000 * 1000;
        elvError = elvRefPos - elvPos;
        elvPower = elvKp * elvError + elvKd * (elvRefVel - elvVel); // PD control

        if (abs(elvError) < 1) {
            elvPower = 0;
        }

        elvPower = min(max(elvPower, -elvMaxPower), elvMaxPower); // Clamp power to +-maxPower
        HAL::sendPower_0(elvPower); 

        aziPos = HAL::getEncoderDegrees_1(); // Same thing for azimuth
        aziVel = HAL::getSlope_1() * 1000 * 1000;
        aziError = check_wraparound(aziRefPos, aziPos);
        aziPower = aziKp * aziError + aziKd * (aziRefVel - aziVel);

        if (abs(aziError) < 1) {
            aziPower = 0;
        }

        aziPower = min(max(aziPower, -aziMaxPower), aziMaxPower);
        HAL::sendPower_1(aziPower);

        /*Serial.print("Elv power: ");
        Serial.print(elvPower, 5);
        Serial.print(" Azi power: ");
        Serial.println(aziPower, 5);*/

        lastMotorTime = micros();
        elvLastPos = elvPos;
        aziLastPos = aziPos;

        sendRotatorState();

        return updatePeriod;
    }

    /*bool *getStateFlags(){
        bool flags[] = {tracking, diagnostic};
        return flags;
    }*/
     // from chatgpt, I sort of fixed it

}