#include "Rotator.h"
#include "EEPROM.h"
#include "HAL.h"
#include <FlexCAN_T4.h>

namespace Rotator {
    // State flags
    bool tracking = false;
    bool diagnostic = false;

    // Motor state
    float elvPos, elvVel, elvPower, elvBacklash, aziPos, aziVel, aziPower, aziBacklash;
    
    // Reference setpoints
    float elvRefPos, elvRefVel, aziRefPos, aziRefVel;

    // Dynamics constants
    float elvKp = 0.002;
    float elvKd = 0.001;
    float elvMaxPower = 0.1;
    float elvMaxBacklash = 3.2;
    float aziKp = 0.001;
    float aziKd = 0;
    float aziMaxPower = 0.1;
    float aziMaxBacklash;

    // Tracking stuff
    float trackingState[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Xpos, Xvel, Xaccel, Ypos, ...
    float rotatorPosition[] = {-500, 0, 0}; // XYZ position (m) relative to launch site

    // Timing for derivatives and tracking updates
    uint32_t lastTrackingUpdate, lastMotorTime;
    float elvLastPos, aziLastPos, motorDt;

    // Diagnostic stuff
    uint8_t diagnosticStep = 0;
    float elvSequence[] = {30, 60, 90, 120, 150, 30, 30,  30,  30,   30, 30, 90, 150, 30};
    float aziSequence[] = {0,   0,  0,   0,   0,  0, 90, 180, -90, -180,  0, 90, -90,  0};
    uint32_t lastDiagnosticTime;
    uint32_t diagnosticDelay = 1000 * 1000;

    void startTracking(){
        tracking = true;
    }

    void stopTracking(){
        tracking = false;
    }

    void trackingUpdate(){
        // TODO: Assume the trackingState array is updated with the X, Y, Z positions and accelerations (all X first, then all Y, then all Z)
        // Given the rotatorPosition, turn this into azimuth and elevation commands (position and velocity)
        // Make sure to update elvRefPos, aziRevPos, as well as elvRefVel and aziRefVel

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
            .withAziPos(aziPos)
            .withAziRefPos(aziRefPos)
            .withAziVel(aziVel)
            .withAziRefVel(aziRefVel)
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
        float error1 = target_angle - current_angle; // forward error
        float error2 = (target_angle - 360) - current_angle; // backward error

        if (abs(error1) < abs(error2)) {
            return error1; // forward is shorter
        } else {
            return error2; // backward is shorter
        }
    }

    void init(){
        tracking = false;
        diagnostic = false;

        Comms::registerCallback(PACKET_ID_RTSetElevation, setElvSetpoint);
        Comms::registerCallback(PACKET_ID_RTSetAzimuth, setAziSetpoint);
        Comms::registerCallback(PACKET_ID_RTRunDiagnostic, runDiagnostic);
        Comms::registerCallback(PACKET_ID_RTEnableFlightTracking, switchTracking);
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
        //aziRefPos = fmod(aziRefPos, 360.0);
        // Serial.println("done with updates");
        
        motorDt = ((float) (micros() - lastMotorTime)) / 1000000; // Time since last motor update (not tracking)

        elvPos = HAL::getEncoderDegrees_0();
        elvVel = HAL::getSlope_0() * 1000 * 1000;
        elvPower = elvKp * (elvRefPos - elvPos) + elvKd * (elvRefVel - elvVel); // PD control
        elvPower = min(max(elvPower, -elvMaxPower), elvMaxPower); // Clamp power to +-maxPower
        HAL::sendPower_0(elvPower); 

        aziPos = HAL::getEncoderDegrees_1(); // Same thing for azimuth
        aziVel = HAL::getSlope_1() * 1000 * 1000;
        aziPower = aziKp * check_wraparound(aziRefPos, aziPos) + aziKd * (aziRefVel - aziVel);
        aziPower = min(max(aziPower, -aziMaxPower), aziMaxPower);
        HAL::sendPower_1(aziPower);

        Serial.print("Elv power: ");
        Serial.print(elvPower, 5);
        Serial.print(" Azi power: ");
        Serial.println(aziPower, 5);

        // BAD!!! MAKE SURE TO REMOVE THIS AFTER TESTING
        aziRefPos = elvPower;
        aziPos = elvPower;

        lastMotorTime = micros();
        elvLastPos = elvPos;
        aziLastPos = aziPos;

        sendRotatorState();

        return 5 * 1000;
    }

    /*bool *getStateFlags(){
        bool flags[] = {tracking, diagnostic};
        return flags;
    }*/
}