#pragma once

#include <Arduino.h>

namespace Packets {

    const uint8_t TELEMETRY_ID = 1;
    const uint8_t CONFIG_ID = 2;
    const uint8_t DIAGNOSTIC_ID = 3;
    const uint8_t STATE_TRANSITION_FAIL_ID = 4;
    const uint8_t FLOW_STATE = 5;
    const uint8_t LIMIT_SWITCHES = 6;
    const uint8_t PHASE_CURRENTS = 7;
    const uint8_t TEMPS = 8;
    const uint8_t ABORT_ID = 9;
    const uint8_t OVERCURRENT_ID = 10;

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
    );
    void sendConfig();
    void sendDiagnostic(uint8_t motorDirPass, uint8_t servoPass);
    void sendStateTransitionError(uint8_t errorCode);
    void sendFlowState(uint8_t flowState);
    void broadcastAbort();
    void sendPhaseCurrents();
    void sendTemperatures();
    void sendOvercurrentPacket();
    void sendLimitSwitches();
}
