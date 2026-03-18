#pragma once

#include <Arduino.h>
#include <TeensyComms.h>
#include "Util/PIDController.h"
#if defined(USE_CODEGEN_KF)
#include "Util/codegen_KF/CombinedTracker.h"
#else
#include "Util/custom_KF/CombinedTracker.h"
#endif
#include "../proto/include/common.h"
#include "../proto/include/Packet_RTRotatorState.h"
#include "../proto/include/Packet_RTSetElevation.h"
#include "../proto/include/Packet_RTSetAzimuth.h"
#include "../proto/include/Packet_RTFlightTracking.h"
#include "../proto/include/Packet_RTRunDiagnostic.h"
#include "../proto/include/Packet_RTEnableFlightTracking.h"
#include "../proto/include/Packet_RTZeroAzimuth.h"
#include "../proto/include/Packet_LowIMUValues.h"
#include "../proto/include/Packet_GPSValues.h"

namespace Rotator {
    void init();
    uint32_t updateAndMove();
    bool *getStateFlags();
    void gpsSeparationENU(float gps1[], float gps2[], float out[]);
}