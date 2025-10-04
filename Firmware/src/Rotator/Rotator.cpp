#include "Rotator.h"
#include "EEPROM.h"
#include "HAL.h"
#define max(A, B) A > B ? A : B

namespace Rotator {
    uint32_t printEncoder() {
        Serial.println(HAL::getEncoderCount_0());
        return 100 * 1000;
    }
}