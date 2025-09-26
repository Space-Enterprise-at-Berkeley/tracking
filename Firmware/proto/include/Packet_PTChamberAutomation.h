
#pragma once

#include "common.h"

#ifndef BOARD_PT
#ifndef BOARD_GD
#ifndef BOARD_AC
#error
#endif
#endif
#endif


#define PACKET_ID_PTChamberAutomation 3

class PacketPTChamberAutomation 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 3;
        Comms::packetAddFloat(packet, m_ChamberP);
    }

    static PacketPTChamberAutomation fromRawPacket(Comms::Packet *packet)
    {
        float v_m_ChamberP = Comms::packetGetFloat(packet, 0);
        return PacketPTChamberAutomation(v_m_ChamberP);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    float m_ChamberP;    
    
    public:    
    Builder_(float ChamberPIn)    
        : m_ChamberP(ChamberPIn)    
    {}    
    
    Builder_() {}    
    
    PacketPTChamberAutomation build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketPTChamberAutomation(this->m_ChamberP);    
    }    
    
            
    Builder_<true> withChamberP(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'ChamberP', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    float m_ChamberP;

private:

    uint8_t id = 3;

    PacketPTChamberAutomation(float ChamberPIn)
        : m_ChamberP(ChamberPIn)
    {}
};

