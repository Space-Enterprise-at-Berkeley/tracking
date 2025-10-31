#include <Arduino.h>

uint8_t tbe_0 = 11;
uint8_t tbe_1 = 14;

int lastPulse_0;
long pulseStart_0;

void monitor_0() {
  if (digitalRead(tbe_0)) {
    pulseStart_0 = micros();
  } else {
    lastPulse_0 = micros() - pulseStart_0;
  }
}

void setup() {
  //lastPulse_0 = 0;
  pulseStart_0 = micros();

  attachInterrupt(tbe_0, monitor_0, CHANGE);
  //lastPulse_0 = analogRead(tbe_0);
  while (1) {
    Serial.println(lastPulse_0);
  //lastPulse_0 = 0;
    delayMicroseconds(10000);
  }
}

void loop () {}

/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */
/*#include <Encoder.h>
#define ENC_PIN1 5
#define ENC_PIN2 6

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

Encoder myEnc(ENC_PIN1, ENC_PIN2);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
}*/