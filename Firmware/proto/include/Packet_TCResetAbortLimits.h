
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_TC
#error
#endif
#endif


#define PACKET_ID_TCResetAbortLimits 122

class PacketTCResetAbortLimits 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 122;

    }

    static PacketTCResetAbortLimits fromRawPacket(Comms::Packet *packet)
    {
        return PacketTCResetAbortLimits();
    }

         
    
class Builder_    
{    
    private:    
        
    
    public:    
    Builder_()    
            
    {}    
    
        
    
    PacketTCResetAbortLimits build() const    
    {            
        //static_assert(, "All fields must be set before building."); // Added static assert    
        return PacketTCResetAbortLimits();    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_;

    

private:

    uint8_t id = 122;

    PacketTCResetAbortLimits()
        
    {}
};

