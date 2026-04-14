#pragma once

#include <Arduino.h>
#include <TeensyComms.h>
#include "Quaternion.h"
#include "KalmanFilter.h"
#include "../proto/include/common.h"
#include "../proto/include/Packet_LowIMUValues.h"
#include "../proto/include/Packet_GPSValues.h"
#include "../proto/include/Packet_GPSExtraValues.h"
#include "../proto/include/Packet_BaroValues.h"

namespace Tracking {
    void startTracking();
    void stopTracking();

    bool accelUpdate(Comms::Packet packet, uint8_t ip);
    bool GPSUpdate(Comms::Packet packet, uint8_t ip);
    bool baroUpdate(Comms::Packet packet, uint8_t ip);
    uint32_t maintenance();

    std::array<float, 3> gpsToECEF(std::array<float, 3> gps);
    std::array<float, 3> gpsSeparationENU(std::array<float, 3> rocketPosition, std::array<float, 3> launchPosition);
}