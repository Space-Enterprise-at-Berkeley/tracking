#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "SPI.h"
#include "Common.h"
#include "TeensyComms.h"
#include "TVC.h"

namespace HAL {

    //check pinouts!!!!

    const int x_pwm = 28; //sparkmax0 comments
    const int y_pwm = 37; //sparkmax1

    const int encA_0 = 7; //encoder A green
    const int encB_0 = 3; //encoder B red 
    const int encC_0 = 8; //encoder C blue

    const int encA_1 = 21;
    const int encB_1 = 18;
    const int encC_1 = 22;

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

    void stop_0();
    void stop_1();

    void sendPower_0(float x);
    void sendPower_1(float x);
}
