#include "Rotator.h"
#include "EEPROM.h"
#include "HAL.h"
#include <FlexCAN_T4.h>

namespace Rotator {
    uint32_t printEncoder() {
        Serial.println(HAL::getEncoderCount_0());
        return 100 * 1000;
    }

    void setUp(){
        //goToTick_0(300,10);
        Serial.println("about to start");
        HAL::stop_0();
        delay(5000);
    }

    int target_setpoint = 0;
    void setTargetSetpoint(int sp){
        target_setpoint = sp;
        Serial.println(sp);
    }
    float speed = 0.0004f; // How fast the motor approaches the target
    float max_speed = 0.3f;
    float min_speed = speed * 10;
    int tolerance = 5; // How close it needs to be to target before stopping
    void setSpeed(float s){
        speed = s;
    }
    void setMaxSpeed(float ms){
        max_speed = ms;
    }
    void setTolerance(int t){
        tolerance = t;
    }   
    /* Aux func to print important info to the serial terminal */
    void printInfoToSerial(int ticks, int dist, float power){
        Serial.print("ticks: ");
        Serial.print(ticks);
        Serial.print("| target: ");
        Serial.print(target_setpoint);
        Serial.print("| dist: ");
        Serial.print(dist);
        Serial.print("| power: ");
        Serial.println(power);
    }
    /* Updates the motor's power based on the relative distance from target Setpoint */
    /* int tolerance: how close ticks needs to be at the target */
    void moveToSetpoint(int tolerance){
        /* Break early if within tolerance*/
        if (abs(HAL::getEncoderCount_0() - target_setpoint) <= tolerance){
            HAL::stop_0();
            return;
        }
        int ticks = HAL::getEncoderCount_0();
        /* This code ansymptotically approches the target */
        int dist = target_setpoint - ticks;
        float power = speed * (float) dist;
        // Clamp power to max speed and min speed
        if(power > max_speed) power = max_speed;
        else if (power < -max_speed) power = -max_speed;
        if (power > 0 && power < min_speed) power = min_speed;
        else if (power < 0 && power > -min_speed) power = -min_speed;
        HAL::sendPower_0(power);
        printInfoToSerial(ticks, dist, power);
        delay(5);
    }
    void update(){
        /* call every step. 
        You can do other stuff by adding other functions above*/
        moveToSetpoint(tolerance);
    }
    /* Uses a constnant magnitude power to approach target within a margin */
    void goToTick_0(int tick,int margin)
    {
        while(tick - HAL::getEncoderCount_0() > margin)
        {
            Serial.println(HAL::getEncoderCount_0());
            Serial.print("distance: ");
            int distance = tick - HAL::getEncoderCount_0();
            Serial.println(distance);

            if(distance == 0)
                break;
            else if(distance > 0)
                HAL::sendPower_0(-0.01f);
            else
                HAL::sendPower_0(0.01f);

            delay(10);

        }

        HAL::stop_0();
    }

    

}