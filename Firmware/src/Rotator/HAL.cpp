#include "HAL.h"

namespace HAL {

    volatile int encoderTicks_0 = 0;
    volatile int encoderTicks_1 = 0;

    volatile uint8_t curEncState_0 = 0;
    volatile uint8_t curEncState_1 = 0;

    volatile long pulseStart_0 = 0; //Through Bore Encoder Elevation Pulse Start
    volatile long pulseWidth_0 = 0; //Through Bore Encoder Elevation Pulse Width

    volatile long pulseStart_1 = 0; //Through Bore Encoder Azimuth Pulse Start
    volatile long pulseWidth_1 = 0; //Through Bore Encoder Azimuth Pulse Width

    bool allowMotorMovement = false;


    /* MAGIC! */
    uint8_t revEncMap[] = {100, 5, 3, 4, 1, 0, 2, 100};
    uint8_t revEncMap_C_Pin_Broken[] = {0, 0, 3, 3, 1, 1, 2, 2};
    uint8_t revEncMap_B_Pin_Broken[] = {0, 1, 0, 1, 3, 2, 3, 2};
    uint8_t revEncMap_A_Pin_Broken[] = {0, 3, 1, 2, 0, 3, 1, 2};

    volatile int num_broken_pins;

    void motorMovement(Comms::Packet packet, uint8_t ip){
        PacketRTEnableRotation parsed_packet = PacketRTEnableRotation::fromRawPacket(&packet);
        allowMotorMovement = parsed_packet.m_Action;
        Serial.println("Motor enable set to: " + allowMotorMovement);
    }

    


