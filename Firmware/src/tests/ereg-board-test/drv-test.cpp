#include <Arduino.h>
#include <SPI.h>
#include <math.h>
//regs



#define ENC_A 14
#define ENC_B 15
#define ENC_C 16

#define LIMIT_1 40
#define LIMIT_2 41


#define INHA 1
#define INLA 4
#define INHB 2
#define INLB 5
#define INHC 3
#define INLC 6

#define MOTOR_MISO 8
#define MOTOR_MOSI 9
#define MOTOR_SCLK 7

#define ETH_MISO 37
#define ETH_MOSI 36
#define ETH_SCLK 38

#define ETH_INTn 35

#define DRV_EN 11
#define DRV_FAULT 12

#define DRV_CS 10
#define MADC_CS 13
#define ETH_CS 39
#define PTADC_CS 21

#define RS422_TX 18
#define RS422_RX 17

#define TEMP1 19
#define TEMP2 20

//endregs
SPIClass *spi = NULL;
int spiclk = 1000000;
bool drv_fault = false;
void sendSpiCommand(int8_t* data, int8_t len, int8_t csPin);
void handleFaultInterrupt() {
    drv_fault = true;
}
void processCurrent();
float curA, curB, curC;

int pwmFreq = 50000;
int pwmRes = 8;
int pwmChan = 0;

int motorCurrentCtr = 0;

int8_t spiBuff[2];
void readRegister(int8_t addr);
void writeRegister(int8_t addr);
float readCurrent(int8_t chan);
void disableDRV() {
    digitalWrite(DRV_EN, LOW);
}
void enableDRV() {
    digitalWrite(DRV_EN, HIGH);
}
void die() {
    Serial.printf("dead\n");
    disableDRV();
    while (1) {
        int f = 69*420;
    }
}
void getDRVFault() {
    spiBuff[0] = 0b00000000;
    spiBuff[1] = 0b00000000;
    sendSpiCommand(spiBuff, 2, DRV_CS);
}
uint32_t encoderTicks = 0;
void risingEncoderA() {
    if (!(digitalRead(ENC_B))) {
        encoderTicks++;
    } else {
        encoderTicks--;
    }
}

uint32_t lastEncoderReport = 0;

void handleFault() {
    Serial.printf("drv fault\n");
    readRegister(0);
    Serial.printf("reg 0: %hhx; %hhx\n", spiBuff[0], spiBuff[1]);
    readRegister(1);
    Serial.printf("reg 1: %hhx; %hhx\n", spiBuff[0], spiBuff[1]);
    drv_fault = false;
}

float getTemperature() {
    float volt = readCurrent(3);
    volt = volt / 5;
    float R = (10000 * volt) / (1 - volt);
    Serial.printf("R: %f, V: %f\n", R, volt);
    float beta = 3380;
    float temp = beta / (log((R / (10000 * exp(-1*(beta/298.15))))));
    temp = temp - 273.15;
    return temp;
}

