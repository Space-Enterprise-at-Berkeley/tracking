#include <Arduino.h>
#include <Common.h>
#include "Util/codegen_KF/CombinedTracker.h"

uint32_t lastMessage;
uint32_t startTime;
CombinedTracker tracker;

void setup() {
    tracker.init();
    Serial.begin(115200);
    Serial.println("Hello World");
    lastMessage = micros();
    startTime = micros();
}

void loop() {
    if (Serial.available()) {
        double gps[3];
        gps[0] = Serial.parseFloat();
        Serial.read();
        gps[1] = Serial.parseFloat();
        Serial.read();
        gps[2] = Serial.parseFloat();
        Serial.clear();
        Serial.println("Starting update");
        tracker.GPSUpdate((double) (micros() - startTime)/1000000.0, gps);
        Serial.println("End update");
    }

    if (micros() - lastMessage > 1000 * 1000) {
        double state[9];
        tracker.extrapolate((double) (micros() - startTime)/1000000.0, state);
        Serial.print(state[0]);
        Serial.print(" ");
        Serial.print(state[3]);
        Serial.print(" ");
        Serial.println(state[6]);
        lastMessage= micros();
    }
}