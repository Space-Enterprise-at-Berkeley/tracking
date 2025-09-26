
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_ER
#error
#endif
#endif


#define PACKET_ID_ERPartialOpen 202

class PacketERPartialOpen 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 202;
        Comms::packetAddFloat(packet, m_EncoderTicks);
    }

    static PacketERPartialOpen fromRawPacket(Comms::Packet *packet)
    {
        float v_m_EncoderTicks = Comms::packetGetFloat(packet, 0);
        return PacketERPartialOpen(v_m_EncoderTicks);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    float m_EncoderTicks;    
    
    public:    
    Builder_(float EncoderTicksIn)    
        : m_EncoderTicks(EncoderTicksIn)    
    {}    
    
    Builder_() {}    
    
    PacketERPartialOpen build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketERPartialOpen(this->m_EncoderTicks);    
    }    
    
            
    Builder_<true> withEncoderTicks(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'EncoderTicks', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    float m_EncoderTicks;

private:

    uint8_t id = 202;

    PacketERPartialOpen(float EncoderTicksIn)
        : m_EncoderTicks(EncoderTicksIn)
    {}
};