void setDRVSpeed(int i) {
    if (i < 150) {
        ledcWrite(0, i);
    } else {
        ledcWrite(0, 0);
    }
}
int startTime;
int testSpeedCtr = 0;
int lastCurrentTime = 0;
void setup() {

    Serial.begin(115200);
    Serial.printf("hi!! Starting in 3\n");
    delay(3000);

    spi = new SPIClass(HSPI);
    spi->begin(MOTOR_SCLK, MOTOR_MISO, MOTOR_MOSI);

    pinMode(DRV_CS, OUTPUT);
    digitalWrite(DRV_CS, HIGH);

    pinMode(MADC_CS, OUTPUT);
    digitalWrite(MADC_CS, HIGH);

    pinMode(DRV_FAULT, INPUT_PULLUP);
    attachInterrupt(DRV_FAULT, handleFaultInterrupt, FALLING);

    pinMode(DRV_EN, OUTPUT);
    digitalWrite(DRV_EN, LOW);

    pinMode(ENC_A, INPUT);
    pinMode(ENC_B, INPUT);
    attachInterrupt(ENC_A, risingEncoderA, RISING);
    // while (true) {
    //     Serial.printf("enc: %d\n", encoderTicks);
    //     delay(100);
    // }

    // attachInterrupt(ENC_A, fallingEncoderA, FALLING);
    // attachInterrupt(ENC_B, risingEncoderB, RISING);
    // attachInterrupt(ENC_B, fallingEncoderB, FALLING);

    pinMode(TEMP1, INPUT);
    pinMode(TEMP2, INPUT);
    // pinMode(INHA, OUTPUT);
    // digitalWrite(INHA, LOW);

    ledcSetup(pwmChan, pwmFreq, pwmRes);
    ledcAttachPin(INHA, 0);

    pinMode(INHC, OUTPUT);
    digitalWrite(INHC, LOW);

    pinMode(INLC, OUTPUT);
    digitalWrite(INLC, LOW);

    Serial.printf("motor temperature: %3.1f\n", getTemperature());
    delay(100);

    Serial.printf("Turning on DRV\n");
    enableDRV();
    //set driver control
    readRegister(2);
    spiBuff[1] = 0b11000000;
    writeRegister(2);
    readRegister(2);

    if (spiBuff[0] != 0x00 && spiBuff[1] != 0xc0) {
        Serial.printf("reg 2 bad :( %hhx, %hhx\n", spiBuff[0], spiBuff[1]);
        die();
    } 
    // delay(100000);

    Serial.printf("sending command:\n");

    //set CSA
    delay(100);
    // // Serial.printf("read 6\n");
    // readRegister(6);
    // spiBuff[1] = 0b10010010;
    // // // Serial.printf("write 6\n");
    // writeRegister(6);
    // delay(200);
    // Serial.printf("read 6\n");
    readRegister(6);
    spiBuff[1] = 0b10000010; 
    writeRegister(6);
    readRegister(6);
    if (spiBuff[0] != 0x02 && spiBuff[1] != 0x80) {
        Serial.printf("reg 6 bad :(\n");
        die();
    } 

    // set gate drive HS 
    readRegister(3);
    spiBuff[1] = 0b11111111; //1000mA, 2000mA
    writeRegister(3);
    readRegister(3);
    if (spiBuff[0] != 0x03 && spiBuff[1] != 0xFF) {
        Serial.printf("reg 3 bad :( %hhx, %hhx\n", spiBuff[0], spiBuff[1]);
        die();
    }

    //set gate drive LS
    readRegister(4);
    spiBuff[1] = 0b11111111;
    writeRegister(4);
    readRegister(4);
    if (spiBuff[0] != 0x07 && spiBuff[1] != 0x84) {
        Serial.printf("reg 4 bad :(\n");
        die();
    }

    //set OCP
    readRegister(5);
    spiBuff[1] = 0b00110101; // OC to latch fault, OC deglitch to 8us, Vds trip to 0.45V
    writeRegister(5);
    readRegister(5);
    if (spiBuff[0] != 0x01 && spiBuff[1] != 0x35) {
        Serial.printf("reg 5 bad :(\n");
        die();
    }






    digitalWrite(INHC, LOW);
    digitalWrite(INLC, HIGH);

    Serial.printf("starting in 5: \n");
    getDRVFault();
    drv_fault = false;
    Serial.printf("clearing fault; fault flags: %hhx, %hhx\n", spiBuff[0], spiBuff[1]);
    delay(5000);
    Serial.printf("Starting!\n");

    // ledcWrite(pwmChan, 7);
    // delay(40);
    // ledcWrite(pwmChan, 0);
    // delay(1000);

    // for (int i = 5; i < 40; i++) {
    //     ledcWrite(pwmChan, i);
    //     delay(100);
    //     if (drv_fault) {
    //         handleFault();
    //     }
    // }

    // for (int i = 40; i > 5; i--) {
    //     ledcWrite(pwmChan, i);
    //     delay(100);
    //     if (drv_fault) {
    //         handleFault();
    //     }
    // }

    // digitalWrite(INHC, HIGH);

    // for (int i = 5; i < 40; i++) {
    //     ledcWrite(pwmChan, i);
    //     delay(100);
    //     if (drv_fault) {
    //         handleFault();
    //     }
    // }

    // for (int i = 40; i > 5; i--) {
    //     ledcWrite(pwmChan, i);
    //     delay(100);
    //     if (drv_fault) {
    //         handleFault();
    //     }
    // }
    // int power = 20;
    // ledcWrite(pwmChan, power);
    // for (int i = 0; i < 30; i++) {
    //     delay(200);
    //     digitalWrite(INHC, i % 2);
    //     if (drv_fault) {
    //         handleFault();
    //     }
    //     digitalWrite(pwmChan, 0);
    //     digitalWrite(INLC, HIGH);
    //     delay(50);
    //     digitalWrite(INLC, LOW);
    //     digitalWrite(pwmChan, power);
    // }
    // ledcWrite(pwmChan, 0);
    // disableDRV();

    startTime = millis();
    enableDRV();


    getDRVFault();
    Serial.printf("clearing fault; fault flags: %hhx, %hhx\n", spiBuff[0], spiBuff[1]);


}
int8_t motorPower(int setpoint) {
    // float p = 0.5;
    // float power = (setpoint - encoderTicks) * p;
    // if (power > 75) {
    //     power = 75;
    // } else if (power < -75) {
    //     power = -75;
    // }
    // return (int8_t) power;
    return 10;
    
}
int8_t power;
void loop() {
    if (drv_fault == true) {
        digitalWrite(DRV_EN, LOW);
        drv_fault = false;
        getDRVFault();
        Serial.printf("drv fault :( %hhx; %hhx\n", spiBuff[0], spiBuff[1]);
        die();
    }


    int sp = ((millis() - startTime) / 1000) * 50;
    if ((millis() - startTime) > 20000) {
        die();
    } else {
        
        // testSpeedCtr = ((millis() - startTime) / 100);
        // setDRVSpeed(testSpeedCtr + 30);
        power = motorPower(sp);
        if (power < 0) {
            power = -1*power;
            digitalWrite(INHC, 0);
        }  else {
            digitalWrite(INHC, 1);
        }
        ledcWrite(0, power);

        
    }

    // if ((millis() - lastCurrentTime) > 50) {
    //     float currA = readCurrent(0);
    //     float currB = readCurrent(1);
    //     float currC = readCurrent(2);
    //     Serial.printf("Speed %d. current A: %1.3f, B: %1.3f, C: %1.3f\n", testSpeedCtr, currA, currB, currC);
    // }
    if ((micros() - 100) > lastCurrentTime) {
        processCurrent();
        lastCurrentTime = micros();
    }

    if (motorCurrentCtr % 500 == 0) {
        // Serial.printf("ctr: %d, current: %1.2f, time: %d\n", motorCurrentCtr, curA, millis());
    } 
    if ((millis() - lastEncoderReport) > 300) {
        // Serial.printf("RPM: %d\n", (int)(((float)encoderTicks) * 14.2857));
        // encoderTicks = 0;
        // lastEncoderReport = millis();
        Serial.printf("Encoder: %d\n", encoderTicks);
        float v1 = ((((float) analogRead(TEMP1)) * (3.3 / 4096.0)) - 0.4) / (0.0195);
        float v2 = ((((float) analogRead(TEMP2)) * (3.3 / 4096.0)) - 0.4) / (0.0195);
        // float motorTemp = getTemperature();
        Serial.printf("T1: %f, T2: %f\n", v1, v2);
        Serial.printf("speed: %d, setpoint: %d\n", power, sp);
        lastEncoderReport = millis();
    }


}





