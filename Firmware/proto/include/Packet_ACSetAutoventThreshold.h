
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_AC
#error
#endif
#endif


#define PACKET_ID_ACSetAutoventThreshold 124

class PacketACSetAutoventThreshold 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 124;
        Comms::packetAddFloat(packet, m_NosAutoventPressure);
        Comms::packetAddFloat(packet, m_IpaAutoventPressure);
        Comms::packetAddUint8(packet, m_NoCommsAbortEnabled);
    }

    static PacketACSetAutoventThreshold fromRawPacket(Comms::Packet *packet)
    {
        float v_m_NosAutoventPressure = Comms::packetGetFloat(packet, 0);
        float v_m_IpaAutoventPressure = Comms::packetGetFloat(packet, 4);
        uint8_t v_m_NoCommsAbortEnabled = Comms::packetGetUint8(packet, 8);
        return PacketACSetAutoventThreshold(v_m_NosAutoventPressure, v_m_IpaAutoventPressure, v_m_NoCommsAbortEnabled);
    }

         
template<bool f0set, bool f1set, bool f2set>    
class Builder_    
{    
    private:    
    float m_NosAutoventPressure;    
    float m_IpaAutoventPressure;    
    uint8_t m_NoCommsAbortEnabled;    
    
    public:    
    Builder_(float NosAutoventPressureIn, float IpaAutoventPressureIn, uint8_t NoCommsAbortEnabledIn)    
        : m_NosAutoventPressure(NosAutoventPressureIn), m_IpaAutoventPressure(IpaAutoventPressureIn), m_NoCommsAbortEnabled(NoCommsAbortEnabledIn)    
    {}    
    
    Builder_() {}    
    
    PacketACSetAutoventThreshold build() const    
    {            
        static_assert( f0set &&  f1set &&  f2set, "All fields must be set before building."); // Added static assert    
        return PacketACSetAutoventThreshold(this->m_NosAutoventPressure, this->m_IpaAutoventPressure, this->m_NoCommsAbortEnabled);    
    }    
    
            
    Builder_<true, f1set, f2set> withNosAutoventPressure(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'NosAutoventPressure', it is already set");    
        return Builder_<true, f1set, f2set>(input, this->m_IpaAutoventPressure, this->m_NoCommsAbortEnabled);    
    }    
    
            
    Builder_<f0set, true, f2set> withIpaAutoventPressure(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'IpaAutoventPressure', it is already set");    
        return Builder_<f0set, true, f2set>(this->m_NosAutoventPressure, input, this->m_NoCommsAbortEnabled);    
    }    
    
            
    Builder_<f0set, f1set, true> withNoCommsAbortEnabled(uint8_t input) const     
    {    
        static_assert(! f2set, "Cannot set field 'NoCommsAbortEnabled', it is already set");    
        return Builder_<f0set, f1set, true>(this->m_NosAutoventPressure, this->m_IpaAutoventPressure, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false, false>;

    float m_NosAutoventPressure;
    float m_IpaAutoventPressure;
    uint8_t m_NoCommsAbortEnabled;

private:

    uint8_t id = 124;

    PacketACSetAutoventThreshold(float NosAutoventPressureIn, float IpaAutoventPressureIn, uint8_t NoCommsAbortEnabledIn)
        : m_NosAutoventPressure(NosAutoventPressureIn), m_IpaAutoventPressure(IpaAutoventPressureIn), m_NoCommsAbortEnabled(NoCommsAbortEnabledIn)
    {}
};

