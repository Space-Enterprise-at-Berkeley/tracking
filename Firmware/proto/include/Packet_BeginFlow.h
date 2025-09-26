
#pragma once

#include "common.h"



#define PACKET_ID_BeginFlow 200

class PacketBeginFlow 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 200;
        Comms::packetAddUint8(packet, m_SystemMode);
        Comms::packetAddFloat(packet, m_BurnTime);
        Comms::packetAddUint8(packet, m_NitrousEnable);
        Comms::packetAddUint8(packet, m_IpaEnable);
    }

    static PacketBeginFlow fromRawPacket(Comms::Packet *packet)
    {
        SystemMode v_m_SystemMode = static_cast<SystemMode>(Comms::packetGetUint8(packet, 0));
        float v_m_BurnTime = Comms::packetGetFloat(packet, 1);
        uint8_t v_m_NitrousEnable = Comms::packetGetUint8(packet, 5);
        uint8_t v_m_IpaEnable = Comms::packetGetUint8(packet, 6);
        return PacketBeginFlow(v_m_SystemMode, v_m_BurnTime, v_m_NitrousEnable, v_m_IpaEnable);
    }

         
template<bool f0set, bool f1set, bool f2set, bool f3set>    
class Builder_    
{    
    private:    
    SystemMode m_SystemMode;    
    float m_BurnTime;    
    uint8_t m_NitrousEnable;    
    uint8_t m_IpaEnable;    
    
    public:    
    Builder_(SystemMode SystemModeIn, float BurnTimeIn, uint8_t NitrousEnableIn, uint8_t IpaEnableIn)    
        : m_SystemMode(SystemModeIn), m_BurnTime(BurnTimeIn), m_NitrousEnable(NitrousEnableIn), m_IpaEnable(IpaEnableIn)    
    {}    
    
    Builder_() {}    
    
    PacketBeginFlow build() const    
    {            
        static_assert( f0set &&  f1set &&  f2set &&  f3set, "All fields must be set before building."); // Added static assert    
        return PacketBeginFlow(this->m_SystemMode, this->m_BurnTime, this->m_NitrousEnable, this->m_IpaEnable);    
    }    
    
            
    Builder_<true, f1set, f2set, f3set> withSystemMode(SystemMode input) const     
    {    
        static_assert(! f0set, "Cannot set field 'SystemMode', it is already set");    
        return Builder_<true, f1set, f2set, f3set>(input, this->m_BurnTime, this->m_NitrousEnable, this->m_IpaEnable);    
    }    
    
            
    Builder_<f0set, true, f2set, f3set> withBurnTime(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'BurnTime', it is already set");    
        return Builder_<f0set, true, f2set, f3set>(this->m_SystemMode, input, this->m_NitrousEnable, this->m_IpaEnable);    
    }    
    
            
    Builder_<f0set, f1set, true, f3set> withNitrousEnable(uint8_t input) const     
    {    
        static_assert(! f2set, "Cannot set field 'NitrousEnable', it is already set");    
        return Builder_<f0set, f1set, true, f3set>(this->m_SystemMode, this->m_BurnTime, input, this->m_IpaEnable);    
    }    
    
            
    Builder_<f0set, f1set, f2set, true> withIpaEnable(uint8_t input) const     
    {    
        static_assert(! f3set, "Cannot set field 'IpaEnable', it is already set");    
        return Builder_<f0set, f1set, f2set, true>(this->m_SystemMode, this->m_BurnTime, this->m_NitrousEnable, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false, false, false>;

    SystemMode m_SystemMode;
    float m_BurnTime;
    uint8_t m_NitrousEnable;
    uint8_t m_IpaEnable;

private:

    uint8_t id = 200;

    PacketBeginFlow(SystemMode SystemModeIn, float BurnTimeIn, uint8_t NitrousEnableIn, uint8_t IpaEnableIn)
        : m_SystemMode(SystemModeIn), m_BurnTime(BurnTimeIn), m_NitrousEnable(NitrousEnableIn), m_IpaEnable(IpaEnableIn)
    {}
};

