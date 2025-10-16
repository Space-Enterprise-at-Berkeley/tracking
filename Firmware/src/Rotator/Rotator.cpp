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
        float power = 0.0;
        int ticks = 0;
        int setpoints[] = {550, 1100, 400};
        int index = 0;
        int i = 0;
        Serial.println("about to start");
        HAL::stop_0();
        delay(5000);
        while(1){
            ticks = HAL::getEncoderCount_0();
            power = 0.0004 * (setpoints[index] - ticks);
            Serial.println(ticks);
            HAL::sendPower_0(power);
            if (i % 400 == 0) {
                if (index == 2) index = 0;
                else index++;
            }
            i++;
            delay(5);
        }
    }

    
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