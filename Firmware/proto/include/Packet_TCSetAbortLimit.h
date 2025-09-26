
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_TC
#error
#endif
#endif


#define PACKET_ID_TCSetAbortLimit 120

class PacketTCSetAbortLimit 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 120;
        Comms::packetAddUint8(packet, m_Channel);
        Comms::packetAddFloat(packet, m_Temp);
    }

    static PacketTCSetAbortLimit fromRawPacket(Comms::Packet *packet)
    {
        uint8_t v_m_Channel = Comms::packetGetUint8(packet, 0);
        float v_m_Temp = Comms::packetGetFloat(packet, 1);
        return PacketTCSetAbortLimit(v_m_Channel, v_m_Temp);
    }

         
template<bool f0set, bool f1set>    
class Builder_    
{    
    private:    
    uint8_t m_Channel;    
    float m_Temp;    
    
    public:    
    Builder_(uint8_t ChannelIn, float TempIn)    
        : m_Channel(ChannelIn), m_Temp(TempIn)    
    {}    
    
    Builder_() {}    
    
    PacketTCSetAbortLimit build() const    
    {            
        static_assert( f0set &&  f1set, "All fields must be set before building."); // Added static assert    
        return PacketTCSetAbortLimit(this->m_Channel, this->m_Temp);    
    }    
    
            
    Builder_<true, f1set> withChannel(uint8_t input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Channel', it is already set");    
        return Builder_<true, f1set>(input, this->m_Temp);    
    }    
    
            
    Builder_<f0set, true> withTemp(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'Temp', it is already set");    
        return Builder_<f0set, true>(this->m_Channel, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false>;

    uint8_t m_Channel;
    float m_Temp;

private:

    uint8_t id = 120;

    PacketTCSetAbortLimit(uint8_t ChannelIn, float TempIn)
        : m_Channel(ChannelIn), m_Temp(TempIn)
    {}
};

