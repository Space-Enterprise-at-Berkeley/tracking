#include "Arduino.h"
#include "HAL.h"
#include "ERegHat/Util.h"

namespace Ducers {
    void init();
    float readInjectorPT();
    float readPressurantPT();
    float readTankPT();
    float readTankFromInjectorPT();
}