#include <Arduino.h>
#include <Common.h>
//#include <EspComms.h>
#include <TeensyComms.h>
#include "Rotator.h"
#include "HAL.h"


Task taskTable[] = {
  {HAL::pushToBuffers, 0, true},
  {Rotator::updateAndMove, 0, true},
  {Tracking::maintenance, 0, true}
  //{sendStateFlags, 0, true}
};

#define TASK_COUNT (sizeof(taskTable) / sizeof (struct Task))

uint32_t sendStateFlags(){
  return 10 * 1000 * 1000;
};

/*void switchModes(Comms::Packet packet, uint8_t ip){
  Rotator::switchModes(Comms::packetGetUint8(&packet, 0));
}*/

void setup() {
  // setup stuff here
  Serial.begin(115200);
  //HAL::init();
  Serial.printf("hii!!\n");
  Comms::init();
  Serial.printf("setup comms!\n");
  //HAL::setupEncoders();
  //HAL::resetEncoders();
  // TVC::init();
  Serial.printf("setup other stuff!\n");  
  Rotator::init();
  HAL::init();

  Serial.printf("Setup complete\n");
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
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
} // arduino overhead is fake, having to upload twice is real