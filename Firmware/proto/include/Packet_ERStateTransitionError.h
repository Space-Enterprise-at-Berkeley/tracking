
#pragma once

#include "common.h"

#ifndef BOARD_ER
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ERStateTransitionError 5

class PacketERStateTransitionError 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 5;
        Comms::packetAddUint8(packet, m_ErrorCode);
    }

    static PacketERStateTransitionError fromRawPacket(Comms::Packet *packet)
    {
        uint8_t v_m_ErrorCode = Comms::packetGetUint8(packet, 0);
        return PacketERStateTransitionError(v_m_ErrorCode);
    }

         
template<bool f0set>    
class Builder_    
{    
    private:    
    uint8_t m_ErrorCode;    
    
    public:    
    Builder_(uint8_t ErrorCodeIn)    
        : m_ErrorCode(ErrorCodeIn)    
    {}    
    
    Builder_() {}    
    
    PacketERStateTransitionError build() const    
    {            
        static_assert( f0set, "All fields must be set before building."); // Added static assert    
        return PacketERStateTransitionError(this->m_ErrorCode);    
    }    
    
            
    Builder_<true> withErrorCode(uint8_t input) const     
    {    
        static_assert(! f0set, "Cannot set field 'ErrorCode', it is already set");    
        return Builder_<true>(input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false>;

    uint8_t m_ErrorCode;

private:

    uint8_t id = 5;

    PacketERStateTransitionError(uint8_t ErrorCodeIn)
        : m_ErrorCode(ErrorCodeIn)
    {}
};

