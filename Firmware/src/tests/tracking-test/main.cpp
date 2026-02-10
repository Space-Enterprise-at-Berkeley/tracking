#include <Arduino.h>
#include <Common.h>
#include "Util/codegen_KF/CombinedTracker.h"
#include "Util/custom_KF/CombinedTracker.h"

uint32_t lastMessage;
uint32_t startTime;
kalman_filter::CombinedTracker tracker; // the kalman filter namespace imports the custom KF
uint32_t update;

void setup() {
    tracker.init();
    Serial.begin(115200);
    Serial.println("Hello World");
    lastMessage = micros();
    startTime = micros();
}

void loop() {
    if (Serial.available()) {
        float gps[3];
        gps[0] = Serial.parseFloat();
        Serial.read();
        gps[1] = Serial.parseFloat();
        Serial.read();
        gps[2] = Serial.parseFloat();
        Serial.clear();
        Serial.println("Starting update");
        update = micros();
        tracker.GPSUpdate((float) (micros() - startTime)/1000000.0, gps);
        update = micros() - update;
        Serial.println(update);
        Serial.println("End update");
    }

    if (micros() - lastMessage > 1000 * 1000) {
        float state[9];
        update = micros();
        tracker.extrapolate((float) (micros() - startTime)/1000000.0, state);
        update = micros() - update;
        Serial.println(update);
        Serial.print(state[0]);
        Serial.print(" ");
        Serial.print(state[3]);
        Serial.print(" ");
        Serial.println(state[6]);
        lastMessage = micros();
    }
}
