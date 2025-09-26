
#pragma once

#include "common.h"

#ifndef BOARD_AC
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_GemsDutyCycle 8

class PacketGemsDutyCycle 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 8;
        Comms::packetAddFloat(packet, m_GemsDutyCycle);
    }

    static PacketGemsDutyCycle fromRawPacket(Comms::Packet *packet)
    {
        float v_m_GemsDutyCycle = Comms::packetGetFloat(packet, 0);
        return PacketGemsDutyCycle(v_m_GemsDutyCycle);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    float m_GemsDutyCycle;    
    
    public:    
    Builder_(float GemsDutyCycleIn)    
        : m_GemsDutyCycle(GemsDutyCycleIn)    
    {}    
    
    Builder_() {}    
    
    PacketGemsDutyCycle build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketGemsDutyCycle(this->m_GemsDutyCycle);    
    }    
    
            
    Builder_<true> withGemsDutyCycle(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'GemsDutyCycle', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    float m_GemsDutyCycle;

private:

    uint8_t id = 8;

    PacketGemsDutyCycle(float GemsDutyCycleIn)
        : m_GemsDutyCycle(GemsDutyCycleIn)
    {}
};

