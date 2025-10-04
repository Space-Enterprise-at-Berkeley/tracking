#pragma once

#include <Arduino.h>
#include <TeensyComms.h>
#include "Util/PIDController.h"
#include <FlexCAN_T4.h>
namespace Rotator {
    void init();
    void moveToAngle();
    void pointToLocation();
    void setPoint();
    void stop();
    void setMode(int mode);

}