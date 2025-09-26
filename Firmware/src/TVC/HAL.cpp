#include "HAL.h"

namespace HAL {

    volatile int encoderTicks_0 = 0;
    volatile int encoderTicks_1 = 0;

    volatile uint8_t curEncState_0 = 0;
    volatile uint8_t curEncState_1 = 0;


    uint8_t revEncMap[] = {100, 5, 3, 4, 1, 0, 2, 100};



    int init() {


        pinMode(x_pwm, OUTPUT); 
        pinMode(y_pwm, OUTPUT);

        ledcSetup(0, 200, 12);
        ledcAttachPin(x_pwm, 0);
        ledcWrite(0, 1229);

        ledcSetup(1, 200, 12);
        ledcAttachPin(y_pwm, 1);
        ledcWrite(1, 1229);
        
        setupEncoders();
        setEncoderCount_0(0);
        setEncoderCount_1(0);

        return 0;
    }

    uint32_t printEncoder_0() {        
        Serial.println(getEncoderCount_0());
        return 50 * 1000;
    }

    uint32_t printEncoder_1() {        
        Serial.println(getEncoderCount_1());
        return 50 * 1000;
    }


    void setEncoderCount_0(int i) {
        encoderTicks_0 = (int) i;
    }

    int getEncoderCount_0() {
        return encoderTicks_0;
    }

    
    void setEncoderCount_1(int i) {
        encoderTicks_1 = (int) i;
    }

    int getEncoderCount_1() {
        return encoderTicks_1;
    }

    void handleEncoderChange(int encA, int encB, int encC, uint8_t* curEncState, int* encoderTicks) {
        bool a, b, c;
        a = digitalRead(encA);
        b = digitalRead(encB);
        c = digitalRead(encC);

        uint8_t newState = a | (b << 1) | (c << 2);

        if (newState == 0 || newState == 7) {
            // TVC::setMode(0); //state error
            return;
        }

        int prevIndex  = revEncMap[*curEncState];
        int newIndex = revEncMap[newState];
        int delta = newIndex - prevIndex;

        if (delta == 1 || delta == -1 || delta == 5 || delta == -5) {
            if (delta == 1 || delta == -5) {
                *encoderTicks -= 1;
            } else {
                *encoderTicks += 1;
            }

            *curEncState = newState;
        } else {
            // TVC::setMode(0);
        }
    }

    void handleEncoderChange_0() {
        handleEncoderChange(encA_0, encB_0, encC_0, (uint8_t*)&curEncState_0, (int*)&encoderTicks_0);
    }
    void handleEncoderChange_1() {
        handleEncoderChange(encA_1, encB_1, encC_1, (uint8_t*)&curEncState_1, (int*)&encoderTicks_1);
    }



    void setupEncoders() {
        pinMode(encA_0, INPUT);
        pinMode(encB_0, INPUT);
        pinMode(encC_0, INPUT);

        pinMode(encA_1, INPUT);
        pinMode(encB_1, INPUT);
        pinMode(encC_1, INPUT);

        attachInterrupt(encA_0, handleEncoderChange_0, CHANGE);
        attachInterrupt(encB_0, handleEncoderChange_0, CHANGE);
        attachInterrupt(encC_0, handleEncoderChange_0, CHANGE);

        attachInterrupt(encA_1, handleEncoderChange_1, CHANGE);
        attachInterrupt(encB_1, handleEncoderChange_1, CHANGE);
        attachInterrupt(encC_1, handleEncoderChange_1, CHANGE);

        #ifndef DISABLE_ENCODER_CHECK
        do {
            curEncState_0 = digitalRead(encA_0) | (digitalRead(encB_0) << 1) | (digitalRead(encC_0) << 2);

            if (millis() % 1000 == 0 && revEncMap[curEncState_0] == 100) {
                Serial.printf("waiting for valid encoders on 0\n");
            }
        } while (revEncMap[curEncState_0] == 100);

        do {
            curEncState_1 = digitalRead(encA_1) | (digitalRead(encB_1) << 1) | (digitalRead(encC_1) << 2);
            if (millis() % 1000 == 0 && revEncMap[curEncState_1] == 100) {
                Serial.printf("waiting for valid encoders on 1\n");
            }
        } while (revEncMap[curEncState_1] == 100);
        #endif

    }

    void resetEncoders() { 
        setEncoderCount_0(0);
        setEncoderCount_1(0);
    }

}