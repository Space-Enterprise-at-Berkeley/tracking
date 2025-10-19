#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "SPI.h"
#include "Common.h"
#include "TeensyComms.h"
#include "../proto/include/common.h"
#include "../proto/include/Packet_EnableRotation.h"

namespace HAL {

    //check pinouts!!!!

    const int x_pwm = 28; //sparkmax0 Azimuth

    const int encA_0 = 7; //encoder A green
    const int encB_0 = 3; //encoder B red 
    const int encC_0 = 8; //encoder C blue

    const int TBE_0 = 14; //Through Bore Encoder PWM Input pin Azimuth

    const int y_pwm = 37; //sparkmax1 Elevation

    const int encA_1 = 21; //encoder A green
    const int encB_1 = 17; //encoder B red 
    const int encC_1 = 22; //encoder C blue

    const int TBE_1 = 11; //Through Bore Encoder PWM Input pin Elevation

    extern volatile int encoderTicks_0;
    extern volatile int encoderTicks_1; 

    const int minTicks_0 = 0;
    const int maxTicks_0 = 1500;
    const int minTicks_1 = 0;
    const int maxTicks_1 = 1500;

    int init();

    void setupEncoders();

    void setEncoderCount_0(int i);
    int getEncoderCount_0();

    void setEncoderCount_1(int i);
    int getEncoderCount_1();

    uint32_t printEncoder_0();
    uint32_t printEncoder_1();

    void resetEncoders();

    void sendPower_0(float x);
    void sendPower_1(float x);

    void stop_0();
    void stop_1();
}
