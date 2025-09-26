
#pragma once

#include "common.h"

#ifndef BOARD_PT
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_PTCalibrationSettings 102

class PacketPTCalibrationSettings 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 102;
        for (size_t i = 0; i < 8; i ++) {
            Comms::packetAddFloat(packet, m_ChannelInfoOffset.at(i));
        }
        for (size_t i = 0; i < 8; i ++) {
            Comms::packetAddFloat(packet, m_ChannelInfoMultiplier.at(i));
        }
    }

    static PacketPTCalibrationSettings fromRawPacket(Comms::Packet *packet)
    {
        std::array<float, 8> v_m_ChannelInfoOffset;
        for (size_t i = 0; i < 32; i += 4) {
            v_m_ChannelInfoOffset[i] = Comms::packetGetFloat(packet, i);
        }

        std::array<float, 8> v_m_ChannelInfoMultiplier;
        for (size_t i = 32; i < 64; i += 4) {
            v_m_ChannelInfoMultiplier[i] = Comms::packetGetFloat(packet, i);
        }

        return PacketPTCalibrationSettings(v_m_ChannelInfoOffset, v_m_ChannelInfoMultiplier);
    }

         
template<bool f0set, bool f1set>    
class Builder_    
{    
    private:    
    std::array<float, 8> m_ChannelInfoOffset;    
    std::array<float, 8> m_ChannelInfoMultiplier;    
    
    public:    
    Builder_(std::array<float, 8> ChannelInfoOffsetIn, std::array<float, 8> ChannelInfoMultiplierIn)    
        : m_ChannelInfoOffset(ChannelInfoOffsetIn), m_ChannelInfoMultiplier(ChannelInfoMultiplierIn)    
    {}    
    
    Builder_() {}    
    
    PacketPTCalibrationSettings build() const    
    {            
        static_assert( f0set &&  f1set, "All fields must be set before building."); // Added static assert    
        return PacketPTCalibrationSettings(this->m_ChannelInfoOffset, this->m_ChannelInfoMultiplier);    
    }    
    
            
    Builder_<true, f1set> withChannelInfoOffset(std::array<float, 8> input) const     
    {    
        static_assert(! f0set, "Cannot set field 'ChannelInfoOffset', it is already set");    
        return Builder_<true, f1set>(input, this->m_ChannelInfoMultiplier);    
    }    
    
            
    Builder_<f0set, true> withChannelInfoMultiplier(std::array<float, 8> input) const     
    {    
        static_assert(! f1set, "Cannot set field 'ChannelInfoMultiplier', it is already set");    
        return Builder_<f0set, true>(this->m_ChannelInfoOffset, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false>;

    std::array<float, 8> m_ChannelInfoOffset;
    std::array<float, 8> m_ChannelInfoMultiplier;

private:

    uint8_t id = 102;

    PacketPTCalibrationSettings(std::array<float, 8> ChannelInfoOffsetIn, std::array<float, 8> ChannelInfoMultiplierIn)
        : m_ChannelInfoOffset(ChannelInfoOffsetIn), m_ChannelInfoMultiplier(ChannelInfoMultiplierIn)
    {}
};

