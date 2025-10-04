#include "Rotator.h"
#include "EEPROM.h"
#include "HAL.h"
#include <FlexCAN_T4.h>

namespace Rotator {
    void moveToAngle(){
        //Get current angle from encoder.
        //Compute error = targetAngle − currentAngle
        //Run PID controller on error → output control value.
        //Convert control value to PWM duty cycle (0–4095 for Teensy).
        //Send PWM to Spark MAX pins.
        //Stop when error is within tolerance (e.g., ±1°).
    }
    
}