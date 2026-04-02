#pragma once

#include <Arduino.h>
#include <TeensyComms.h>
#include "Rotator.h"
#include "Quaternion.h"
#include "../proto/include/common.h"
#include "../proto/include/Packet_LowIMUValues.h"
#include "../proto/include/Packet_GPSValues.h"
#include "../proto/include/Packet_BaroValues.h"

namespace Tracking {
    std::array<float, 9> trackingState = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Xpos, Xvel, Xaccel, Ypos, ...
    std::array<float, 3> launchPosition;
    std::array<float, 3> launchAcceleration;
    std::array<float, 3> launchGyro;
    float launchPressure;
    float dt;
    
    
    bool trackingStart = false;
    bool apogeeReached = false;

    bool accelUpdate(Comms::Packet packet, uint8_t ip);
    bool GPSUpdate(Comms::Packet packet, uint8_t ip);
    bool baroUpdate(Comms::Packet packet, uint8_t ip);
}