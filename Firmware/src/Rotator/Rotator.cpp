#include "Rotator.h"
#include "EEPROM.h"
#include "HAL.h"
#include <FlexCAN_T4.h>

namespace Rotator {
    uint32_t printEncoder() {
        // Serial.println(HAL::getEncoderCount_0());
        return 100 * 1000;
    }
    void setUp(){
        //goToTick_0(300,10);
        float i = 0.0;
        Serial.print("about to start");
        delay(5000);
        while(1){
            HAL::sendPower_0(0);
            delay(500);
            HAL::sendPower_0(-1.0*i);
            Serial.print("current power:");
            Serial.println(-1.0*i);
            delay(500);
            HAL::printEncoder_0();
            i += 0.01;
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