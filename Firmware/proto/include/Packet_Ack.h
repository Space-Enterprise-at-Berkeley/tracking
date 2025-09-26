
#pragma once

#include "common.h"



#define PACKET_ID_Ack 0

class PacketAck 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 0;
        for (size_t i = 0; i < 40; i ++) {
            Comms::packetAddUint8(packet, m_ProtoVersion.at(i));
        }
    }

    static PacketAck fromRawPacket(Comms::Packet *packet)
    {
        std::array<uint8_t, 40> v_m_ProtoVersion;
        for (size_t i = 0; i < 40; i += 1) {
            v_m_ProtoVersion[i] = Comms::packetGetUint8(packet, i);
        }

        return PacketAck(v_m_ProtoVersion);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    std::array<uint8_t, 40> m_ProtoVersion;    
    
    public:    
    Builder_(std::array<uint8_t, 40> ProtoVersionIn)    
        : m_ProtoVersion(ProtoVersionIn)    
    {}    
    
    Builder_() {}    
    
    PacketAck build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketAck(this->m_ProtoVersion);    
    }    
    
            
    Builder_<true> withProtoVersion(std::array<uint8_t, 40> input) const     
    {    
        static_assert(! f0set, "Cannot set field 'ProtoVersion', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    std::array<uint8_t, 40> m_ProtoVersion;

private:

    uint8_t id = 0;

    PacketAck(std::array<uint8_t, 40> ProtoVersionIn)
        : m_ProtoVersion(ProtoVersionIn)
    {}
};

