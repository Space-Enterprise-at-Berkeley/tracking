
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_ER
#error
#endif
#endif


#define PACKET_ID_ERRunCheckoutSequence 204

class PacketERRunCheckoutSequence 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 204;

    }

    static PacketERRunCheckoutSequence fromRawPacket(Comms::Packet *packet)
    {
        return PacketERRunCheckoutSequence();
    }

         
    
class Builder_    
{    
    private:    
        
    
    public:    
    Builder_()    
            
    {}    
    
        
    
    PacketERRunCheckoutSequence build() const    
    {            
        //static_assert(, "All fields must be set before building."); // Added static assert    
        return PacketERRunCheckoutSequence();    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_;

    

private:

    uint8_t id = 204;

    PacketERRunCheckoutSequence()
        
    {}
};

