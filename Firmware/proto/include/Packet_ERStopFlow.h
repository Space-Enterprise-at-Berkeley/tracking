
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_ER
#error
#endif
#endif


#define PACKET_ID_ERStopFlow 201

class PacketERStopFlow 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 201;

    }

    static PacketERStopFlow fromRawPacket(Comms::Packet *packet)
    {
        return PacketERStopFlow();
    }

         
    
class Builder_    
{    
    private:    
        
    
    public:    
    Builder_()    
            
    {}    
    
        
    
    PacketERStopFlow build() const    
    {            
        //static_assert(, "All fields must be set before building."); // Added static assert    
        return PacketERStopFlow();    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_;

    

private:

    uint8_t id = 201;

    PacketERStopFlow()
        
    {}
};

