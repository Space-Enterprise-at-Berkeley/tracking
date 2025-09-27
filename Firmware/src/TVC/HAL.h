#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "SPI.h"
#include "Common.h"
#include "TeensyComms.h"
#include "TVC.h"

namespace HAL {

    //check pinouts!!!!

    const int x_pwm = 39; //sparkmax0 comments
    const int y_pwm = 15; //sparkmax1

    const int encA_0 = 34; //encoder A blue
    const int encB_0 = 21; //encoder B red
    const int encC_0 = 20; //encoder C green

    const int encA_1 = 14;
    const int encB_1 = 17;
    const int encC_1 = 18;

    extern volatile int encoderTicks_0;
    extern volatile int encoderTicks_1; 


    int init();

    void setupEncoders();

    void setEncoderCount_0(int i);
    int getEncoderCount_0();

    void setEncoderCount_1(int i);
    int getEncoderCount_1();

    uint32_t printEncoder_0();
    uint32_t printEncoder_1();

    void resetEncoders();
}
