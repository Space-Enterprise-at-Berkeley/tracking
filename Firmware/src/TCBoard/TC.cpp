#include "TC.h"

namespace TC {
  Comms::Packet tcPacket = {.id = 2};
  MAX31855* tcs = new MAX31855[8];
  int sendRate = 50 * 1000; // 100ms
  SPIClass *vspi;
  bool abortOn = false;
  uint32_t abortTemp = 200;
  uint32_t abortTime = 500;
  ulong abortStart[8] = {0,0,0,0,0,0,0,0};

  void init() {
    //Serial.println("Initializing TCs...");
    uint8_t chipSelectPins[] = { 16, 17, 18, 19, 20, 21, 26, 33 };
    vspi = new SPIClass(HSPI);
    vspi->begin(36, 37, 4, 5);
    vspi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    //Serial.println("SPI initialized");
    for (uint8_t i = 0; i < 8; i ++) {
      tcs[i] = MAX31855();
      Serial.print("yeeyy");
      tcs[i].init(vspi, chipSelectPins[i]);
      //Serial.print("TC ");
      //Serial.print(i);
      //Serial.println(" initialized");
    }
    //Serial.println("TCs initialized");
  }

  void setAbort(bool on, uint32_t temp, uint32_t abortTime){
    abortOn = on;
    abortTemp = temp;
    abortTime = abortTime;
  }

  void setAbort(bool on){
    abortOn = on;
  }

  float sample(uint8_t index) {
    if (abortOn){
      float temp = tcs[index].readCelsius();
      if (temp > abortTemp){
        if (abortStart[index] == 0){
          abortStart[index] = millis();
        }
        else if (millis() - abortStart[index] > abortTime){
          Comms::sendAbort(HOTFIRE, ENGINE_OVERTEMP);
        }
      }
      else{
        abortStart[index] = 0;
      }
    }
    return tcs[index].readCelsius();
  }

  uint32_t task_sampleTCs() {
    tcPacket.len = 0;
    for (uint8_t i = 0; i < 8; i ++) {
      Comms::packetAddFloat(&tcPacket, sample(i));
    }
    Comms::emitPacketToGS(&tcPacket);
    return sendRate;
  }

  void print_sampleTCs(){
    for (uint8_t i = 0; i < 8; i ++) {
      Serial.print(sample(i));
      Serial.print(" ");
    }
    Serial.println();
  }
}