
#pragma once

#include "common.h"

#ifndef BOARD_TC
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_TCFaults 4

class PacketTCFaults 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 4;
        for (size_t i = 0; i < 8; i ++) {
            Comms::packetAddUint8(packet, m_Faults.at(i));
        }
    }

    static PacketTCFaults fromRawPacket(Comms::Packet *packet)
    {
        std::array<uint8_t, 8> v_m_Faults;
        for (size_t i = 0; i < 8; i += 1) {
            v_m_Faults[i] = Comms::packetGetUint8(packet, i);
        }

        return PacketTCFaults(v_m_Faults);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    std::array<uint8_t, 8> m_Faults;    
    
    public:    
    Builder_(std::array<uint8_t, 8> FaultsIn)    
        : m_Faults(FaultsIn)    
    {}    
    
    Builder_() {}    
    
    PacketTCFaults build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketTCFaults(this->m_Faults);    
    }    
    
            
    Builder_<true> withFaults(std::array<uint8_t, 8> input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Faults', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    std::array<uint8_t, 8> m_Faults;

private:

    uint8_t id = 4;

    PacketTCFaults(std::array<uint8_t, 8> FaultsIn)
        : m_Faults(FaultsIn)
    {}
};

