#include <Arduino.h>


volatile int encoderTicks = 0;

int32_t numReads = 0;


const int encA_0 = 34; //encoder A blue
const int encB_0 = 21; //encoder B red
const int encC_0 = 20; //encoder C green


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


void risingA() {
    if (digitalRead(encC)) {
        encoderTicks += 1;
    } i
    else {
        encoderTicks -= 1;
    }
    
}

void risingB() {
    if (digitalRead(encA)) {
        encoderTicks += 1;
    } else {
        encoderTicks -= 1;
    } 
}

void risingC() {
    if (digitalRead(encB)) {
        encoderTicks += 1;
    } else {
        encoderTicks -= 1;
    } 
}

void fallingA() {
    if (digitalRead(encB)) {
        encoderTicks += 1;
    } else {
        encoderTicks -= 1;
    }  
}

void fallingB() {
    if (digitalRead(encC)) {
        encoderTicks += 1;
    } else {
        encoderTicks -= 1;
    }  
}

void fallingC() {
    if (digitalRead(encA)) {
        encoderTicks += 1;
    } else {
        encoderTicks -= 1;
    }  
}

void changeA() {
    if (digitalRead(encA)) {
        risingA();
    } else {
        fallingA();
    }
}

void changeB() {
    if (digitalRead(encB)) {
        risingB();
    } else {
        fallingB();
    }
}

void changeC() {
    if (digitalRead(encC)) {
        risingC();
    } else {
        fallingC();
    }
}

void setupEncoder() {
    pinMode(encA, INPUT);
    pinMode(encB, INPUT);
    pinMode(encC, INPUT);

    // attachInterrupt(encA, changeA, CHANGE);
    attachInterrupt(encB, changeB, CHANGE);
    attachInterrupt(encC, changeC, CHANGE);
    // Serial.printf("done setting up encoder. ticks: %d, prevEncoderState: %hhx\n", encoderTicks, prevEncoderState);

}

void setup() {
    Serial.begin(115200);
    delay(1000); 
    setupEncoder();
}

void loop() {
    Serial.print("Count: ");
    Serial.println(getEncoderCount());
    Serial.print("A: ");
    Serial.println(digitalRead(encA));
    Serial.print("B: ");
    Serial.println(digitalRead(encB));
    Serial.print("C: ");
    Serial.println(digitalRead(encC));
    delay(100);
}

