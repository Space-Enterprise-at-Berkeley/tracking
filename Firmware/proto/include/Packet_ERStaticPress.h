
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_ER
#error
#endif
#endif


#define PACKET_ID_ERStaticPress 203

class PacketERStaticPress 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 203;

    }

    static PacketERStaticPress fromRawPacket(Comms::Packet *packet)
    {
        return PacketERStaticPress();
    }

         
    
class Builder_    
{    
    private:    
        
    
    public:    
    Builder_()    
            
    {}    
    
        
    
    PacketERStaticPress build() const    
    {            
        //static_assert(, "All fields must be set before building."); // Added static assert    
        return PacketERStaticPress();    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_;

    

private:

    uint8_t id = 203;

    PacketERStaticPress()
        
    {}
};

