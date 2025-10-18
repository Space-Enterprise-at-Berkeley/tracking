#include <Arduino.h>
#include <Common.h>
//#include <EspComms.h>
#include <TeensyComms.h>
#include "Rotator.h"
#include "HAL.h"

Task taskTable[] = {
  {HAL::printEncoder_0, 0, true},
};

#define TASK_COUNT (sizeof(taskTable) / sizeof (struct Task))

//test to see if packet reading works
void func(Comms::Packet packet, uint8_t ip){
  Serial.print(Comms::packetGetFloat(&packet,0));
  Serial.print(Comms::packetGetFloat(&packet,4));
}

//helper function to call setTargetSetpoint(<value from packet>)
void callSetTargetSetpoint(Comms::Packet packet, uint8_t ip){
    Rotator::setTargetSetpoint(Comms::packetGetUint32(&packet, 0));
  }



void setup() {
  // setup stuff here
  Serial.begin(115200);
  //HAL::init();
  Serial.printf("hii!!\n");
  //Comms::init()
  Serial.printf("setup comms!\n");
  //HAL::setupEncoders();
  //HAL::resetEncoders();
  // TVC::init();
  Serial.printf("setup other stuff!\n");  
  Rotator::setUp();

  //if number detected, do function
  
  // Comms::registerCallback(102, TVC::enableCircle);
  // Comms::registerCallback(102, startLaunch);
  // Comms::registerCallback(103, zeroTVC);
  // Comms::registerCallback(104, stopTVCAll);
  // Comms::registerCallback(105, TVC::setRadius);
  // Comms::registerCallback(106, TVC::setAngle);
  // Comms::registerCallback(200, packetcounter);
  // Comms::registerCallback(150, startLaunch);
  // Comms::registerCallback(5, TVC::setTVCMode);
  // Comms::registerCallback(101, joystickCommand);
  // Comms::registerCallback(2, TVC::printEncoders);

  //for testing purposes
  Comms::registerCallback(100, func);

  

  Comms::registerCallback(101, callSetTargetSetpoint);

  Serial.printf("Setup complete\n");

  while(1) {
    // main loop here to avoid arduino overhead
    for(uint32_t i = 0; i < TASK_COUNT; i++) { // for each task, execute if next time >= current time
      uint32_t ticks = micros(); // current time in microseconds
      if (taskTable[i].nexttime - ticks > UINT32_MAX / 2 && taskTable[i].enabled) {
        uint32_t delayoftask = taskTable[i].taskCall();
        if (delayoftask == 0) {
          taskTable[i].enabled = false;
        } else {
          taskTable[i].nexttime = ticks + delayoftask;
        }
      }
    }
    // delayMicroseconds(10);
    Comms::processWaitingPackets();
  }
}

void loop() {} // unused