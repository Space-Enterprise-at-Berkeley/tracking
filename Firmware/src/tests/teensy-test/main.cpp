
#include <Arduino.h>
#include <Common.h>
#include "EEPROM.h"


int main(void) {

  Serial.begin(115200);

  


    while (1) {
        Serial.println("hello World");

        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);


    } 

    return 0;
}
