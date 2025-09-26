
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_PT
#ifndef BOARD_LC
#ifndef BOARD_ER
#error
#endif
#endif
#endif
#endif


#define PACKET_ID_RequestCalibrationSettings 102

class PacketRequestCalibrationSettings 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 102;

    }

    static PacketRequestCalibrationSettings fromRawPacket(Comms::Packet *packet)
    {
        return PacketRequestCalibrationSettings();
    }

         
    
class Builder_    
{    
    private:    
        
    
    public:    
    Builder_()    
            
    {}    
    
        
    
    PacketRequestCalibrationSettings build() const    
    {            
        //static_assert(, "All fields must be set before building."); // Added static assert    
        return PacketRequestCalibrationSettings();    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_;

    

private:

    uint8_t id = 102;

    PacketRequestCalibrationSettings()
        
    {}
};

