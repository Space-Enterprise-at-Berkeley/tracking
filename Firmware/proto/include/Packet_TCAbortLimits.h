
#pragma once

#include "common.h"

#ifndef BOARD_TC
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_TCAbortLimits 123

class PacketTCAbortLimits 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 123;
        for (size_t i = 0; i < 8; i ++) {
            Comms::packetAddFloat(packet, m_Temps.at(i));
        }
    }

    static PacketTCAbortLimits fromRawPacket(Comms::Packet *packet)
    {
        std::array<float, 8> v_m_Temps;
        for (size_t i = 0; i < 32; i += 4) {
            v_m_Temps[i] = Comms::packetGetFloat(packet, i);
        }

        return PacketTCAbortLimits(v_m_Temps);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    std::array<float, 8> m_Temps;    
    
    public:    
    Builder_(std::array<float, 8> TempsIn)    
        : m_Temps(TempsIn)    
    {}    
    
    Builder_() {}    
    
    PacketTCAbortLimits build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketTCAbortLimits(this->m_Temps);    
    }    
    
            
    Builder_<true> withTemps(std::array<float, 8> input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Temps', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    std::array<float, 8> m_Temps;

private:

    uint8_t id = 123;

    PacketTCAbortLimits(std::array<float, 8> TempsIn)
        : m_Temps(TempsIn)
    {}
};

