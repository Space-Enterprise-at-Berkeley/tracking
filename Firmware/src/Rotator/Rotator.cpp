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
    
    void setElvSetpoint(Comms::Packet packet, uint8_t ip){
        tracking = false;
        diagnostic = false;
        // TODO: Unwrap an RTSetElevation packet and update the elvRefPos variable
        PacketRTSetElevation parsed_packet = PacketRTSetElevation::fromRawPacket(&packet);
        elvRefPos = parsed_packet.m_Degrees;
    }

    void setAziSetpoint(Comms::Packet packet, uint8_t ip){
        tracking = false;
        diagnostic = false;
        // TODO: Unwrap an RTSetAzimuth packet and update the aziRefPos variable
        PacketRTSetAzimuth parsed_packet = PacketRTSetAzimuth::fromRawPacket(&packet);
        aziRefPos = parsed_packet.m_Degrees;

    }




    void trackingUpdate(){
        // TODO: Assume the trackingState array is updated with the X, Y, Z positions and accelerations (all X first, then all Y, then all Z)
        // Given the rotatorPosition, turn this into azimuth and elevation commands (position and velocity)
        // Make sure to update elvRefPos, aziRevPos, as well as elvRefVel and aziRefVel

    }

    void diagnosticUpdate(){
        // TODO: preprogramed diagnostic movement, this will require some timing and probably an extra array or two
    }

    void runDiagnostic(Comms::Packet packet, uint8_t ip){
        tracking = false;
        diagnostic = true;
        //run the actual diagnostic
        diagnosticUpdate();

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

    /*int tolerance = 5; // How close it needs to be to target before stopping
    void setSpeed(float s){
        speed = s;
    }
    void setMaxSpeed(float ms){
        max_speed = ms;
    }
    void setTolerance(int t){
        tolerance = t;
    }   
    // Aux func to print important info to the serial terminal
    void printInfoToSerial(int ticks, int dist, float power){
        Serial.print("ticks: ");
        Serial.print(ticks);
        Serial.print("| target: ");
        Serial.print(target_setpoint);
        Serial.print("| dist: ");
        Serial.print(dist);
        Serial.print("| power: ");
        Serial.println(power);
    }
    // Updates the motor's power based on the relative distance from target Setpoint
    // int tolerance: how close ticks needs to be at the target
    void moveToSetpoint(int tolerance){
        // Break early if within tolerance
        if (abs(HAL::getEncoderCount_0() - target_setpoint) <= tolerance){
            HAL::stop_0();
            return;
        }
        int ticks = HAL::getEncoderCount_0();
        // This code ansymptotically approches the target
        int dist = target_setpoint - ticks;
        float power = speed * (float) dist;
        // Clamp power to max speed and min speed
        if(power > max_speed) power = max_speed;
        else if (power < -max_speed) power = -max_speed;
        if (power > 0 && power < min_speed) power = min_speed;
        else if (power < 0 && power > -min_speed) power = -min_speed;
        HAL::sendPower_0(power);
        printInfoToSerial(ticks, dist, power);
        delay(5);
    }
    void update(){
        // call every step. 
        // You can do other stuff by adding other functions above
        moveToSetpoint(tolerance);
    }
    // Uses a constnant magnitude power to approach target within a margin
    void goToTick_0(int tick,int margin)
    {
        while(tick - HAL::getEncoderCount_0() > margin)
        {
            Serial.println(HAL::getEncoderCount_0());
            Serial.print("distance: ");
            int distance = tick - HAL::getEncoderCount_0();
            Serial.println(distance);

            if(distance == 0)
                break;
            else if(distance > 0)
                HAL::sendPower_0(-0.01f);
            else
                HAL::sendPower_0(0.01f);

            delay(10);

        }

        HAL::stop_0();
    }*/

    

}