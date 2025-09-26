
#pragma once

#include "common.h"

#ifndef BOARD_AC
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ACActuatorStates 2

class PacketACActuatorStates 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 2;
        for (size_t i = 0; i < 8; i ++) {
            Comms::packetAddUint8(packet, m_States.at(i));
        }
    }

    static PacketACActuatorStates fromRawPacket(Comms::Packet *packet)
    {
        std::array<ACActuatorStatesType, 8> v_m_States;
        for (size_t i = 0; i < 8; i += 1) {
            v_m_States[i] = static_cast<ACActuatorStatesType>(Comms::packetGetUint8(packet, i));
        }

        return PacketACActuatorStates(v_m_States);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    std::array<ACActuatorStatesType, 8> m_States;    
    
    public:    
    Builder_(std::array<ACActuatorStatesType, 8> StatesIn)    
        : m_States(StatesIn)    
    {}    
    
    Builder_() {}    
    
    PacketACActuatorStates build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketACActuatorStates(this->m_States);    
    }    
    
            
    Builder_<true> withStates(std::array<ACActuatorStatesType, 8> input) const     
    {    
        static_assert(! f0set, "Cannot set field 'States', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    std::array<ACActuatorStatesType, 8> m_States;

private:

    uint8_t id = 2;

    PacketACActuatorStates(std::array<ACActuatorStatesType, 8> StatesIn)
        : m_States(StatesIn)
    {}
};

