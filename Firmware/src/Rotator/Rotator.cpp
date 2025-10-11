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
        goToTick_0(300,10);
    }

    
    void goToTick_0(int tick,int margin)
    {
        while(tick - HAL::getEncoderCount_0() > margin)
        {
            Serial.println(HAL::getEncoderCount_0());
            Serial.print("Wanted tick: ");
            Serial.println(tick);


            int distance = tick - HAL::getEncoderCount_0();
            int sign = (distance > 0 ) - (distance < 0);
            
            HAL::sendPower_0(sign * 0.01f);

        }
    }

    

}