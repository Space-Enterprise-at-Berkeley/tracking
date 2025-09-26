
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_ER
#error
#endif
#endif


#define PACKET_ID_ERZero 205

class PacketERZero 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 205;

    }

    static PacketERZero fromRawPacket(Comms::Packet *packet)
    {
        return PacketERZero();
    }

         
    
class Builder_    
{    
    private:    
        
    
    public:    
    Builder_()    
            
    {}    
    
        
    
    PacketERZero build() const    
    {            
        //static_assert(, "All fields must be set before building."); // Added static assert    
        return PacketERZero();    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_;

    

private:

    uint8_t id = 205;

    PacketERZero()
        
    {}
};

