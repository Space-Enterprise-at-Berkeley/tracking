#pragma once

#include <Arduino.h>
#include <TeensyComms.h>
#include "Util/PIDController.h"
#include <FlexCAN_T4.h>
namespace Rotator {
    uint32_t printEncoder();
    void init();
    void moveToAngle();
    void pointToLocation();
    void setPoint();
    void stop();
    void setMode(int mode);
    void setUp();
    void goToTick_0(int tick,int margin);
    void setTargetSetpoint(int sp);
    void setAzimuthSetpoint(int sp);
    void switchModes(uint8_t state);

}