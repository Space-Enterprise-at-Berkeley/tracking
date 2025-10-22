#pragma once

#include <Arduino.h>
#include <TeensyComms.h>
#include "Util/PIDController.h"
#include <FlexCAN_T4.h>
namespace Rotator {
    void init();
    void deinit();
    void goToTick_0(int tick,int margin);
    void setTargetSetpoint(int sp);
    void setAzimuthSetpoint(int sp);

}