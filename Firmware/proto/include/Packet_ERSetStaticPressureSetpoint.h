
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_ER
#error
#endif
#endif


#define PACKET_ID_ERSetStaticPressureSetpoint 215

class PacketERSetStaticPressureSetpoint 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 215;
        Comms::packetAddFloat(packet, m_Value);
    }

    static PacketERSetStaticPressureSetpoint fromRawPacket(Comms::Packet *packet)
    {
        float v_m_Value = Comms::packetGetFloat(packet, 0);
        return PacketERSetStaticPressureSetpoint(v_m_Value);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    float m_Value;    
    
    public:    
    Builder_(float ValueIn)    
        : m_Value(ValueIn)    
    {}    
    
    Builder_() {}    
    
    PacketERSetStaticPressureSetpoint build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketERSetStaticPressureSetpoint(this->m_Value);    
    }    
    
            
    Builder_<true> withValue(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Value', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    float m_Value;

private:

    uint8_t id = 215;

    PacketERSetStaticPressureSetpoint(float ValueIn)
        : m_Value(ValueIn)
    {}
};

