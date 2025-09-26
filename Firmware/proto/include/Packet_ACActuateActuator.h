
#pragma once

#include "common.h"

#ifndef BOARD_GD
#ifndef BOARD_AC
#error
#endif
#endif


#define PACKET_ID_ACActuateActuator 100

class PacketACActuateActuator 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 100;
        Comms::packetAddUint8(packet, m_ActuatorNumber);
        Comms::packetAddUint8(packet, m_Action);
        Comms::packetAddUint32(packet, m_ActuateTime);
    }

    static PacketACActuateActuator fromRawPacket(Comms::Packet *packet)
    {
        uint8_t v_m_ActuatorNumber = Comms::packetGetUint8(packet, 0);
        ACActuatorActions v_m_Action = static_cast<ACActuatorActions>(Comms::packetGetUint8(packet, 1));
        uint32_t v_m_ActuateTime = Comms::packetGetUint32(packet, 2);
        return PacketACActuateActuator(v_m_ActuatorNumber, v_m_Action, v_m_ActuateTime);
    }

         
template<bool f0set, bool f1set, bool f2set>    
class Builder_    
{    
    private:    
    uint8_t m_ActuatorNumber;    
    ACActuatorActions m_Action;    
    uint32_t m_ActuateTime;    
    
    public:    
    Builder_(uint8_t ActuatorNumberIn, ACActuatorActions ActionIn, uint32_t ActuateTimeIn)    
        : m_ActuatorNumber(ActuatorNumberIn), m_Action(ActionIn), m_ActuateTime(ActuateTimeIn)    
    {}    
    
    Builder_() {}    
    
    PacketACActuateActuator build() const    
    {            
        static_assert( f0set &&  f1set &&  f2set, "All fields must be set before building."); // Added static assert    
        return PacketACActuateActuator(this->m_ActuatorNumber, this->m_Action, this->m_ActuateTime);    
    }    
    
            
    Builder_<true, f1set, f2set> withActuatorNumber(uint8_t input) const     
    {    
        static_assert(! f0set, "Cannot set field 'ActuatorNumber', it is already set");    
        return Builder_<true, f1set, f2set>(input, this->m_Action, this->m_ActuateTime);    
    }    
    
            
    Builder_<f0set, true, f2set> withAction(ACActuatorActions input) const     
    {    
        static_assert(! f1set, "Cannot set field 'Action', it is already set");    
        return Builder_<f0set, true, f2set>(this->m_ActuatorNumber, input, this->m_ActuateTime);    
    }    
    
            
    Builder_<f0set, f1set, true> withActuateTime(uint32_t input) const     
    {    
        static_assert(! f2set, "Cannot set field 'ActuateTime', it is already set");    
        return Builder_<f0set, f1set, true>(this->m_ActuatorNumber, this->m_Action, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false, false>;

    uint8_t m_ActuatorNumber;
    ACActuatorActions m_Action;
    uint32_t m_ActuateTime;

private:

    uint8_t id = 100;

    PacketACActuateActuator(uint8_t ActuatorNumberIn, ACActuatorActions ActionIn, uint32_t ActuateTimeIn)
        : m_ActuatorNumber(ActuatorNumberIn), m_Action(ActionIn), m_ActuateTime(ActuateTimeIn)
    {}
};

