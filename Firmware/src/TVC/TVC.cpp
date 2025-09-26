#include "TVC.h"
#include "EEPROM.h"
#include "HAL.h"
#define max(A, B) A > B ? A : B

namespace TVC {

    bool freqSweepEnabled = true;

    // define update period
    uint32_t tvcUpdatePeriod = 5 * 1000;
    int x_motor_ticksp = 0;
    int y_motor_ticksp = 0;
    float x_p = 2; //change to 1.6 prob
    float x_i = 0.5e-6;
    float x_d = 0;
    float y_p = 2; //change to 1.6 prob
    float y_i = 0.5e-6;
    float y_d = 0;
    int MID_SPD = 1229;
    //(4096 * (1500 / 200000)))
    int MAX_SPD = 160; //out of 409 max pwr
    int MIN_SPD = -160;
    int INNER_BUFFER_SIZE = 2;
    
    int speed_x = 0;
    int speed_y = 0;

    int idx = 0;
    int idy = 150;

    // just for records
    int max_x_ticks = 500;
    int min_x_ticks = -500;

    int tvcState = 0; //0: constant power move, 1: pid control
    int circleEnabled = false;

    float angle = 0;
    float radius = 0;

    float circlePeriod = 1;
    float circleRadius = 250;
    int circleCrossover = 0; //used to keep track of when the X axis goes back to zero for the first circle loop. Prevents jolt at beginning to top of x axis.

    int flowState = 0;

    float freqSweepCirclePeriod = circlePeriod;
    uint32_t freqSweepTimeDelta = 50 * 1000;
    float totalTime = 14;
    float stopCirclePeriod = 0.4; 
    float freqSweepDelta = ((circlePeriod - stopCirclePeriod) / (totalTime / freqSweepTimeDelta)) * (1e-6);


    // define class variables    
    PIDController x_Controller(
        x_p, x_i, x_d, 
        MIN_SPD, MAX_SPD, 
        PIDController::standard, 
        INNER_BUFFER_SIZE);

    PIDController y_Controller(
        y_p, y_i, y_d, 
        MIN_SPD, MAX_SPD, 
        PIDController::standard, 
        INNER_BUFFER_SIZE);

    void init() {
        x_Controller.reset();
        y_Controller.reset();
        delay(3000); 
    }

    void setRadius(Comms::Packet packet, uint8_t ip) {
        float r = (float)(packetGetFloat(&packet, 0));
        if (r < 550 && r >= 0) {
            Serial.printf("setting radius to %f\n", r);
            radius = r;
            setMode(1);
        }
    }

    void setAngle(Comms::Packet packet, uint8_t ip) {
        setMode(1);
        angle = (float)(packetGetFloat(&packet, 0));
        Serial.printf("setting angle to %f\n", angle);
    }




    void defineSpeeds(Comms::Packet defSpeeds, uint8_t id) {
        setXSpeed(packetGetUint8(&defSpeeds, 0));
        setYSpeed(packetGetUint8(&defSpeeds, 4));
    }

    void getTVCPosition(double radius, double angle, int* xticks, int* yticks) {
        *xticks = (int)(radius * cos(angle));
        *yticks = (int)(radius * sin(angle));
    }




    uint32_t moveTVC() {

        if (tvcState) { // moving with PID is state 1
            if (circleEnabled) { 
                float f;
                if (freqSweepEnabled) {
                    f = freqSweepCirclePeriod;
                } else {
                    f = circlePeriod;
                }
                printf("setting f to %f\n", f);
                angle -= (tvcUpdatePeriod * 2 * PI) / (f * 1000 * 1000);
                if (angle >= 2 * PI) angle -= 2 * PI;
            }

            getTVCPosition(radius, angle, &x_motor_ticksp, &y_motor_ticksp);
            if (x_motor_ticksp < 0) {
                circleCrossover = 1;
            }
            if (!circleCrossover) {
                x_motor_ticksp = 0;
            }
            speed_x = x_Controller.update(x_motor_ticksp - HAL::getEncoderCount_0());
            speed_y = y_Controller.update(y_motor_ticksp - HAL::getEncoderCount_1());

            // Serial.println("X encoder count: " + String(HAL::getEncoderCount_0()));
            // Serial.println("Y encoder count: " + String(HAL::getEncoderCount_1()));
        } else {
            speed_x = 0;
            speed_y = 0;
        } 
        Comms::Packet tmp = {.id=42};
        Comms::packetAddUint32(&tmp, HAL::getEncoderCount_0());
        Comms::packetAddUint32(&tmp, HAL::getEncoderCount_1());
        Comms::emitPacketToGS(&tmp);

        Comms::Packet stp = {.id=43};
        Comms::packetAddUint32(&stp, x_motor_ticksp);
        Comms::packetAddUint32(&stp, y_motor_ticksp);
        Comms::packetAddFloat(&stp, radius);
        Comms::packetAddFloat(&stp, angle);
        Comms::emitPacketToGS(&stp); 


        // if ((millis() % 1000)  >= 0) {
        //     Serial.printf("encX @ %d, encY @ %d\n", HAL::getEncoderCount_0(), HAL::getEncoderCount_1());
        //     Serial.printf("speedX @ %d, speedY @ %d\n", speed_x + MID_SPD, speed_y + MID_SPD);
        // }
        #ifdef DISABLE_ENCODER_CHECK
        ledcWrite(0, MID_SPD);
        ledcWrite(1, MID_SPD);
        #else
        ledcWrite(0, speed_x + MID_SPD);
        ledcWrite(1, speed_y + MID_SPD);
        #endif
        return tvcUpdatePeriod;
    }

