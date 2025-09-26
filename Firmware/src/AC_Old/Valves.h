#pragma once

#include <Common.h>

#include "HAL.h"
#include <TeensyComms.h>

#include <Arduino.h>
#include <INA219.h>

namespace Valves {

    struct Valve {
        uint8_t valveID;
        uint8_t statePacketID;
        uint8_t statusPacketID;

        uint8_t pin; 
        float voltage;
        float current;
        float ocThreshold;
        uint32_t period;

        INA219 *ina;
    };

    extern Valve igniter;
    extern Valve breakwire;
    extern Valve igniterRelay;

    void initValves();

    void openIgniter();
    void closeIgniter(uint8_t OCShutoff = 0);

    void openIgniterRelay();
    void closeIgniterRelay(uint8_t OCShutoff = 0);

    void sampleValve(Valve *valve);

    uint32_t igniterSample();
    uint32_t breakwireSample();
};