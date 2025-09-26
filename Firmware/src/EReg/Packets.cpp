#include "Packets.h"
#include "Config.h"
#include "EspComms.h"
#include "StateMachine.h"

namespace Packets {
    /**
     * Send telemetry packet:
     * - upstream pressure
     * - downstream pressure 
     * - encoder reading 
     * - angle setpoint 
     * - pressure setpoint
     * - motor power 
     * - pressure control loop P term
     * - pressure control loop I term
     * - pressure control loop D term
     */


    uint8_t ac1_ip = 11;
    uint8_t ac2_ip = 12;
    uint8_t ACTUATE_IP = 100;


    void sendTelemetry(
        float upstreamPressure,
        float downstreamPressure,
        float encoderAngle,
        float angleSetpoint,
        float pressureSetpoint,
        float motorPower,
        float pressureControlP,
        float pressureControlI,
        float pressureControlD
    ) {

        Comms::Packet packet = {.id = TELEMETRY_ID};
        Comms::packetAddFloat(&packet, upstreamPressure);
        Comms::packetAddFloat(&packet, downstreamPressure);
        Comms::packetAddFloat(&packet, encoderAngle);
        Comms::packetAddFloat(&packet, angleSetpoint);
        Comms::packetAddFloat(&packet, pressureSetpoint);
        Comms::packetAddFloat(&packet, motorPower);
        Comms::packetAddFloat(&packet, pressureControlP);
        Comms::packetAddFloat(&packet, pressureControlI);
        Comms::packetAddFloat(&packet, pressureControlD);
        Comms::emitPacket(&packet);
        sendTemperatures();
        sendPhaseCurrents();
        sendLimitSwitches();
        // Serial.printf("packet sent\n");
    }

    /**
     * Send config packet:
     * - target downstream pressure
     * - outer control loop k_p
     * - outer control loop k_i
     * - outer control loop k_d
     * - inner control loop k_p
     * - inner control loop k_i
     * - inner control loop k_d
     */
    void sendConfig() {
        Comms::Packet packet = {.id = CONFIG_ID};
        Comms::packetAddFloat(&packet, Config::pressureSetpoint);
        Comms::packetAddFloat(&packet, Config::p_outer_nominal);
        Comms::packetAddFloat(&packet, Config::i_outer_nominal);
        Comms::packetAddFloat(&packet, Config::d_outer_nominal);
        Comms::packetAddFloat(&packet, Config::p_inner);
        Comms::packetAddFloat(&packet, Config::i_inner);
        Comms::packetAddFloat(&packet, Config::d_inner);
        Comms::packetAddFloat(&packet, (float) (Config::flowDuration / 1e6));
        Comms::emitPacket(&packet);
    }

    /**
     * Send diagnostic test report packet:
     * - success / failure message
     */
    void sendDiagnostic(uint8_t motorDirPass, uint8_t servoPass) {
        #ifdef DEBUG_MODE
        DEBUGF("Motor Dir Test: %i \t Servo Test: %i \n", motorDirPass, servoPass);
        #else
        Comms::Packet packet = {.id = DIAGNOSTIC_ID};
        packet.len = 0;
        Comms::packetAddUint8(&packet, motorDirPass);
        Comms::packetAddUint8(&packet, servoPass);
        Comms::emitPacket(&packet);
        #endif
    }

    /**
     * Send state transition failure packet:
     * - failure message
     */
    void sendStateTransitionError(uint8_t errorCode) {
        #ifdef DEBUG_MODE
        DEBUG("State Transition Error: ");
        DEBUGLN(errorCode);
        #else
        Comms::Packet packet = {.id = STATE_TRANSITION_FAIL_ID};
        packet.len = 0;
        Comms::packetAddUint8(&packet, errorCode);
        Comms::emitPacket(&packet);
        #endif
    }

    /**
     * @brief sends flow state updates to the AC
     * flowStates: 0 = abort
     * @param flowState 
     */
    void sendFlowState(uint8_t flowState) {
        Comms::Packet packet = {.id = FLOW_STATE};
        packet.len = 0;
        Comms::packetAddUint8(&packet, flowState);
        Comms::emitPacket(&packet);
    }


    /**
     * Sends an abort command to all 4 ESPs
     */
    void broadcastAbort() { //TODO
        Comms::Packet packet = {.id = ABORT_ID};
        packet.len = 0;
        Comms::emitPacket(&packet);

        //send abort to ACs
        Comms::Packet actuate = {.id = ACTUATE_IP, .len=0};

        //open fuel GEMS
        actuate.len = 0;
        Comms::packetAddUint8(&actuate, 7);
        Comms::packetAddUint8(&actuate, 4);
        Comms::packetAddUint8(&actuate, 0);
        Comms::emitPacket(&actuate, ac2_ip);
        delay(30);

        //open lox GEMS
        actuate.len = 0;
        Comms::packetAddUint8(&actuate, 6);
        Comms::packetAddUint8(&actuate, 4);
        Comms::packetAddUint8(&actuate, 0);
        Comms::emitPacket(&actuate, ac2_ip);



        delay(30);

        //open lox vent rbv
        actuate.len = 0;
        Comms::packetAddUint8(&actuate, 3);
        Comms::packetAddUint8(&actuate, 0);
        Comms::packetAddUint8(&actuate, 0);
        Comms::emitPacket(&actuate, ac2_ip);

        delay(30);

        //open fuel vent rbv
        actuate.len = 0;
        Comms::packetAddUint8(&actuate, 4);
        Comms::packetAddUint8(&actuate, 0);
        Comms::packetAddUint8(&actuate, 0);
        Comms::emitPacket(&actuate, ac2_ip);

    }


    void sendPhaseCurrents() {
        Comms::Packet packet = {.id = PHASE_CURRENTS};
        packet.len = 0;
        HAL::packetizePhaseCurrents(&packet);
        Comms::emitPacket(&packet);
    }

    void sendTemperatures() {
        Comms::Packet packet = {.id = TEMPS};
        packet.len = 0;
        HAL::packetizeTemperatures(&packet);
        Comms::emitPacket(&packet);
    }

    void sendOvercurrentPacket() {
        Comms::Packet packet = {.id = OVERCURRENT_ID};
        packet.len = 0;
        Comms::emitPacket(&packet);
    }

    void sendLimitSwitches() {
        Comms::Packet packet = {.id = LIMIT_SWITCHES};
        packet.len = 0;
        Comms::packetAddFloat(&packet, HAL::getClosedLimitSwitchState());
        Comms::packetAddFloat(&packet, HAL::getOpenLimitSwitchState());
        Comms::emitPacket(&packet);
    }

}