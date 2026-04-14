#pragma once

#include <Arduino.h>
#include <TeensyComms.h>
#include <ArduinoEigen.h>
#include "Tracking.h"
#include "../proto/include/common.h"
#include "../proto/include/Packet_RTRotatorState.h"
#include "../proto/include/Packet_RTSetElevation.h"
#include "../proto/include/Packet_RTSetAzimuth.h"
#include "../proto/include/Packet_RTRunDiagnostic.h"
#include "../proto/include/Packet_RTEnableFlightTracking.h"
#include "../proto/include/Packet_RTZeroAzimuth.h"
#include "../proto/include/Packet_LowIMUValues.h"
#include "../proto/include/Packet_GPSValues.h"

namespace Rotator {
    void init();
    uint32_t updateAndMove();
}