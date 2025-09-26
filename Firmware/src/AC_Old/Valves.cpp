#include "Valves.h"

namespace Valves {
    // state of each valve is stored in each bit
    // bit 0 is armValve, bit 1 is igniter, etc
    // the order of bits is the same as the order of valves on the E-1 Design spreadsheet
    uint16_t valveStates = 0x00;

    // info for each individual valve

    Valve igniter = {.valveID = 0,
                      .statePacketID = 80,
                      .statusPacketID = 81,
                      .pin = HAL::ctl24vChan1,
                      .voltage = 0.0,
                      .current = 0.0,
                      .ocThreshold = 3.0,
                      .period = 10 * 1000,
                      .ina = &HAL::chan2};

    Valve breakwire = {.valveID = 1,
                      .statePacketID = 82,
                      .statusPacketID = 83,
                      .pin = HAL::ctl24vChan2,
                      .voltage = 0.0,
                      .current = 0.0,
                      .ocThreshold = 3.0,
                      .period = 10 * 1000,
                      .ina = &HAL::chan3};

    Valve igniterRelay = {.valveID = 2,
                      .statePacketID = 84,
                      .statusPacketID = 85,
                      .pin = 15,
                      .voltage = 0.0,
                      .current = 0.0,
                      .ocThreshold = 3.0,
                      .period = 10 * 1000,
                      .ina = NULL};

    void sendStatusPacket() {
        Comms::Packet tmp = {.id = 86};
        Comms::packetAddUint16(&tmp, valveStates);
        Comms::emitPacketToGS(&tmp);
    }

    // common function for opening a valve
    void openValve(Valve *valve) {
        digitalWriteFast(valve->pin, HIGH); // turn on the physical pin
        valveStates |= (0x01 << valve->valveID); // set bit <valveID> to 1

        Comms::Packet tmp = {.id = valve->statePacketID}; // valve packets have an offset of 40 (check the E-1 Design spreadsheet)
        Comms::packetAddUint8(&tmp, 1); // a value of 1 indicates the valve was turned on
        Comms::emitPacketToGS(&tmp);
        
        sendStatusPacket();
    }

    // common function for closing a valve
    void closeValve(Valve *valve, uint8_t OCShutoff) { //optional argument overcurrentShutoff
        digitalWriteFast(valve->pin, LOW); // turn off the physical pin
        valveStates &= ~(0x01 << valve->valveID); // set bit <valveID> to 1

        Comms::Packet tmp = {.id = valve->statePacketID}; // valve packets have an offset of 40 (check the E-1 Design spreadsheet)
        Comms::packetAddUint8(&tmp, OCShutoff << 1); // a value of 0 indicates the valve was turned off, 2 indicates overcurrent shutoff
        Comms::emitPacketToGS(&tmp);
        
        sendStatusPacket();
    }

    // functions for each individual valve
    void openIgniter() { openValve(&igniter); }
    void closeIgniter(uint8_t OCShutoff = 0) { closeValve(&igniter, OCShutoff); }
    void igniterPacketHandler(Comms::Packet tmp, uint8_t ip) { return tmp.data[0] ? openIgniter() : closeIgniter(); }

    void openIgniterRelay() { openValve(&igniterRelay); }
    void closeIgniterRelay(uint8_t OCShutoff = 0) { closeValve(&igniterRelay, OCShutoff); }
    void igniterRelayPacketHandler(Comms::Packet tmp, uint8_t ip) { return tmp.data[0] ? openIgniterRelay() : closeIgniterRelay(); }

    // common function for sampling a valve's voltage and current
    void sampleValve(Valve *valve) {
        valve->voltage = valve->ina->readBusVoltage();
        valve->current = valve->ina->readShuntCurrent();
        
        Comms::Packet tmp = {.id = valve->statusPacketID};
        //IDS: Arming valve, igniter, lox main valve, fuel main valve
        if (valve->current > valve->ocThreshold) {
            closeValve(valve, 1);
        }
        Comms::packetAddFloat(&tmp, valve->voltage);
        Comms::packetAddFloat(&tmp, valve->current);
        Comms::emitPacketToGS(&tmp);
    }

    // individual task functions (see taskTable in main.cpp)

    uint32_t igniterSample() {
        sampleValve(&igniter);
        return igniter.period;
    }

    uint32_t breakwireSample() {
        sampleValve(&breakwire);
        return breakwire.period;
    }

    // init function for valves namespace
    void initValves() {
        // link the right packet IDs to the valve open/close handler functions
        Comms::registerCallback(181, igniterPacketHandler);
        Comms::registerCallback(182, igniterRelayPacketHandler);

        pinMode(15, OUTPUT);
        digitalWriteFast(15, LOW);
    }

};