    int init() {
        /* In case a singular pin is broken, we can gracefully handle it without too much issue */
        #ifdef ENCODER_A_PIN_BROKEN
            num_broken_pins += 1;
            for (int i = 0; i < 8; i++) { // Maybe there's a better way to do this idk
                revEncMap[i] = revEncMap_A_Pin_Broken[i];
            }
        #endif
        #ifdef ENCODER_B_PIN_BROKEN
            num_broken_pins += 1;
            for (int i = 0; i < 8; i++) {
                revEncMap[i] = revEncMap_B_Pin_Broken[i];
            }
        #endif
        #ifdef ENCODER_C_PIN_BROKEN
            num_broken_pins += 1;
            for (int i = 0; i < 8; i++) {
                revEncMap[i] = revEncMap_C_Pin_Broken[i];
            }
        #endif

        if (num_broken_pins > 1) {
            while (1) {
                Serial.println("ERROR: At most one encoder pin can be broken");
                delay(10);
            }
        }
        pinMode(pwm_0, OUTPUT); 
        pinMode(pwm_1, OUTPUT);

        //ledcSetup(0, 200, 12);
        //ledcAttachPin(pwm_0, 0);
        //ledcWrite(0, 1229);

        analogWriteResolution(12);
        analogWriteFrequency(pwm_0, 200);
        analogWrite(pwm_0, 1229);

        //ledcSetup(1, 200, 12);
        //ledcAttachPin(pwm_1, 1);
        //ledcWrite(1, 1229);
        //analogWriteResolution(12);

        analogWriteFrequency(pwm_1, 200);
        analogWrite(pwm_1, 1229);


        setupEncoders();
        setEncoderCount_0(0);
        setEncoderCount_1(0);

        Comms::registerCallback(PACKET_ID_RTEnableRotation, motorMovement);

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

        if (revEncMap[newState] == 100) {
            // TVC::setMode(0); //state error
            return;
        }

        int prevIndex  = revEncMap[*curEncState];
        int newIndex = revEncMap[newState];
        int delta = newIndex - prevIndex;
        int turnover = num_broken_pins ? 3 : 5;
        if (delta == 1 || delta == -1 || delta == turnover || delta == -turnover) {
            if (delta == 1 || delta == -turnover) {
                *encoderTicks += (num_broken_pins && (prevIndex == 0 || newIndex == 0)) ?  2 : 1;
            } 
            else {
                *encoderTicks -= (num_broken_pins && (prevIndex == 0 || newIndex == 0)) ?  2 : 1;
            }

            *curEncState = newState;
        } else {
            // TVC::setMode(0);
        }
        
        // Serial.printf("a: %d, b: %d, c: %d, delta: %d, ticks: %d\n", a, b, c, delta, encoderTicks_0);
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

        pinMode(tbe_0, INPUT);
        pinMode(tbe_1, INPUT);

        attachInterrupt(encA_0, handleEncoderChange_0, CHANGE);
        attachInterrupt(encB_0, handleEncoderChange_0, CHANGE);
        attachInterrupt(encC_0, handleEncoderChange_0, CHANGE);

        attachInterrupt(encA_1, handleEncoderChange_1, CHANGE);
        attachInterrupt(encB_1, handleEncoderChange_1, CHANGE);
        attachInterrupt(encC_1, handleEncoderChange_1, CHANGE);

        attachInterrupt(tbe_0, monitor_TBE_0, CHANGE);
        attachInterrupt(tbe_1, monitor_TBE_1, CHANGE);



        #ifndef DISABLE_RELATIVE_ENCODER_CHECK
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
        } while (revEncMap[curEncState_1] == 100 && false); // change this when there's a second encoder
        #endif

    }

    void resetEncoders() { 
        setEncoderCount_0(0);
        setEncoderCount_1(0);
    }

    void sendPwm(uint8_t pin, float power){
        // Serial.println(power);

        float deadband = 0.01;
        int neutral = (1500*4096)/5000; // middle of deadband
        int upper_neutral = (1500*(1+deadband)*4096)/5000; // top of deadband
        int lower_neutral = (1500*(1-deadband)*4096)/5000;
        int maximum = (2000*4096)/5000;
        int minimum = (1000*4096)/5000;

        if (power < -1) power = -1;
        if (power > 1) power = 1;
        if (!allowMotorMovement) power = 0;

        int pulse = neutral;

        if (power > 0)
            pulse = upper_neutral + (maximum - upper_neutral) * power;
        else if (power < 0)
            pulse = lower_neutral + (lower_neutral - minimum) * power;
        
        analogWrite(pin, pulse);

    }

    void sendPower_0(float power){
        if ((power > 0 && encoderTicks_0 > maxTicks_0) || (power < 0 && encoderTicks_0 < minTicks_0)) {
            sendPwm(pwm_0, 0);
        } else if ((power > 0 && encoderTicks_0 > maxTicks_0 - 200) || (power < 0 && encoderTicks_0 < minTicks_0 + 200)) {
            sendPwm(pwm_0, max(min(power, 0.025), -0.025));
        } else {
            sendPwm(pwm_0, power);
        }
    }

    void sendPower_1(float power){
        sendPwm(pwm_1, power);
    }

    void stop_0() {
        sendPower_0(0);
    }

    void stop_1() {
        sendPower_1(0);
    }
    const float PULSE_MAX = 1024;
    const float PULSE_MIN = 1;

    void monitor_TBE_0(){
        if(digitalRead(HAL::tbe_0) == HIGH){
            pulseStart_0 = micros();
        }
        else{
            pulseWidth_0 = micros() - pulseStart_0;
        }
    }

    void monitor_TBE_1(){
        if(digitalRead(HAL::tbe_1) == HIGH){
            pulseStart_1 = micros();
        }
        else{
            pulseWidth_1 = micros() - pulseStart_1;
        }
    }

    float readDegrees(long raw_pulse) {
        long relative_pulse = raw_pulse - PULSE_MIN;
        if(relative_pulse < 0) relative_pulse = 0;
        if(relative_pulse > 1023) relative_pulse = 1023;
        return (float)relative_pulse * 360/(PULSE_MAX - PULSE_MIN);
        // TODO: use interrupts to read the pulse width coming from the TBE pin and convert to a degree measurement
        // Look in tests/rev-encoder-test for an example of how to do this, you will need to define a new function
        // 1 microsecond = 0 degrees, 1024 microseconds = 360 degrees
    }

    float getEncoderDegrees_0() {
        return readDegrees(pulseWidth_0);
    }
    
    float getEncoderDegrees_1() {
        return readDegrees(pulseWidth_1);
    }

}