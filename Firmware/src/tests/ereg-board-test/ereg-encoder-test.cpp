#include "Arduino.h"

const int encA = 14; //encoder A
const int encB = 15; //encoder B
const int encC = 16; //encoder C
uint8_t encVal = 0;
int change = 0;
void encChange() {
    encVal = 0;
    encVal |= (digitalRead(encA) & 0x01) << 0;
    encVal |= (digitalRead(encB) & 0x01) << 1;
    encVal |= (digitalRead(encC) & 0x01) << 2;
    change = 1;

}
void setup() {
    Serial.begin(115200);
    pinMode(encA, INPUT);
    pinMode(encB, INPUT);
    pinMode(encC, INPUT);

    attachInterrupt(encA, encChange, CHANGE);
    attachInterrupt(encB, encChange, CHANGE);
    attachInterrupt(encC, encChange, CHANGE);

}

void loop() {
    if (change) {
        change = 0;
        Serial.printf("encoders: a %d, b %d, c %d\n", (encVal >> 0) & 0x01, (encVal >> 1) & 0x01, (encVal >> 2) & 0x01);
    }
}