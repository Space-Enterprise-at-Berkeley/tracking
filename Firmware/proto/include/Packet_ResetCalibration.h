
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_PT
#ifndef BOARD_LC
#ifndef BOARD_ER
#error
#endif
#endif
#endif
#endif


#define PACKET_ID_ResetCalibration 103

class PacketResetCalibration 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 103;
        Comms::packetAddUint8(packet, m_Channel);
    }

    static PacketResetCalibration fromRawPacket(Comms::Packet *packet)
    {
        uint8_t v_m_Channel = Comms::packetGetUint8(packet, 0);
        return PacketResetCalibration(v_m_Channel);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    uint8_t m_Channel;    
    
    public:    
    Builder_(uint8_t ChannelIn)    
        : m_Channel(ChannelIn)    
    {}    
    
    Builder_() {}    
    
    PacketResetCalibration build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketResetCalibration(this->m_Channel);    
    }    
    
            
    Builder_<true> withChannel(uint8_t input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Channel', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    uint8_t m_Channel;

private:

    uint8_t id = 103;

    PacketResetCalibration(uint8_t ChannelIn)
        : m_Channel(ChannelIn)
    {}
};

