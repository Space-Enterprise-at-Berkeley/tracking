
#pragma once

#include "common.h"

#ifndef BOARD_ER
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ERLimitSwitch 7

class PacketERLimitSwitch 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 7;
        Comms::packetAddFloat(packet, m_FullyClosedSwitch);
        Comms::packetAddFloat(packet, m_FullyOpenSwitch);
    }

    static PacketERLimitSwitch fromRawPacket(Comms::Packet *packet)
    {
        float v_m_FullyClosedSwitch = Comms::packetGetFloat(packet, 0);
        float v_m_FullyOpenSwitch = Comms::packetGetFloat(packet, 4);
        return PacketERLimitSwitch(v_m_FullyClosedSwitch, v_m_FullyOpenSwitch);
    }

         
template<bool f0set, bool f1set>    
class Builder_    
{    
    private:    
    float m_FullyClosedSwitch;    
    float m_FullyOpenSwitch;    
    
    public:    
    Builder_(float FullyClosedSwitchIn, float FullyOpenSwitchIn)    
        : m_FullyClosedSwitch(FullyClosedSwitchIn), m_FullyOpenSwitch(FullyOpenSwitchIn)    
    {}    
    
    Builder_() {}    
    
    PacketERLimitSwitch build() const    
    {            
        static_assert( f0set &&  f1set, "All fields must be set before building."); // Added static assert    
        return PacketERLimitSwitch(this->m_FullyClosedSwitch, this->m_FullyOpenSwitch);    
    }    
    
            
    Builder_<true, f1set> withFullyClosedSwitch(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'FullyClosedSwitch', it is already set");    
        return Builder_<true, f1set>(input, this->m_FullyOpenSwitch);    
    }    
    
            
    Builder_<f0set, true> withFullyOpenSwitch(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'FullyOpenSwitch', it is already set");    
        return Builder_<f0set, true>(this->m_FullyClosedSwitch, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false>;

    float m_FullyClosedSwitch;
    float m_FullyOpenSwitch;

private:

    uint8_t id = 7;

    PacketERLimitSwitch(float FullyClosedSwitchIn, float FullyOpenSwitchIn)
        : m_FullyClosedSwitch(FullyClosedSwitchIn), m_FullyOpenSwitch(FullyOpenSwitchIn)
    {}
};

