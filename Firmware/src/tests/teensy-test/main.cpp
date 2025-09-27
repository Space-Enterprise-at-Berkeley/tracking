
#include <Arduino.h>
#include <Common.h>
#include "EEPROM.h"


const int x_pwm = 7; //sparkmax0

void setup() {
    Serial.begin(115200);
    Serial.println("Hello World");

    

    pinMode(x_pwm, OUTPUT); 

    //0 - 4096
    // 307 +- 100


    //ledcSetup(0, 50, 12);
    //ledcAttachPin(x_pwm, 0);
    //ledcWrite(0, 307);

    analogWriteResolution(12);
    analogWriteFrequency(x_pwm, 200);
    analogWrite(x_pwm, 1229);

    //ledcSetup(1, 50, 12);
    //ledcAttachPin(y_pwm, 1);
    //ledcWrite(1, 307);


}


void loop() {
/*
    Serial.printf("high\n");
    //digitalWrite(48, HIGH);
    //ledcWrite(1, 307 + 5);
    //analogWrite(x_pwm, 307 + 5);


    analogWrite(x_pwm, 1229);

    delay(5000);
    //ledcWrite(1, 307);
    analogWrite(x_pwm, 307);
    delay(5000);
*/

    /*
    Serial.printf("low\n");
    digitalWrite(48, LOW);
    ledcWrite(1, 307 - 5);
    delay(5000);
    ledcWrite(1, 307);
    delay(1000);
    */


}