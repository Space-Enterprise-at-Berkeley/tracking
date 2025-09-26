#include <Common.h>
#include <EspComms.h>
#include <Arduino.h>
#include "ReadPower.h"

#include "AC.h"
#include "ChannelMonitor.h"
#include <MCP23008.h>
#include <Wire.h>

//Actuators
enum Actuators {
  //AC1
  IGNITER = 7,
  BREAKWIRE = 1,

  ARM_VENT = 2,
  ARM = 3,
  LOX_MAIN_VALVE = 4,
  FUEL_MAIN_VALVE = 5,

  //AC2
  N2_FILL = 0,
  N2_VENT = 1,
  N2_FLOW = 2,
  N2_RQD = 3,

  LOX_VENT_RBV = 4,
  FUEL_VENT_RBV = 5,
  LOX_GEMS = 6,
  FUEL_GEMS = 7,
};


Comms::Packet heart = {.id = HEARTBEAT, .len = 0};
//uint8_t counter = 0;
uint32_t task_heartbeat() {
  heart.len = 0;
  Comms::packetAddUint8(&heart, ID);
  //Comms::packetAddUint8(&heart, counter++);
  Comms::emitPacketToGS(&heart);
  // Serial.println("Heartbeat");
  return 1000 * 1000; //1 sec
}

Mode systemMode = HOTFIRE;
uint8_t launchStep = 0;
uint32_t flowLength;

uint32_t launchDaemon(){
  if (ID == AC1){
    switch(launchStep){
      case 0:
      {
        // Light igniter and wait for 2.0 sec
        if (systemMode == HOTFIRE || systemMode == LAUNCH){
          Serial.println("launch step 0, igniter on");
          AC::actuate(IGNITER, AC::ON, 0);
          launchStep++;
          return 2000 * 1000;
        } else {
          Serial.println("launch step 0, not hotfire, skip");
          launchStep++;
          return 10;
        }
        
      }
      case 1:
      {
        if (systemMode == HOTFIRE || systemMode == LAUNCH){
          //igniter off
          Serial.println("launch step 1, igniter off");
          AC::actuate(IGNITER, AC::OFF, 0);

          //Throw abort if breakwire still has continuity
          ChannelMonitor::readChannels();
          if (ChannelMonitor::isChannelContinuous(BREAKWIRE)){
            Serial.println("breakwire still has continuity, aborting");
/*             Comms::Packet abort = {.id = 43, .len = 0};
            Comms::packetAddUint8(&abort, systemMode);
            Comms::packetAddUint8(&abort, BREAKWIRE_NO_BURNT);
            Comms::emitPacket(&abort, ALL); */
            Comms::sendAbort(systemMode, BREAKWIRE_NO_BURNT);
            launchStep = 0;
            return 0;
          }
        }

        //send packet for eregs
        Comms::Packet launch = {.id = STARTFLOW, .len = 0};
        Comms::packetAddUint8(&launch, systemMode);
        Comms::packetAddUint32(&launch, flowLength);
        Comms::emitPacketToAll(&launch);

        //arm and open main valves
        AC::actuate(ARM, AC::ON, 0);
        AC::delayedActuate(LOX_MAIN_VALVE, AC::ON, 0, 100);
        AC::delayedActuate(FUEL_MAIN_VALVE, AC::ON, 0, 150);
        AC::delayedActuate(ARM, AC::OFF, 0, 2000);
        AC::delayedActuate(ARM_VENT, AC::ON, 0, 2050);
        AC::delayedActuate(ARM_VENT, AC::OFF, 0, 2500);
        launchStep++;
        return flowLength * 1000;
      }
      case 2:
      {
        //end flow

        //end packet for eregs
        Comms::Packet endFlow = {.id = ENDFLOW, .len = 0};
        Comms::emitPacketToAll(&endFlow);

        //arm and close main valves
        AC::actuate(LOX_MAIN_VALVE, AC::OFF, 0);
        AC::actuate(FUEL_MAIN_VALVE, AC::OFF, 0);
        AC::delayedActuate(ARM, AC::ON, 0, 100);
        AC::delayedActuate(ARM, AC::OFF, 0, 2000);
        AC::delayedActuate(ARM_VENT, AC::ON, 0, 2050);
        AC::delayedActuate(ARM_VENT, AC::OFF, 0, 2500);



        //open lox and fuel gems via abort only to AC2
        delay(100); // temporary to give time to eth chip to send the packet
        // Comms::Packet openGems = {.id = ABORT, .len = 0};
        // Comms::packetAddUint8(&openGems, systemMode);
        // Comms::packetAddUint8(&openGems, LC_UNDERTHRUST);
        // Comms::emitPacket(&openGems, AC2);

        launchStep = 0;
        return 0;  
      }
    }
  }
  return 0;
}

