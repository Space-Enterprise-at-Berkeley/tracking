
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


#define PACKET_ID_SetCalibrationOffset 104

class PacketSetCalibrationOffset 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 104;
        Comms::packetAddUint8(packet, m_Channel);
        Comms::packetAddFloat(packet, m_Value);
    }

    static PacketSetCalibrationOffset fromRawPacket(Comms::Packet *packet)
    {
        uint8_t v_m_Channel = Comms::packetGetUint8(packet, 0);
        float v_m_Value = Comms::packetGetFloat(packet, 1);
        return PacketSetCalibrationOffset(v_m_Channel, v_m_Value);
    }

         
template<bool f0set, bool f1set>    
class Builder_    
{    
    private:    
    uint8_t m_Channel;    
    float m_Value;    
    
    public:    
    Builder_(uint8_t ChannelIn, float ValueIn)    
        : m_Channel(ChannelIn), m_Value(ValueIn)    
    {}    
    
    Builder_() {}    
    
    PacketSetCalibrationOffset build() const    
    {            
        static_assert( f0set &&  f1set, "All fields must be set before building."); // Added static assert    
        return PacketSetCalibrationOffset(this->m_Channel, this->m_Value);    
    }    
    
            
    Builder_<true, f1set> withChannel(uint8_t input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Channel', it is already set");    
        return Builder_<true, f1set>(input, this->m_Value);    
    }    
    
            
    Builder_<f0set, true> withValue(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'Value', it is already set");    
        return Builder_<f0set, true>(this->m_Channel, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false>;

    uint8_t m_Channel;
    float m_Value;

private:

    uint8_t id = 104;

    PacketSetCalibrationOffset(uint8_t ChannelIn, float ValueIn)
        : m_Channel(ChannelIn), m_Value(ValueIn)
    {}
};

