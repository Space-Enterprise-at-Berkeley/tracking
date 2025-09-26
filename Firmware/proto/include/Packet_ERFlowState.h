
#pragma once

#include "common.h"

#ifndef BOARD_ER
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ERFlowState 6

class PacketERFlowState 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 6;
        Comms::packetAddUint8(packet, m_FlowState);
    }

    static PacketERFlowState fromRawPacket(Comms::Packet *packet)
    {
        uint8_t v_m_FlowState = Comms::packetGetUint8(packet, 0);
        return PacketERFlowState(v_m_FlowState);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    uint8_t m_FlowState;    
    
    public:    
    Builder_(uint8_t FlowStateIn)    
        : m_FlowState(FlowStateIn)    
    {}    
    
    Builder_() {}    
    
    PacketERFlowState build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketERFlowState(this->m_FlowState);    
    }    
    
            
    Builder_<true> withFlowState(uint8_t input) const     
    {    
        static_assert(! f0set, "Cannot set field 'FlowState', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    uint8_t m_FlowState;

private:

    uint8_t id = 6;

    PacketERFlowState(uint8_t FlowStateIn)
        : m_FlowState(FlowStateIn)
    {}
};

