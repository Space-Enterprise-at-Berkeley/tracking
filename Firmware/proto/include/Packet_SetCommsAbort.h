
#pragma once

#include "common.h"



#define PACKET_ID_SetCommsAbort 251

class PacketSetCommsAbort 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 251;
        Comms::packetAddUint8(packet, m_Enabled);
    }

    static PacketSetCommsAbort fromRawPacket(Comms::Packet *packet)
    {
        uint8_t v_m_Enabled = Comms::packetGetUint8(packet, 0);
        return PacketSetCommsAbort(v_m_Enabled);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    uint8_t m_Enabled;    
    
    public:    
    Builder_(uint8_t EnabledIn)    
        : m_Enabled(EnabledIn)    
    {}    
    
    Builder_() {}    
    
    PacketSetCommsAbort build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketSetCommsAbort(this->m_Enabled);    
    }    
    
            
    Builder_<true> withEnabled(uint8_t input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Enabled', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    uint8_t m_Enabled;

private:

    uint8_t id = 251;

    PacketSetCommsAbort(uint8_t EnabledIn)
        : m_Enabled(EnabledIn)
    {}
};

