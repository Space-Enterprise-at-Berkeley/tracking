
#pragma once

#include "common.h"



#define PACKET_ID_Heartbeat 249

class PacketHeartbeat 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 249;
        Comms::packetAddUint32(packet, m_PacketSpecVersion);
    }

    static PacketHeartbeat fromRawPacket(Comms::Packet *packet)
    {
        uint32_t v_m_PacketSpecVersion = Comms::packetGetUint32(packet, 0);
        return PacketHeartbeat(v_m_PacketSpecVersion);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    uint32_t m_PacketSpecVersion;    
    
    public:    
    Builder_(uint32_t PacketSpecVersionIn)    
        : m_PacketSpecVersion(PacketSpecVersionIn)    
    {}    
    
    Builder_() {}    
    
    PacketHeartbeat build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketHeartbeat(this->m_PacketSpecVersion);    
    }    
    
            
    Builder_<true> withPacketSpecVersion(uint32_t input) const     
    {    
        static_assert(! f0set, "Cannot set field 'PacketSpecVersion', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    uint32_t m_PacketSpecVersion;

private:

    uint8_t id = 249;

    PacketHeartbeat(uint32_t PacketSpecVersionIn)
        : m_PacketSpecVersion(PacketSpecVersionIn)
    {}
};

