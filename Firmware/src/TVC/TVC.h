#pragma once

#include <Arduino.h>
//#include <EspComms.h>
#include <TeensyComms.h>
#include <PIDController.h>
namespace TVC {

    void init();
    void definePosition(Comms::Packet defPos, uint8_t id);
    void defineSpeeds(Comms::Packet defSpeeds, uint8_t id);

    uint32_t moveTVC();
    void enableCircle(Comms::Packet statePacket, uint8_t ip); 
    void setMode(int mode);
    void setTVCMode(Comms::Packet statePacket, uint8_t ip);
    void setXSpeed(int spdx);
    void setYSpeed(int spdy);
    void stopTVC(Comms::Packet statePacket, uint8_t ip);
    uint32_t zero();
    void beginFlow(Comms::Packet statePacket, uint8_t ip);
    uint32_t flowSequence();
    void stopCircling();

    void setRadius(Comms::Packet statePacket, uint8_t ip);
    void setAngle(Comms::Packet statePacket, uint8_t ip);
}