    void setMode(int mode) { 
        tvcState = mode;
        // mode 0: manual, 1: PID
    }

    void setTVCMode(Comms::Packet packet, uint8_t ip) { 
        tvcState = (int)(packetGetUint8(&packet, 0));
    }


    void enableCircleNoArgs() {
        setMode(1);
        circleEnabled = 1;// (int)(packetGetUint8(&packet, 0));
        radius = circleRadius;
        // angle = 0;
        Serial.println("Circle enabled");
    }

    void stopCircling() {
        // angle = 0;
        circleEnabled = 0;
        circleCrossover = 0;
    }
    
    uint32_t flowStartTime = 0;

    uint32_t flowSequence() {

        switch (flowState) {
            case 0: 
            {
                //waiting 1 second
                stopCircling();
                flowState++;
                flowStartTime = micros();
                if (freqSweepEnabled) {
                    freqSweepCirclePeriod = circlePeriod;
                }
                return 1500 * 1000;
                break;
            }
            case 1:
            {
                if (freqSweepCirclePeriod == circlePeriod) {
                    // Serial.printf("enabling circle, period is %f\n", freqSweepCirclePeriod);
                    enableCircleNoArgs();
                }
                if (freqSweepEnabled) {
                    if (freqSweepCirclePeriod < stopCirclePeriod) {
                        flowState++;
                        freqSweepCirclePeriod = circlePeriod;
                        Serial.printf("here now\n");
                        return max(10 * 1000, 25 * 1000 * 1000 - (micros() - flowStartTime));
                    } else {
                        freqSweepCirclePeriod -= freqSweepDelta;
                        return freqSweepTimeDelta;
                    }
                } else {
                // if (freqSweepEnabled) {
                //     // Serial.printf("decring fscp\n");
                    
                //     // Serial.printf("setting cp is now to %f\n", freqSweepCirclePeriod);
                // } else {
                    return 30 * 1000 * 1000;
                }
                break;
            }
            case 2:
            {

                stopCircling();
                flowState = 0;
                return 0;
                break;
            }
        }

    }


    void enableCircle(Comms::Packet packet, uint8_t ip) { 
        enableCircleNoArgs();
    }




    void setXSpeed(int spdx) { 
        speed_x = spdx;
    }

    void setYSpeed(int spdy) { 
        speed_y = spdy;
    }

    void stopTVC(Comms::Packet packet, uint8_t ip) { 
        setMode(0);
        flowState = 0;
        circleEnabled = 0;

        speed_x = 0;
        speed_y = 0;
    }

    // uint32_t zero() { //zeroing by jamming against hardstop. For now just going to hold it to a zero position and reset encoders, which is what the new zero routine does
    //     static int zeroState = 0;
    //     circleEnabled = 0;
    //     switch(zeroState) { 
    //         case 0:
    //             setMode(0);
    //             setXSpeed(-15);
    //             setYSpeed(-15);
    //             ledcWrite(0, MID_SPD + speed_x);
    //             ledcWrite(1, MID_SPD + speed_y);    
    //             zeroState = 1;
    //             Serial.println("in zeroing");
    //             return 5*1000*1000;
    //         case 1:
    //             HAL::setEncoderCount_0(650);
    //             HAL::setEncoderCount_1(650);

    //             // x_motor_ticksp = 0;
    //             // y_motor_ticksp = 0;
    //             radius = 0;
    //             angle = 0;

    //             setMode(1);
    //             Serial.println("done zeroing");
    //             zeroState = 0;
    //             return 0; //disables
    //     }
    //     return 0;
    // }

    uint32_t zero() {
        HAL::setEncoderCount_0(0);
        HAL::setEncoderCount_1(0);
        return 0;
    }
    
}
