
#pragma once

#include "common.h"



#define PACKET_ID_EndFlow 201

class PacketEndFlow 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 201;

    }

    static PacketEndFlow fromRawPacket(Comms::Packet *packet)
    {
        return PacketEndFlow();
    }

         
    
class Builder_    
{    
    private:    
        
    
    public:    
    Builder_()    
            
    {}    
    
        
    
    PacketEndFlow build() const    
    {            
        //static_assert(, "All fields must be set before building."); // Added static assert    
        return PacketEndFlow();    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_;

    

private:

    uint8_t id = 201;

    PacketEndFlow()
        
    {}
};

