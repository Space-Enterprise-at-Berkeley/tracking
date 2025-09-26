
#pragma once

#include "common.h"

#ifndef BOARD_LC
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_LCValues 2

class PacketLCValues 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 2;
        for (size_t i = 0; i < 4; i ++) {
            Comms::packetAddFloat(packet, m_Values.at(i));
        }
    }

    static PacketLCValues fromRawPacket(Comms::Packet *packet)
    {
        std::array<float, 4> v_m_Values;
        for (size_t i = 0; i < 16; i += 4) {
            v_m_Values[i] = Comms::packetGetFloat(packet, i);
        }

        return PacketLCValues(v_m_Values);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    std::array<float, 4> m_Values;    
    
    public:    
    Builder_(std::array<float, 4> ValuesIn)    
        : m_Values(ValuesIn)    
    {}    
    
    Builder_() {}    
    
    PacketLCValues build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketLCValues(this->m_Values);    
    }    
    
            
    Builder_<true> withValues(std::array<float, 4> input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Values', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    std::array<float, 4> m_Values;

private:

    uint8_t id = 2;

    PacketLCValues(std::array<float, 4> ValuesIn)
        : m_Values(ValuesIn)
    {}
};

