#include <Arduino.h>
#include <Common.h>
//#include <EspComms.h>
#include <TeensyComms.h>
#include "Rotator.h"
#include "HAL.h"

Task taskTable[] = {
  {Rotator::printEncoder, 0, true},
};

#define TASK_COUNT (sizeof(taskTable) / sizeof (struct Task))

void setup() {
  // setup stuff here
  Serial.begin(115200);
  HAL::init();
  Serial.printf("hii!!\n");
  //Comms::init()
  Serial.printf("setup comms!\n");
  HAL::setupEncoders();
  HAL::resetEncoders();
  // TVC::init();
  Serial.printf("setup other stuff!\n");  

  // Rotator::setUp();
  
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
    //Comms::processWaitingPackets();
  }
}

void loop() {} // unused