#include <Arduino.h>
#include "HAL.h"
#include "Util.h"
#include "EspComms.h"
#include "Config.h"
#include "StateMachine.h"
#include "Packets.h"
#include "Ducers.h"

StateMachine::FlowState *flowState = StateMachine::getFlowState();
StateMachine::IdleClosedState *idleClosedState = StateMachine::getIdleClosedState();
StateMachine::PartiallyOpenState *partiallyOpenState = StateMachine::getPartiallyOpenState();
StateMachine::DiagnosticState *diagnosticState = StateMachine::getDiagnosticState();
StateMachine::PressurizeState *pressurizeState = StateMachine::getPressurizeState();

void zero() { 
    delay(1000);
    DEBUGLN("starting zero command");
    Serial.printf("fault pin: %d\n", digitalRead(12));
    Util::runMotors(-50);
    long startTime = millis();
    while ((millis() - startTime) < 2000) {
        if (!digitalRead(12)) {
            Serial.printf("fault pin low, starttime %d, millis %d\n",  startTime, millis());
            HAL::printMotorDriverFaultAndDisable();
        }
    }
    Util::runMotors(0); 
    // zero encoder value (so encoder readings range from -x (open) to 0 (closed))
    delay(1100);
    HAL::setEncoderCount(-20);
    DEBUG("encoder position after zero: ");
    DEBUGLN(HAL::getEncoderCount());
}

void zero(Comms::Packet packet, uint8_t ip) {
    zero();
}

void flow(Comms::Packet packet, uint8_t ip) {
    StateMachine::enterFlowState();
}

void stopFlow(Comms::Packet packet, uint8_t ip) {
    StateMachine::enterIdleClosedState();
}

void partialOpen(Comms::Packet packet, uint8_t ip) {
    StateMachine::enterPartialOpenState(Comms::packetGetFloat(&packet, 0));
}

void runDiagnostics(Comms::Packet packet, uint8_t ip) {
    
    StateMachine::enterDiagnosticState();
}

void pressurize(Comms::Packet packet, uint8_t ip) {
    StateMachine::enterPressurizeState();
}


void setup() {
    
    delay(3000);
    Serial.begin(115200);
    Serial.printf("micros: %d\n", micros());
    Serial.printf("hi!!\n");
    if (HAL::init() == -1) {
        DEBUGF("HAL initialization failed\n");
        while(1){};
    } else {
        DEBUGF("HAL initialization success!\n");
    }
    Comms::init(HAL::ETH_CS, HAL::ETH_MISO, HAL::ETH_MOSI, HAL::ETH_SCLK, HAL::ETH_INTn);
    StateMachine::enterIdleClosedState();
    zero(); 
    Comms::registerCallback(200, flow);
    Comms::registerCallback(201, stopFlow);
    Comms::registerCallback(202, partialOpen);
    Comms::registerCallback(203, pressurize);
    Comms::registerCallback(204, runDiagnostics);
    Comms::registerCallback(205, zero);
    
    Packets::sendConfig();
}



void loop() {
    Comms::processWaitingPackets();
    Util::checkMotorDriverHealth();
    HAL::monitorPhaseCurrent();
    switch (StateMachine::getCurrentState()) {
        case StateMachine::IDLE_CLOSED:
        idleClosedState->update();
        break;
        
        case StateMachine::PARTIAL_OPEN:
        partiallyOpenState->update();
        break;

        case StateMachine::PRESSURIZE:
        pressurizeState->update();
        break;

        case StateMachine::FLOW:
        flowState->update();
        break;

        case StateMachine::DIAGNOSTIC:
        diagnosticState->update();
        break;
    };
}

