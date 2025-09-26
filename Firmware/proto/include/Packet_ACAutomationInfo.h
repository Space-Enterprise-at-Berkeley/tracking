
#pragma once

#include "common.h"

#ifndef BOARD_AC
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ACAutomationInfo 7

class PacketACAutomationInfo 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 7;
        Comms::packetAddUint8(packet, m_AutomationState);
        Comms::packetAddFloat(packet, m_FillDp);
    }

    static PacketACAutomationInfo fromRawPacket(Comms::Packet *packet)
    {
        uint8_t v_m_AutomationState = Comms::packetGetUint8(packet, 0);
        float v_m_FillDp = Comms::packetGetFloat(packet, 1);
        return PacketACAutomationInfo(v_m_AutomationState, v_m_FillDp);
    }

         
template<bool f0set, bool f1set>    
class Builder_    
{    
    private:    
    uint8_t m_AutomationState;    
    float m_FillDp;    
    
    public:    
    Builder_(uint8_t AutomationStateIn, float FillDpIn)    
        : m_AutomationState(AutomationStateIn), m_FillDp(FillDpIn)    
    {}    
    
    Builder_() {}    
    
    PacketACAutomationInfo build() const    
    {            
        static_assert( f0set &&  f1set, "All fields must be set before building."); // Added static assert    
        return PacketACAutomationInfo(this->m_AutomationState, this->m_FillDp);    
    }    
    
            
    Builder_<true, f1set> withAutomationState(uint8_t input) const     
    {    
        static_assert(! f0set, "Cannot set field 'AutomationState', it is already set");    
        return Builder_<true, f1set>(input, this->m_FillDp);    
    }    
    
            
    Builder_<f0set, true> withFillDp(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'FillDp', it is already set");    
        return Builder_<f0set, true>(this->m_AutomationState, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false>;

    uint8_t m_AutomationState;
    float m_FillDp;

private:

    uint8_t id = 7;

    PacketACAutomationInfo(uint8_t AutomationStateIn, float FillDpIn)
        : m_AutomationState(AutomationStateIn), m_FillDp(FillDpIn)
    {}
};

