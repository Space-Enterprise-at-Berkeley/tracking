
#pragma once

#include "common.h"

#ifndef BOARD_AC
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ACActuatorContinuities 3

class PacketACActuatorContinuities 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 3;
        for (size_t i = 0; i < 8; i ++) {
            Comms::packetAddFloat(packet, m_Continuities.at(i));
        }
    }

    static PacketACActuatorContinuities fromRawPacket(Comms::Packet *packet)
    {
        std::array<float, 8> v_m_Continuities;
        for (size_t i = 0; i < 32; i += 4) {
            v_m_Continuities[i] = Comms::packetGetFloat(packet, i);
        }

        return PacketACActuatorContinuities(v_m_Continuities);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    std::array<float, 8> m_Continuities;    
    
    public:    
    Builder_(std::array<float, 8> ContinuitiesIn)    
        : m_Continuities(ContinuitiesIn)    
    {}    
    
    Builder_() {}    
    
    PacketACActuatorContinuities build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketACActuatorContinuities(this->m_Continuities);    
    }    
    
            
    Builder_<true> withContinuities(std::array<float, 8> input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Continuities', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    std::array<float, 8> m_Continuities;

private:

    uint8_t id = 3;

    PacketACActuatorContinuities(std::array<float, 8> ContinuitiesIn)
        : m_Continuities(ContinuitiesIn)
    {}
};