Task taskTable[] = {
  {launchDaemon, 0, false}, //do not move from index 0
  {AC::actuationDaemon, 0, true},
  {AC::task_actuatorStates, 0, true},
  {ChannelMonitor::readChannels, 0, true},
  {Power::task_readSendPower, 0, true},
  // {AC::task_printActuatorStates, 0, true},
  {task_heartbeat, 0, true},
};

#define TASK_COUNT (sizeof(taskTable) / sizeof (struct Task))

// ABORT behaviour - 
// switch(abort_reason)
// case TANK OVERPRESSURE:
//    1. Open LOX and FUEL GEMS  
//    2. Open LOX and FUEL Vent RBVs
//    3. Leave Main Valves in current state
// case ENGINE OVERTEMP: 
//    1. Open LOX and FUEL GEMS
//    2. ARM and close LOX and FUEL Main Valves 
// case LC UNDERTHRUST:
//    1. Open LOX and FUEL GEMS
//    2. ARM and close LOX and FUEL Main Valves, fuel first by 0.5 secs to reduce flame.
// case MANUAL/DASHBOARD ABORT:
//    1. Open LOX and FUEL GEMS
//    2. ARM and close LOX and FUEL Main Valves
// case IGNITER NO CONTINUITY:
//    1. Open LOX and FUEL GEMS
//    2. ARM and close LOX and FUEL Main Valves
// case BREAKWIRE CONTINUITY:
//    1. Open LOX and FUEL GEMS
//    2. ARM and close LOX and FUEL Main Valves

void onAbort(Comms::Packet packet, uint8_t ip) {
  Mode systemMode = (Mode)packetGetUint8(&packet, 0);
  AbortReason abortReason = (AbortReason)packetGetUint8(&packet, 1);
  Serial.println("abort received");
  Serial.println(abortReason);
  Serial.println(systemMode);

  if (launchStep != 0){
    Serial.println("mid-flow abort");
    launchStep = 0;
    AC::actuate(IGNITER, AC::OFF, 0);
    taskTable[0].enabled = false;
  }


  switch(abortReason) {
    case TANK_OVERPRESSURE:
      if(ID == AC1){
        //leave main valves in current state
      } else if (ID == AC2){
        //open lox and fuel gems
        AC::actuate(LOX_GEMS, AC::ON, 0);
        AC::actuate(FUEL_GEMS, AC::ON, 0);
        //open lox and fuel vent rbvs
        //AC::actuate(LOX_VENT_RBV, AC::RETRACT_FULLY, 0);
        //AC::actuate(FUEL_VENT_RBV, AC::RETRACT_FULLY, 0);
        AC::actuate(N2_FLOW, AC::RETRACT_FULLY, 0);
      }
      break;
    case ENGINE_OVERTEMP:
      if(ID == AC1){
        //arm and close main valves   
        AC::actuate(LOX_MAIN_VALVE, AC::OFF, 0);
        AC::actuate(FUEL_MAIN_VALVE, AC::OFF, 0);
        AC::delayedActuate(ARM, AC::ON, 0, 100);
        AC::delayedActuate(ARM, AC::OFF, 0, 2000);
        AC::delayedActuate(ARM_VENT, AC::ON, 0, 2050);
        AC::delayedActuate(ARM_VENT, AC::OFF, 0, 2500);
      } else if (ID == AC2){
        //open lox and fuel gems
        AC::actuate(LOX_GEMS, AC::ON, 0);
        AC::actuate(FUEL_GEMS, AC::ON, 0);
        AC::actuate(N2_FLOW, AC::RETRACT_FULLY, 0);
      }
      break;
    case LC_UNDERTHRUST:
      if(ID == AC1){
        //arm and close main valves
        AC::actuate(LOX_MAIN_VALVE, AC::OFF, 0);
        AC::actuate(FUEL_MAIN_VALVE, AC::OFF, 0);
        AC::delayedActuate(ARM, AC::ON, 0, 100);
        AC::delayedActuate(ARM, AC::OFF, 0, 2000);
        AC::delayedActuate(ARM_VENT, AC::ON, 0, 2050);
        AC::delayedActuate(ARM_VENT, AC::OFF, 0, 2500);

      } else if (ID == AC2){
        //open lox and fuel gems
        AC::actuate(LOX_GEMS, AC::ON, 0);
        AC::actuate(FUEL_GEMS, AC::ON, 0);
        AC::actuate(N2_FLOW, AC::RETRACT_FULLY, 0);
      }    
      break;
    case MANUAL_ABORT:
      if (ID == AC2){
        //open lox and fuel gems
        Serial.println("manual abort opening gems");
        AC::actuate(LOX_GEMS, AC::ON, 0);
        AC::actuate(FUEL_GEMS, AC::ON, 0);
      }
    case IGNITER_NO_CONTINUITY:
    case BREAKWIRE_NO_CONTINUITY:
    case BREAKWIRE_NO_BURNT:
      if(ID == AC1){
        //arm and close main valves
        // AC::actuate(ARM, AC::ON, 0);
        // AC::actuate(LOX_MAIN_VALVE, AC::OFF, 0);
        // AC::actuate(FUEL_MAIN_VALVE, AC::OFF, 0);
        // AC::delayedActuate(ARM, AC::OFF, 0, 1000);
        // AC::delayedActuate(ARM_VENT, AC::ON, 0, 1050);
        // AC::delayedActuate(ARM_VENT, AC::OFF, 0, 1500);
      } else if (ID == AC2){
        //open lox and fuel gems
        AC::actuate(LOX_GEMS, AC::ON, 0);
        AC::actuate(FUEL_GEMS, AC::ON, 0);
      }
      break;
  }
}

