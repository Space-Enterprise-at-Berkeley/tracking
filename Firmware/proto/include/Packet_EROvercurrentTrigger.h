
#pragma once

#include "common.h"

#ifndef BOARD_ER
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_EROvercurrentTrigger 10

class PacketEROvercurrentTrigger 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 10;

    }

    static PacketEROvercurrentTrigger fromRawPacket(Comms::Packet *packet)
    {
        return PacketEROvercurrentTrigger();
    }

         
    
class Builder_    
{    
    private:    
        
    
    public:    
    Builder_()    
            
    {}    
    
        
    
    PacketEROvercurrentTrigger build() const    
    {            
        //static_assert(, "All fields must be set before building."); // Added static assert    
        return PacketEROvercurrentTrigger();    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_;

    

private:

    uint8_t id = 10;

    PacketEROvercurrentTrigger()
        
    {}
};

