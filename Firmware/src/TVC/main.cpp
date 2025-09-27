#include <Arduino.h>
#include <Common.h>
//#include <EspComms.h>
#include <TeensyComms.h>
#include "TVC.h"
#include "HAL.h"



Task taskTable[] = {
  {TVC::zero, 0, false}, 
  {TVC::moveTVC, 0, true},
  {TVC::flowSequence, 0, false},
};

#define TASK_COUNT (sizeof(taskTable) / sizeof (struct Task))

void zeroTVC(Comms::Packet packet, uint8_t ip) { 
  Serial.printf("zeroing...\n");
  if (taskTable[0].enabled) return; 
  taskTable[0].enabled = true;
  taskTable[0].nexttime = micros();
}

uint32_t ctr = 0;

void packetcounter(Comms::Packet packet, uint8_t ip) {
  ctr ++;
  Serial.printf("ctr: %d\n", ctr);
}

void startLaunch(Comms::Packet packet, uint8_t ip) {
  Serial.printf("hihii starting launch\n");
  taskTable[2].enabled = true;
  taskTable[2].nexttime = micros();
}

void stopTVCAll(Comms::Packet packet, uint8_t ip) {
  taskTable[2].enabled = false;
  TVC::stopTVC(packet, ip);
}

void setup() {
  // setup stuff here
  Serial.begin(115200);
  HAL::init();
  Serial.printf("hii!!\n");
  //Comms::init();
  Serial.printf("setup comms!\n");
  HAL::setupEncoders();
  HAL::resetEncoders();
  TVC::init();
  Serial.printf("setup other stuff!\n");  
  // Comms::registerCallback(102, TVC::enableCircle);
  Comms::registerCallback(102, startLaunch);
  Comms::registerCallback(103, zeroTVC);
  Comms::registerCallback(104, stopTVCAll);
  Comms::registerCallback(105, TVC::setRadius);
  Comms::registerCallback(106, TVC::setAngle);
  Comms::registerCallback(200, packetcounter);
  Comms::registerCallback(150, startLaunch);
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

