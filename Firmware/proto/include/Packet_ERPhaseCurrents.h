
#pragma once

#include "common.h"

#ifndef BOARD_ER
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ERPhaseCurrents 8

class PacketERPhaseCurrents 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 8;
        Comms::packetAddFloat(packet, m_CurrentA);
        Comms::packetAddFloat(packet, m_CurrentB);
        Comms::packetAddFloat(packet, m_CurrentC);
    }

    static PacketERPhaseCurrents fromRawPacket(Comms::Packet *packet)
    {
        float v_m_CurrentA = Comms::packetGetFloat(packet, 0);
        float v_m_CurrentB = Comms::packetGetFloat(packet, 4);
        float v_m_CurrentC = Comms::packetGetFloat(packet, 8);
        return PacketERPhaseCurrents(v_m_CurrentA, v_m_CurrentB, v_m_CurrentC);
    }

         
template<bool f0set, bool f1set, bool f2set>    
class Builder_    
{    
    private:    
    float m_CurrentA;    
    float m_CurrentB;    
    float m_CurrentC;    
    
    public:    
    Builder_(float CurrentAIn, float CurrentBIn, float CurrentCIn)    
        : m_CurrentA(CurrentAIn), m_CurrentB(CurrentBIn), m_CurrentC(CurrentCIn)    
    {}    
    
    Builder_() {}    
    
    PacketERPhaseCurrents build() const    
    {            
        static_assert( f0set &&  f1set &&  f2set, "All fields must be set before building."); // Added static assert    
        return PacketERPhaseCurrents(this->m_CurrentA, this->m_CurrentB, this->m_CurrentC);    
    }    
    
            
    Builder_<true, f1set, f2set> withCurrentA(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'CurrentA', it is already set");    
        return Builder_<true, f1set, f2set>(input, this->m_CurrentB, this->m_CurrentC);    
    }    
    
            
    Builder_<f0set, true, f2set> withCurrentB(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'CurrentB', it is already set");    
        return Builder_<f0set, true, f2set>(this->m_CurrentA, input, this->m_CurrentC);    
    }    
    
            
    Builder_<f0set, f1set, true> withCurrentC(float input) const     
    {    
        static_assert(! f2set, "Cannot set field 'CurrentC', it is already set");    
        return Builder_<f0set, f1set, true>(this->m_CurrentA, this->m_CurrentB, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false, false>;

    float m_CurrentA;
    float m_CurrentB;
    float m_CurrentC;

private:

    uint8_t id = 8;

    PacketERPhaseCurrents(float CurrentAIn, float CurrentBIn, float CurrentCIn)
        : m_CurrentA(CurrentAIn), m_CurrentB(CurrentBIn), m_CurrentC(CurrentCIn)
    {}
};

