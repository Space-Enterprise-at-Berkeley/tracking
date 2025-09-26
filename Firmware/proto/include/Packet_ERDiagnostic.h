
#pragma once

#include "common.h"

#ifndef BOARD_ER
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ERDiagnostic 4

class PacketERDiagnostic 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 4;
        Comms::packetAddUint8(packet, m_MotorDirPass);
        Comms::packetAddUint8(packet, m_ServoDirPass);
    }

    static PacketERDiagnostic fromRawPacket(Comms::Packet *packet)
    {
        uint8_t v_m_MotorDirPass = Comms::packetGetUint8(packet, 0);
        uint8_t v_m_ServoDirPass = Comms::packetGetUint8(packet, 1);
        return PacketERDiagnostic(v_m_MotorDirPass, v_m_ServoDirPass);
    }

         
template<bool f0set, bool f1set>    
class Builder_    
{    
    private:    
    uint8_t m_MotorDirPass;    
    uint8_t m_ServoDirPass;    
    
    public:    
    Builder_(uint8_t MotorDirPassIn, uint8_t ServoDirPassIn)    
        : m_MotorDirPass(MotorDirPassIn), m_ServoDirPass(ServoDirPassIn)    
    {}    
    
    Builder_() {}    
    
    PacketERDiagnostic build() const    
    {            
        static_assert( f0set &&  f1set, "All fields must be set before building."); // Added static assert    
        return PacketERDiagnostic(this->m_MotorDirPass, this->m_ServoDirPass);    
    }    
    
            
    Builder_<true, f1set> withMotorDirPass(uint8_t input) const     
    {    
        static_assert(! f0set, "Cannot set field 'MotorDirPass', it is already set");    
        return Builder_<true, f1set>(input, this->m_ServoDirPass);    
    }    
    
            
    Builder_<f0set, true> withServoDirPass(uint8_t input) const     
    {    
        static_assert(! f1set, "Cannot set field 'ServoDirPass', it is already set");    
        return Builder_<f0set, true>(this->m_MotorDirPass, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false>;

    uint8_t m_MotorDirPass;
    uint8_t m_ServoDirPass;

private:

    uint8_t id = 4;

    PacketERDiagnostic(uint8_t MotorDirPassIn, uint8_t ServoDirPassIn)
        : m_MotorDirPass(MotorDirPassIn), m_ServoDirPass(ServoDirPassIn)
    {}
};

