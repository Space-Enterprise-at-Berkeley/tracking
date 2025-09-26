
#pragma once

#include "common.h"

#ifndef BOARD_AC
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ACActuatorCurrents 4

class PacketACActuatorCurrents 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 4;
        for (size_t i = 0; i < 8; i ++) {
            Comms::packetAddFloat(packet, m_Currents.at(i));
        }
    }

    static PacketACActuatorCurrents fromRawPacket(Comms::Packet *packet)
    {
        std::array<float, 8> v_m_Currents;
        for (size_t i = 0; i < 32; i += 4) {
            v_m_Currents[i] = Comms::packetGetFloat(packet, i);
        }

        return PacketACActuatorCurrents(v_m_Currents);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    std::array<float, 8> m_Currents;    
    
    public:    
    Builder_(std::array<float, 8> CurrentsIn)    
        : m_Currents(CurrentsIn)    
    {}    
    
    Builder_() {}    
    
    PacketACActuatorCurrents build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketACActuatorCurrents(this->m_Currents);    
    }    
    
            
    Builder_<true> withCurrents(std::array<float, 8> input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Currents', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    std::array<float, 8> m_Currents;

private:

    uint8_t id = 4;

    PacketACActuatorCurrents(std::array<float, 8> CurrentsIn)
        : m_Currents(CurrentsIn)
    {}
};

