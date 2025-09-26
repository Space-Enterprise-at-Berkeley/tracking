
#pragma once

#include "common.h"

#ifndef BOARD_PT
#ifndef BOARD_TC
#ifndef BOARD_LC
#ifndef BOARD_AC
#ifndef BOARD_GD
#error
#endif
#endif
#endif
#endif
#endif


#define PACKET_ID_24VSupplyStats 1

class Packet24VSupplyStats 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 1;
        Comms::packetAddFloat(packet, m_Supply24Voltage);
        Comms::packetAddFloat(packet, m_Supply24Current);
        Comms::packetAddFloat(packet, m_Supply24Power);
    }

    static Packet24VSupplyStats fromRawPacket(Comms::Packet *packet)
    {
        float v_m_Supply24Voltage = Comms::packetGetFloat(packet, 0);
        float v_m_Supply24Current = Comms::packetGetFloat(packet, 4);
        float v_m_Supply24Power = Comms::packetGetFloat(packet, 8);
        return Packet24VSupplyStats(v_m_Supply24Voltage, v_m_Supply24Current, v_m_Supply24Power);
    }

         
template<bool f0set, bool f1set, bool f2set>    
class Builder_    
{    
    private:    
    float m_Supply24Voltage;    
    float m_Supply24Current;    
    float m_Supply24Power;    
    
    public:    
    Builder_(float Supply24VoltageIn, float Supply24CurrentIn, float Supply24PowerIn)    
        : m_Supply24Voltage(Supply24VoltageIn), m_Supply24Current(Supply24CurrentIn), m_Supply24Power(Supply24PowerIn)    
    {}    
    
    Builder_() {}    
    
    Packet24VSupplyStats build() const    
    {            
        static_assert( f0set &&  f1set &&  f2set, "All fields must be set before building."); // Added static assert    
        return Packet24VSupplyStats(this->m_Supply24Voltage, this->m_Supply24Current, this->m_Supply24Power);    
    }    
    
            
    Builder_<true, f1set, f2set> withSupply24Voltage(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Supply24Voltage', it is already set");    
        return Builder_<true, f1set, f2set>(input, this->m_Supply24Current, this->m_Supply24Power);    
    }    
    
            
    Builder_<f0set, true, f2set> withSupply24Current(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'Supply24Current', it is already set");    
        return Builder_<f0set, true, f2set>(this->m_Supply24Voltage, input, this->m_Supply24Power);    
    }    
    
            
    Builder_<f0set, f1set, true> withSupply24Power(float input) const     
    {    
        static_assert(! f2set, "Cannot set field 'Supply24Power', it is already set");    
        return Builder_<f0set, f1set, true>(this->m_Supply24Voltage, this->m_Supply24Current, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false, false>;

    float m_Supply24Voltage;
    float m_Supply24Current;
    float m_Supply24Power;

private:

    uint8_t id = 1;

    Packet24VSupplyStats(float Supply24VoltageIn, float Supply24CurrentIn, float Supply24PowerIn)
        : m_Supply24Voltage(Supply24VoltageIn), m_Supply24Current(Supply24CurrentIn), m_Supply24Power(Supply24PowerIn)
    {}
};

