
#pragma once

#include "common.h"

#ifndef BOARD_PT
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_PTValues 2

class PacketPTValues 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 2;
        for (size_t i = 0; i < 8; i ++) {
            Comms::packetAddFloat(packet, m_Values.at(i));
        }
    }

    static PacketPTValues fromRawPacket(Comms::Packet *packet)
    {
        std::array<float, 8> v_m_Values;
        for (size_t i = 0; i < 32; i += 4) {
            v_m_Values[i] = Comms::packetGetFloat(packet, i);
        }

        return PacketPTValues(v_m_Values);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    std::array<float, 8> m_Values;    
    
    public:    
    Builder_(std::array<float, 8> ValuesIn)    
        : m_Values(ValuesIn)    
    {}    
    
    Builder_() {}    
    
    PacketPTValues build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketPTValues(this->m_Values);    
    }    
    
            
    Builder_<true> withValues(std::array<float, 8> input) const     
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

    std::array<float, 8> m_Values;

private:

    uint8_t id = 2;

    PacketPTValues(std::array<float, 8> ValuesIn)
        : m_Values(ValuesIn)
    {}
};

