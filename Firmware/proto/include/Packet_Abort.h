
#pragma once

#include "common.h"



#define PACKET_ID_Abort 133

class PacketAbort 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 133;
        Comms::packetAddUint8(packet, m_SystemMode);
        Comms::packetAddUint8(packet, m_AbortReason);
    }

    static PacketAbort fromRawPacket(Comms::Packet *packet)
    {
        SystemMode v_m_SystemMode = static_cast<SystemMode>(Comms::packetGetUint8(packet, 0));
        AbortCode v_m_AbortReason = static_cast<AbortCode>(Comms::packetGetUint8(packet, 1));
        return PacketAbort(v_m_SystemMode, v_m_AbortReason);
    }

         
template<bool f0set, bool f1set>    
class Builder_    
{    
    private:    
    SystemMode m_SystemMode;    
    AbortCode m_AbortReason;    
    
    public:    
    Builder_(SystemMode SystemModeIn, AbortCode AbortReasonIn)    
        : m_SystemMode(SystemModeIn), m_AbortReason(AbortReasonIn)    
    {}    
    
    Builder_() {}    
    
    PacketAbort build() const    
    {            
        static_assert( f0set &&  f1set, "All fields must be set before building."); // Added static assert    
        return PacketAbort(this->m_SystemMode, this->m_AbortReason);    
    }    
    
            
    Builder_<true, f1set> withSystemMode(SystemMode input) const     
    {    
        static_assert(! f0set, "Cannot set field 'SystemMode', it is already set");    
        return Builder_<true, f1set>(input, this->m_AbortReason);    
    }    
    
            
    Builder_<f0set, true> withAbortReason(AbortCode input) const     
    {    
        static_assert(! f1set, "Cannot set field 'AbortReason', it is already set");    
        return Builder_<f0set, true>(this->m_SystemMode, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false>;

    SystemMode m_SystemMode;
    AbortCode m_AbortReason;

private:

    uint8_t id = 133;

    PacketAbort(SystemMode SystemModeIn, AbortCode AbortReasonIn)
        : m_SystemMode(SystemModeIn), m_AbortReason(AbortReasonIn)
    {}
};

