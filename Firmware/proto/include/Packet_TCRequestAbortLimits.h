
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_TC
#error
#endif
#endif


#define PACKET_ID_TCRequestAbortLimits 121

class PacketTCRequestAbortLimits 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 121;

    }

    static PacketTCRequestAbortLimits fromRawPacket(Comms::Packet *packet)
    {
        return PacketTCRequestAbortLimits();
    }

         
    
class Builder_    
{    
    private:    
        
    
    public:    
    Builder_()    
            
    {}    
    
        
    
    PacketTCRequestAbortLimits build() const    
    {            
        //static_assert(, "All fields must be set before building."); // Added static assert    
        return PacketTCRequestAbortLimits();    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_;

    

private:

    uint8_t id = 121;

    PacketTCRequestAbortLimits()
        
    {}
};