void readRegister(int8_t addr) {
    spiBuff[0]  = 0x00;
    spiBuff[1] = 0x00;
    spiBuff[0] |= 0b10000000; //set read mode
    addr &= 0x0F;
    spiBuff[0] |= (addr << 3);
    sendSpiCommand(spiBuff, 2, DRV_CS);
}

void writeRegister(int8_t addr) {
    spiBuff[0] &= 0b01111111; //set write mode
    addr &= 0x0F;
    spiBuff[0] |= (addr << 3);
    sendSpiCommand(spiBuff, 2, DRV_CS);
}

void sendSpiCommand(int8_t *data, int8_t len, int8_t csPin) {
    if (len == 2) {
        // Serial.printf("Transferring %hhx %hhx; \n", data[0], data[1]);
    }
    spi->beginTransaction(SPISettings(spiclk, MSBFIRST, SPI_MODE1));
    digitalWrite(csPin, LOW);
    spi->transfer((uint8_t*)data, len);
    spi->endTransaction();
    digitalWrite(csPin, HIGH);
    if (len == 2) {
        // Serial.printf("received %hhx %hhx\n", data[0], data[1]);
    }
}


float readCurrent(int8_t chan) {
    if ((chan > 3) || (chan < 0)) {
        Serial.printf("bad channel index\n");
        return 0;
    }
    spiBuff[0] = 0;
    spiBuff[0] |= (chan << 3);
    spiBuff[0] &= 0b00011000;
    spiBuff[1] = 0;
    spi->beginTransaction(SPISettings(spiclk, MSBFIRST, SPI_MODE0));
    digitalWrite(MADC_CS, LOW);
    spi->transfer((uint8_t*)spiBuff, 2);
    spi->endTransaction();
    digitalWrite(MADC_CS, HIGH);
    // Serial.printf("pt channel %d: %hhx %hhx\n", chan, spiBuff[0], spiBuff[1]);
    int16_t val = ((spiBuff[0] & 0b00001111) << 8) + spiBuff[1];
    
    float f = (((float) val) / 4096) * 5.0;
    f = (5 - f) / (20*0.005);
    return f;
}

void processCurrent() {

    curA = readCurrent(0);
    curB = readCurrent(1);
    curC = readCurrent(2);
    motorCurrentCtr++;
}