#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "SPI.h"
#include "Common.h"
#include "Util/data_buff.h"
#include "TeensyComms.h"
#include "../proto/include/common.h"
#include "../proto/include/Packet_RTEnableRotation.h"

namespace HAL {

    //check pinouts!!!!

    const uint8_t pwm_0 = 28; //sparkmax0 Elevation

    const uint8_t encA_0 = 7; //encoder A green
    const uint8_t encB_0 = 3; //encoder B red 
    const uint8_t encC_0 = 8; //encoder C blue

    const uint8_t tbe_0 = 11; //Through Bore Encoder PWM Input pin Elevation
    const uint8_t tbe_1 = 14; //Through Bore Encoder PWM Input pin Azimuth

    const uint8_t pwm_1 = 37; //sparkmax1 Azimuth

    const uint8_t encA_1 = 21; //encoder A green
    const uint8_t encB_1 = 17; //encoder B red 
    const uint8_t encC_1 = 22; //encoder C blue

    


    extern volatile int encoderTicks_0;
    extern volatile int encoderTicks_1; 

    const float minDegrees_0 = 26;
    const float maxDegrees_0 = 154;

    int init();

    void setupEncoders();

    //void setEncoderCount_0(int i);
    //int getEncoderCount_0();
    float getEncoderDegrees_0();
    float getSlope_0();

    //void setEncoderCount_1(int i);
    //int getEncoderCount_1();
    float getEncoderDegrees_1();
    float getSlope_1();

    //uint32_t printEncoder_0();
    //uint32_t printEncoder_1();

    void resetEncoders();

    void sendPower_0(float x);
    void sendPower_1(float x);

    void stop_0();
    void stop_1();

    void monitor_TBE_0();
    void monitor_TBE_1();
    uint32_t pushToBuffers();

    bool getMotorEnable();
    bool getFault_0();
    bool getFault_1();

    /*float readDegrees(long raw_pulse,float offset_degrees);
    float getEncoderDegrees_0(float offset_degrees);
    float getEncoderDegrees_1(float offset_degrees);

    bool *getStateFlags();*/
}
