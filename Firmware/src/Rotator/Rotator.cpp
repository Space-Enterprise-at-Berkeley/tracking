#include "Rotator.h"
#include "EEPROM.h"
#include "HAL.h"
#include <FlexCAN_T4.h>

namespace Rotator {
    // State flags
    bool tracking = false;
    bool diagnostic = false;

    // Motor state
    float elvPos, elvVel, elvPower, aziPos, aziVel, aziPower;
    
    // Reference setpoints
    float elvRefPos, elvRefVel, aziRefPos, aziRefVel;

    // Dynamics constants
    float elvKp = 0.0004;
    float elvKd = 0;
    float elvMaxPower = 0.2;
    float aziKp = 0.0004;
    float aziKd = 0;
    float aziMaxPower = 0.2;

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
    int diagnosticDelay = 1000 * 1000;

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
        diagnostic = true;
        diagnosticStep = 0;
        lastDiagnosticTime = micros();
    }

    void stopDiagnostic(){
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
    }

    void setAziSetpoint(Comms::Packet packet, uint8_t ip){
        stopTracking();
        stopDiagnostic();
        // TODO: Unwrap an RTSetAzimuth packet and update the aziRefPos variable
        PacketRTSetAzimuth parsed_packet = PacketRTSetAzimuth::fromRawPacket(&packet);
        aziRefPos = parsed_packet.m_Degrees;

    }

    void runDiagnostic(Comms::Packet packet, uint8_t ip){
        stopTracking();
        startDiagnostic();
    }

    void sendTrackingState(){
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
    } // TODO: emit elvPos, elvRefPos, elvVel, elvRefVel, and their azimuth equivalents as an RTRotatorState packet

    void sendRotatorState(){
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
        Comms::emitPacketToGS(&newpacket);
    } // TODO: emit trackingState[] as an RTTrackingState packet

    void init(){
        // TODO: make these packet spec'd
        Comms::registerCallback(PACKET_ID_RTSetElevation, setElvSetpoint);
        Comms::registerCallback(PACKET_ID_RTSetAzimuth, setAziSetpoint);
        Comms::registerCallback(PACKET_ID_RTRunDiagnostic, runDiagnostic);

    }

    uint32_t updateAndMove(){
        if (tracking) trackingUpdate();
        else {
            elvRefVel = 0;
            aziRefVel = 0;
            if (diagnostic) diagnosticUpdate();
        }

        motorDt = ((float) (micros() - lastMotorTime)) / 1000000; // Time since last motor update (not tracking)

        elvPos = HAL::getEncoderDegrees_0();
        elvVel = (elvPos - elvLastPos) / motorDt; // Elevation angular velocity, degrees per second
        float elvPower = elvKp * (elvRefPos - elvPos) + elvKd * (elvRefVel - elvVel); // PD control
        HAL::sendPower_0(min(max(elvPower, -elvMaxPower), elvMaxPower)); // Clamp power to +-maxPower

        float aziPos = HAL::getEncoderDegrees_1(); // Same thing for azimuth
        float aziVel = (aziPos - aziLastPos) / motorDt;
        float aziPower = aziKp * (aziRefPos - aziPos) + aziKd * (aziRefVel - aziVel);
        HAL::sendPower_1(min(max(aziPower, -aziMaxPower), aziMaxPower));

        lastMotorTime = micros();
        elvLastPos = elvPos;
        aziLastPos = aziPos;

        sendRotatorState();

        return 5 * 1000;
    }

}