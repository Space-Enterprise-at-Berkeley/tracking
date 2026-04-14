#pragma once

#include <Arduino.h>
#include <ArduinoEigen.h>
#include <TeensyComms.h>
#include "Quaternion.h"
#include "KalmanFilter.h"
#include "../proto/include/common.h"
#include "../proto/include/Packet_LowIMUValues.h"
#include "../proto/include/Packet_GPSValues.h"
#include "../proto/include/Packet_GPSExtraValues.h"
#include "../proto/include/Packet_BaroValues.h"
#include "../proto/include/Packet_RTFlightTracking.h"
#include "../proto/include/Packet_RTEnableFlightTracking.h"


namespace Tracking {
    void startTracking();
    void stopTracking();
    bool getEnable();

    void accelUpdate(Comms::Packet packet, uint8_t ip);
    void GPSUpdate(Comms::Packet packet, uint8_t ip);
    void baroUpdate(Comms::Packet packet, uint8_t ip);
    uint32_t maintenance();
    Vector<float, 9> getState();

    std::array<float, 3> gpsToECEF(std::array<float, 3> gps);
    std::array<float, 3> gpsSeparationENU(std::array<float, 3> rocketPosition, std::array<float, 3> launchPosition);
}