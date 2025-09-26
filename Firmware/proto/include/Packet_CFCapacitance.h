
#pragma once

#include "common.h"

#ifndef BOARD_CF
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_CFCapacitance 1

class PacketCFCapacitance 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 1;
        Comms::packetAddFloat(packet, m_Cap);
        Comms::packetAddFloat(packet, m_Ref);
        Comms::packetAddFloat(packet, m_Temperature);
    }

    static PacketCFCapacitance fromRawPacket(Comms::Packet *packet)
    {
        float v_m_Cap = Comms::packetGetFloat(packet, 0);
        float v_m_Ref = Comms::packetGetFloat(packet, 4);
        float v_m_Temperature = Comms::packetGetFloat(packet, 8);
        return PacketCFCapacitance(v_m_Cap, v_m_Ref, v_m_Temperature);
    }

         
template<bool f0set, bool f1set, bool f2set>    
class Builder_    
{    
    private:    
    float m_Cap;    
    float m_Ref;    
    float m_Temperature;    
    
    public:    
    Builder_(float CapIn, float RefIn, float TemperatureIn)    
        : m_Cap(CapIn), m_Ref(RefIn), m_Temperature(TemperatureIn)    
    {}    
    
    Builder_() {}    
    
    PacketCFCapacitance build() const    
    {            
        static_assert( f0set &&  f1set &&  f2set, "All fields must be set before building."); // Added static assert    
        return PacketCFCapacitance(this->m_Cap, this->m_Ref, this->m_Temperature);    
    }    
    
            
    Builder_<true, f1set, f2set> withCap(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'Cap', it is already set");    
        return Builder_<true, f1set, f2set>(input, this->m_Ref, this->m_Temperature);    
    }    
    
            
    Builder_<f0set, true, f2set> withRef(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'Ref', it is already set");    
        return Builder_<f0set, true, f2set>(this->m_Cap, input, this->m_Temperature);    
    }    
    
            
    Builder_<f0set, f1set, true> withTemperature(float input) const     
    {    
        static_assert(! f2set, "Cannot set field 'Temperature', it is already set");    
        return Builder_<f0set, f1set, true>(this->m_Cap, this->m_Ref, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false, false>;

    float m_Cap;
    float m_Ref;
    float m_Temperature;

private:

    uint8_t id = 1;

    PacketCFCapacitance(float CapIn, float RefIn, float TemperatureIn)
        : m_Cap(CapIn), m_Ref(RefIn), m_Temperature(TemperatureIn)
    {}
};

