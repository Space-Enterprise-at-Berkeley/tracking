#include <Arduino.h>


volatile int encoderTicks = 0;

int32_t numReads = 0;


const int encA_0 = 34; //encoder A blue
const int encB_0 = 21; //encoder B red
const int encC_0 = 20; //encoder C green
bool printFlag;

const int encA_1 = 14;
const int encB_1 = 17;
const int encC_1 = 18;

int encA = encA_1;
int encB = encB_1;
int encC = encC_1;

void setEncoderCount(int i) {
    encoderTicks = (int) i;
}

int getEncoderCount() {
    return encoderTicks;
}

int curEncState = 0;
uint8_t forwardEncMap[] = {0b101, 0b100, 0b110, 0b010, 0b011, 0b001};
uint8_t revEncMap[] = {100, 5, 3, 4, 1, 0, 2, 100};

void handleEncoderChange() {
    printFlag = true;

    bool a, b, c;
    a = digitalRead(encA);
    b = digitalRead(encB);
    c = digitalRead(encC);

    uint8_t newState = a | (b << 1) | (c << 2);

    if (newState == 0 || newState == 7) {
        return;
    }

    int prevIndex  = revEncMap[curEncState];
    int newIndex = revEncMap[newState];
    int delta = newIndex - prevIndex;

    if (delta == 1 || delta == -1 || delta == 5 || delta == -5) {
        if (delta == 1 || delta == -5) {
            encoderTicks += 1;
        } else {
            encoderTicks -= 1;
        }

        curEncState = newState;
    } 
}

void setupEncoder() {
    pinMode(encA, INPUT);
    pinMode(encB, INPUT);
    pinMode(encC, INPUT);

    attachInterrupt(encA, handleEncoderChange, CHANGE);
    attachInterrupt(encB, handleEncoderChange, CHANGE);
    attachInterrupt(encC, handleEncoderChange, CHANGE);

    do {
         curEncState = digitalRead(encA) | (digitalRead(encB) << 1) | (digitalRead(encC) << 2);
    }
    while (revEncMap[curEncState] == 100);
    Serial.printf("curEncState: %d\n", curEncState);
        
    // Serial.printf("done setting up encoder. ticks: %d, prevEncoderState: %hhx\n", encoderTicks, prevEncoderState);

}

void setup() {
    Serial.begin(115200);
    delay(1000); 
    Serial.printf("hi");
    setupEncoder();

}

void loop() {
    if (printFlag) {
        Serial.print("Count: ");
        Serial.println(getEncoderCount());
        Serial.print("A: ");
        Serial.println(digitalRead(encA));
        Serial.print("B: ");
        Serial.println(digitalRead(encB));
        Serial.print("C: ");
        Serial.println(digitalRead(encC));
        printFlag = false;
    }
    // delay(100);
}

