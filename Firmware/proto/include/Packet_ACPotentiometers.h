
#pragma once

#include "common.h"

#ifndef BOARD_AC
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ACPotentiometers 6

class PacketACPotentiometers 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 6;
        for (size_t i = 0; i < 8; i ++) {
            Comms::packetAddUint16(packet, m_Potentiometers.at(i));
        }
    }

    static PacketACPotentiometers fromRawPacket(Comms::Packet *packet)
    {
        std::array<uint16_t, 8> v_m_Potentiometers;
        for (size_t i = 0; i < 16; i += 2) {
            v_m_Potentiometers[i] = Comms::packetGetUint16(packet, i);
        }

        return PacketACPotentiometers(v_m_Potentiometers);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    std::array<uint16_t, 8> m_Potentiometers;    
    
    public:    
    Builder_(std::array<uint16_t, 8> PotentiometersIn)    
        : m_Potentiometers(PotentiometersIn)    
    {}    
    
    Builder_() {}    
    
    PacketACPotentiometers build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketACPotentiometers(this->m_Potentiometers);    
    }    
    
            
    Builder_<true> withPotentiometers(std::array<uint16_t, 8> input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Potentiometers', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    std::array<uint16_t, 8> m_Potentiometers;

private:

    uint8_t id = 6;

    PacketACPotentiometers(std::array<uint16_t, 8> PotentiometersIn)
        : m_Potentiometers(PotentiometersIn)
    {}
};

