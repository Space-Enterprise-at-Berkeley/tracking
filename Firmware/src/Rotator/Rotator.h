#pragma once

#include <Arduino.h>
#include <TeensyComms.h>
#include "Util/PIDController.h"
#include "../proto/include/common.h"
#include "../proto/include/Packet_RTRotatorState.h"
#include "../proto/include/Packet_RTSetElevation.h"
#include "../proto/include/Packet_RTSetAzimuth.h"
#include "../proto/include/Packet_RTFlightTracking.h"
#include "../proto/include/Packet_RTRunDiagnostic.h"
#include "../proto/include/Packet_RTEnableFlightTracking.h"
<<<<<<< HEAD
#include "../proto/include/Packet_GPSValues.h"

=======
#include "../proto/include/Packet_LowIMUValues.h"
#include "../proto/include/Packet_GPSValues.h"
>>>>>>> fe0fb2b6fff59e6452970b185d0d2b6882546e62

namespace Rotator {
    void init();
    uint32_t updateAndMove();
    bool *getStateFlags();
    std::array<float, 3> gpsToECEF(float lat, float lon, float alt);
    std::array<float, 3> gpsSeparationENU(float gps1[], float gps2[]);
}