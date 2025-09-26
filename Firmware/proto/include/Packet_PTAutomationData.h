
#pragma once

#include "common.h"

#ifndef BOARD_PT
#ifndef BOARD_GD
#ifndef BOARD_AC
#error
#endif
#endif
#endif


#define PACKET_ID_PTAutomationData 4

class PacketPTAutomationData 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 4;
        Comms::packetAddFloat(packet, m_NosTank);
        Comms::packetAddFloat(packet, m_IpaTank);
    }

    static PacketPTAutomationData fromRawPacket(Comms::Packet *packet)
    {
        float v_m_NosTank = Comms::packetGetFloat(packet, 0);
        float v_m_IpaTank = Comms::packetGetFloat(packet, 4);
        return PacketPTAutomationData(v_m_NosTank, v_m_IpaTank);
    }

         
template<bool f0set, bool f1set>    
class Builder_    
{    
    private:    
    float m_NosTank;    
    float m_IpaTank;    
    
    public:    
    Builder_(float NosTankIn, float IpaTankIn)    
        : m_NosTank(NosTankIn), m_IpaTank(IpaTankIn)    
    {}    
    
    Builder_() {}    
    
    PacketPTAutomationData build() const    
    {            
        static_assert( f0set &&  f1set, "All fields must be set before building."); // Added static assert    
        return PacketPTAutomationData(this->m_NosTank, this->m_IpaTank);    
    }    
    
            
    Builder_<true, f1set> withNosTank(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'NosTank', it is already set");    
        return Builder_<true, f1set>(input, this->m_IpaTank);    
    }    
    
            
    Builder_<f0set, true> withIpaTank(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'IpaTank', it is already set");    
        return Builder_<f0set, true>(this->m_NosTank, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false>;

    float m_NosTank;
    float m_IpaTank;

private:

    uint8_t id = 4;

    PacketPTAutomationData(float NosTankIn, float IpaTankIn)
        : m_NosTank(NosTankIn), m_IpaTank(IpaTankIn)
    {}
};

