
#pragma once

#include "common.h"

#ifndef BOARD_ER
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ERTemperatures 9

class PacketERTemperatures 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 9;
        Comms::packetAddFloat(packet, m_BoardTemp1);
        Comms::packetAddFloat(packet, m_BoardTemp2);
        Comms::packetAddFloat(packet, m_MotorTemp);
    }

    static PacketERTemperatures fromRawPacket(Comms::Packet *packet)
    {
        float v_m_BoardTemp1 = Comms::packetGetFloat(packet, 0);
        float v_m_BoardTemp2 = Comms::packetGetFloat(packet, 4);
        float v_m_MotorTemp = Comms::packetGetFloat(packet, 8);
        return PacketERTemperatures(v_m_BoardTemp1, v_m_BoardTemp2, v_m_MotorTemp);
    }

         
template<bool f0set, bool f1set, bool f2set>    
class Builder_    
{    
    private:    
    float m_BoardTemp1;    
    float m_BoardTemp2;    
    float m_MotorTemp;    
    
    public:    
    Builder_(float BoardTemp1In, float BoardTemp2In, float MotorTempIn)    
        : m_BoardTemp1(BoardTemp1In), m_BoardTemp2(BoardTemp2In), m_MotorTemp(MotorTempIn)    
    {}    
    
    Builder_() {}    
    
    PacketERTemperatures build() const    
    {            
        static_assert( f0set &&  f1set &&  f2set, "All fields must be set before building."); // Added static assert    
        return PacketERTemperatures(this->m_BoardTemp1, this->m_BoardTemp2, this->m_MotorTemp);    
    }    
    
            
    Builder_<true, f1set, f2set> withBoardTemp1(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'BoardTemp1', it is already set");    
        return Builder_<true, f1set, f2set>(input, this->m_BoardTemp2, this->m_MotorTemp);    
    }    
    
            
    Builder_<f0set, true, f2set> withBoardTemp2(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'BoardTemp2', it is already set");    
        return Builder_<f0set, true, f2set>(this->m_BoardTemp1, input, this->m_MotorTemp);    
    }    
    
            
    Builder_<f0set, f1set, true> withMotorTemp(float input) const     
    {    
        static_assert(! f2set, "Cannot set field 'MotorTemp', it is already set");    
        return Builder_<f0set, f1set, true>(this->m_BoardTemp1, this->m_BoardTemp2, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false, false>;

    float m_BoardTemp1;
    float m_BoardTemp2;
    float m_MotorTemp;

private:

    uint8_t id = 9;

    PacketERTemperatures(float BoardTemp1In, float BoardTemp2In, float MotorTempIn)
        : m_BoardTemp1(BoardTemp1In), m_BoardTemp2(BoardTemp2In), m_MotorTemp(MotorTempIn)
    {}
};

