
#pragma once

#include "common.h"

#ifndef BOARD_ER
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ERCalibrationSettings 102

class PacketERCalibrationSettings 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 102;
        Comms::packetAddFloat(packet, m_UpstreamPt1Offset);
        Comms::packetAddFloat(packet, m_UpstreamPt1Multiplier);
        Comms::packetAddFloat(packet, m_UpstreamPt2Offset);
        Comms::packetAddFloat(packet, m_UpstreamPt2Multiplier);
        Comms::packetAddFloat(packet, m_DownstreamPt1Offset);
        Comms::packetAddFloat(packet, m_DownstreamPt1Multiplier);
        Comms::packetAddFloat(packet, m_DownstreamPt2Offset);
        Comms::packetAddFloat(packet, m_DownstreamPt2Multiplier);
    }

    static PacketERCalibrationSettings fromRawPacket(Comms::Packet *packet)
    {
        float v_m_UpstreamPt1Offset = Comms::packetGetFloat(packet, 0);
        float v_m_UpstreamPt1Multiplier = Comms::packetGetFloat(packet, 4);
        float v_m_UpstreamPt2Offset = Comms::packetGetFloat(packet, 8);
        float v_m_UpstreamPt2Multiplier = Comms::packetGetFloat(packet, 12);
        float v_m_DownstreamPt1Offset = Comms::packetGetFloat(packet, 16);
        float v_m_DownstreamPt1Multiplier = Comms::packetGetFloat(packet, 20);
        float v_m_DownstreamPt2Offset = Comms::packetGetFloat(packet, 24);
        float v_m_DownstreamPt2Multiplier = Comms::packetGetFloat(packet, 28);
        return PacketERCalibrationSettings(v_m_UpstreamPt1Offset, v_m_UpstreamPt1Multiplier, v_m_UpstreamPt2Offset, v_m_UpstreamPt2Multiplier, v_m_DownstreamPt1Offset, v_m_DownstreamPt1Multiplier, v_m_DownstreamPt2Offset, v_m_DownstreamPt2Multiplier);
    }

         
template<bool f0set, bool f1set, bool f2set, bool f3set, bool f4set, bool f5set, bool f6set, bool f7set>    
class Builder_    
{    
    private:    
    float m_UpstreamPt1Offset;    
    float m_UpstreamPt1Multiplier;    
    float m_UpstreamPt2Offset;    
    float m_UpstreamPt2Multiplier;    
    float m_DownstreamPt1Offset;    
    float m_DownstreamPt1Multiplier;    
    float m_DownstreamPt2Offset;    
    float m_DownstreamPt2Multiplier;    
    
    public:    
    Builder_(float UpstreamPt1OffsetIn, float UpstreamPt1MultiplierIn, float UpstreamPt2OffsetIn, float UpstreamPt2MultiplierIn, float DownstreamPt1OffsetIn, float DownstreamPt1MultiplierIn, float DownstreamPt2OffsetIn, float DownstreamPt2MultiplierIn)    
        : m_UpstreamPt1Offset(UpstreamPt1OffsetIn), m_UpstreamPt1Multiplier(UpstreamPt1MultiplierIn), m_UpstreamPt2Offset(UpstreamPt2OffsetIn), m_UpstreamPt2Multiplier(UpstreamPt2MultiplierIn), m_DownstreamPt1Offset(DownstreamPt1OffsetIn), m_DownstreamPt1Multiplier(DownstreamPt1MultiplierIn), m_DownstreamPt2Offset(DownstreamPt2OffsetIn), m_DownstreamPt2Multiplier(DownstreamPt2MultiplierIn)    
    {}    
    
    Builder_() {}    
    