void onEndFlow(Comms::Packet packet, uint8_t ip) {
  if (ID == AC2){
    //open lox and fuel gems
    AC::actuate(LOX_GEMS, AC::ON, 0);
    AC::actuate(FUEL_GEMS, AC::ON, 0);
  }
}


void onLaunchQueue(Comms::Packet packet, uint8_t ip){
  if(ID == AC1){
    if(launchStep != 0){
      Serial.println("launch command recieved, but launch already in progress");
      return;
    }
    systemMode = (Mode)packetGetUint8(&packet, 0);
    flowLength = packetGetUint32(&packet, 1);
    Serial.println("System mode: " + String(systemMode));
    Serial.println("Flow length: " + String(flowLength));

    if (systemMode == LAUNCH || systemMode == HOTFIRE){
      // check igniter and breakwire continuity
      // if no continuity, abort
      // if continuity, start launch daemon
      ChannelMonitor::readChannels();
      if (!ChannelMonitor::isChannelContinuous(IGNITER)){
        Comms::sendAbort(systemMode, IGNITER_NO_CONTINUITY);
        return;
      } else if (!ChannelMonitor::isChannelContinuous(BREAKWIRE)){
        Comms::sendAbort(systemMode, BREAKWIRE_NO_CONTINUITY);
        return;
      }
    } 

    //start launch daemon
    launchStep = 0;
    taskTable[0].enabled = true;
    taskTable[0].nexttime = micros(); // this has to be here for timestamp overflowing
    Serial.println("launch command recieved, starting sequence");

  }
}

void setup() {
  // setup stuff here
  Comms::init(); // takes care of Serial.begin()
  AC::init();
  initWire();
  Power::init();
  ChannelMonitor::init(41, 42, 47, 4, 5);
  //abort register
  Comms::registerCallback(ABORT, onAbort);
  //launch register
  Comms::registerCallback(LAUNCH_QUEUE, onLaunchQueue);
  //endflow register
  Comms::registerCallback(ENDFLOW, onEndFlow);


  for (int i = 0; i < 8; i++) {
    ChannelMonitor::getMCP1().digitalWrite(i, LOW); 
    ChannelMonitor::getMCP2().digitalWrite(i, LOW); 
  }
      
  for (int i = 0; i < 8; i+=2) {
    ChannelMonitor::getMCP1().digitalWrite(i, HIGH); 
    delay(250);
  }

  for (int i = 0; i < 8; i++) {
    ChannelMonitor::getMCP1().digitalWrite(i, LOW); 
  }

  for (int i = 1; i < 8; i+=2) {
    ChannelMonitor::getMCP1().digitalWrite(i, HIGH); 
    delay(250);
  }

  for (int i = 0; i < 8; i+=2) {
    ChannelMonitor::getMCP2().digitalWrite(i, HIGH); 
    delay(250);
  }

  for (int i = 0; i < 8; i++) {
    ChannelMonitor::getMCP2().digitalWrite(i, LOW); 
  }

  for (int i = 1; i < 8; i+=2) {
    ChannelMonitor::getMCP2().digitalWrite(i, HIGH); 
    delay(250);
  }
 
  
  uint32_t ticks;
  uint32_t nextTime;

  
  while(1) {
    // main loop here to avoid arduino overhead
    for(uint32_t i = 0; i < TASK_COUNT; i++) { // for each task, execute if next time >= current time
      ticks = micros(); // current time in microseconds
      if (taskTable[i].nexttime - ticks > UINT32_MAX / 2 && taskTable[i].enabled) {
        nextTime = taskTable[i].taskCall();
        if (nextTime == 0) {
          taskTable[i].enabled = false;
        } else {
          taskTable[i].nexttime = ticks + nextTime;
        }
      }
    }
    Comms::processWaitingPackets();
  }
}

void loop() {} // unused