    PacketERCalibrationSettings build() const    
    {            
        static_assert( f0set &&  f1set &&  f2set &&  f3set &&  f4set &&  f5set &&  f6set &&  f7set, "All fields must be set before building."); // Added static assert    
        return PacketERCalibrationSettings(this->m_UpstreamPt1Offset, this->m_UpstreamPt1Multiplier, this->m_UpstreamPt2Offset, this->m_UpstreamPt2Multiplier, this->m_DownstreamPt1Offset, this->m_DownstreamPt1Multiplier, this->m_DownstreamPt2Offset, this->m_DownstreamPt2Multiplier);    
    }    
    
            
    Builder_<true, f1set, f2set, f3set, f4set, f5set, f6set, f7set> withUpstreamPt1Offset(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'UpstreamPt1Offset', it is already set");    
        return Builder_<true, f1set, f2set, f3set, f4set, f5set, f6set, f7set>(input, this->m_UpstreamPt1Multiplier, this->m_UpstreamPt2Offset, this->m_UpstreamPt2Multiplier, this->m_DownstreamPt1Offset, this->m_DownstreamPt1Multiplier, this->m_DownstreamPt2Offset, this->m_DownstreamPt2Multiplier);    
    }    
    
            
    Builder_<f0set, true, f2set, f3set, f4set, f5set, f6set, f7set> withUpstreamPt1Multiplier(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'UpstreamPt1Multiplier', it is already set");    
        return Builder_<f0set, true, f2set, f3set, f4set, f5set, f6set, f7set>(this->m_UpstreamPt1Offset, input, this->m_UpstreamPt2Offset, this->m_UpstreamPt2Multiplier, this->m_DownstreamPt1Offset, this->m_DownstreamPt1Multiplier, this->m_DownstreamPt2Offset, this->m_DownstreamPt2Multiplier);    
    }    
    
            
    Builder_<f0set, f1set, true, f3set, f4set, f5set, f6set, f7set> withUpstreamPt2Offset(float input) const     
    {    
        static_assert(! f2set, "Cannot set field 'UpstreamPt2Offset', it is already set");    
        return Builder_<f0set, f1set, true, f3set, f4set, f5set, f6set, f7set>(this->m_UpstreamPt1Offset, this->m_UpstreamPt1Multiplier, input, this->m_UpstreamPt2Multiplier, this->m_DownstreamPt1Offset, this->m_DownstreamPt1Multiplier, this->m_DownstreamPt2Offset, this->m_DownstreamPt2Multiplier);    
    }    
    
            
    Builder_<f0set, f1set, f2set, true, f4set, f5set, f6set, f7set> withUpstreamPt2Multiplier(float input) const     
    {    
        static_assert(! f3set, "Cannot set field 'UpstreamPt2Multiplier', it is already set");    
        return Builder_<f0set, f1set, f2set, true, f4set, f5set, f6set, f7set>(this->m_UpstreamPt1Offset, this->m_UpstreamPt1Multiplier, this->m_UpstreamPt2Offset, input, this->m_DownstreamPt1Offset, this->m_DownstreamPt1Multiplier, this->m_DownstreamPt2Offset, this->m_DownstreamPt2Multiplier);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, true, f5set, f6set, f7set> withDownstreamPt1Offset(float input) const     
    {    
        static_assert(! f4set, "Cannot set field 'DownstreamPt1Offset', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, true, f5set, f6set, f7set>(this->m_UpstreamPt1Offset, this->m_UpstreamPt1Multiplier, this->m_UpstreamPt2Offset, this->m_UpstreamPt2Multiplier, input, this->m_DownstreamPt1Multiplier, this->m_DownstreamPt2Offset, this->m_DownstreamPt2Multiplier);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, f4set, true, f6set, f7set> withDownstreamPt1Multiplier(float input) const     
    {    
        static_assert(! f5set, "Cannot set field 'DownstreamPt1Multiplier', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, f4set, true, f6set, f7set>(this->m_UpstreamPt1Offset, this->m_UpstreamPt1Multiplier, this->m_UpstreamPt2Offset, this->m_UpstreamPt2Multiplier, this->m_DownstreamPt1Offset, input, this->m_DownstreamPt2Offset, this->m_DownstreamPt2Multiplier);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, f4set, f5set, true, f7set> withDownstreamPt2Offset(float input) const     
    {    
        static_assert(! f6set, "Cannot set field 'DownstreamPt2Offset', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, f4set, f5set, true, f7set>(this->m_UpstreamPt1Offset, this->m_UpstreamPt1Multiplier, this->m_UpstreamPt2Offset, this->m_UpstreamPt2Multiplier, this->m_DownstreamPt1Offset, this->m_DownstreamPt1Multiplier, input, this->m_DownstreamPt2Multiplier);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, f4set, f5set, f6set, true> withDownstreamPt2Multiplier(float input) const     
    {    
        static_assert(! f7set, "Cannot set field 'DownstreamPt2Multiplier', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, f4set, f5set, f6set, true>(this->m_UpstreamPt1Offset, this->m_UpstreamPt1Multiplier, this->m_UpstreamPt2Offset, this->m_UpstreamPt2Multiplier, this->m_DownstreamPt1Offset, this->m_DownstreamPt1Multiplier, this->m_DownstreamPt2Offset, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false, false, false, false, false, false, false>;

    float m_UpstreamPt1Offset;
    float m_UpstreamPt1Multiplier;
    float m_UpstreamPt2Offset;
    float m_UpstreamPt2Multiplier;
    float m_DownstreamPt1Offset;
    float m_DownstreamPt1Multiplier;
    float m_DownstreamPt2Offset;
    float m_DownstreamPt2Multiplier;

private:

    uint8_t id = 102;

    PacketERCalibrationSettings(float UpstreamPt1OffsetIn, float UpstreamPt1MultiplierIn, float UpstreamPt2OffsetIn, float UpstreamPt2MultiplierIn, float DownstreamPt1OffsetIn, float DownstreamPt1MultiplierIn, float DownstreamPt2OffsetIn, float DownstreamPt2MultiplierIn)
        : m_UpstreamPt1Offset(UpstreamPt1OffsetIn), m_UpstreamPt1Multiplier(UpstreamPt1MultiplierIn), m_UpstreamPt2Offset(UpstreamPt2OffsetIn), m_UpstreamPt2Multiplier(UpstreamPt2MultiplierIn), m_DownstreamPt1Offset(DownstreamPt1OffsetIn), m_DownstreamPt1Multiplier(DownstreamPt1MultiplierIn), m_DownstreamPt2Offset(DownstreamPt2OffsetIn), m_DownstreamPt2Multiplier(DownstreamPt2MultiplierIn)
    {}
};

