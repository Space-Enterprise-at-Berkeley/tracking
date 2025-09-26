
#pragma once

#include "common.h"

#ifndef BOARD_ER
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ERConfig 3

class PacketERConfig 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 3;
        Comms::packetAddFloat(packet, m_PressureSetpointStart);
        Comms::packetAddFloat(packet, m_POuterNominal);
        Comms::packetAddFloat(packet, m_IOuterNominal);
        Comms::packetAddFloat(packet, m_DOuterNominal);
        Comms::packetAddFloat(packet, m_PInner);
        Comms::packetAddFloat(packet, m_IInner);
        Comms::packetAddFloat(packet, m_DInner);
        Comms::packetAddFloat(packet, m_PressureSetpointDropRate);
        Comms::packetAddFloat(packet, m_PressureSetpointMinimum);
        Comms::packetAddFloat(packet, m_StaticPressureSetpoint);
    }

    static PacketERConfig fromRawPacket(Comms::Packet *packet)
    {
        float v_m_PressureSetpointStart = Comms::packetGetFloat(packet, 0);
        float v_m_POuterNominal = Comms::packetGetFloat(packet, 4);
        float v_m_IOuterNominal = Comms::packetGetFloat(packet, 8);
        float v_m_DOuterNominal = Comms::packetGetFloat(packet, 12);
        float v_m_PInner = Comms::packetGetFloat(packet, 16);
        float v_m_IInner = Comms::packetGetFloat(packet, 20);
        float v_m_DInner = Comms::packetGetFloat(packet, 24);
        float v_m_PressureSetpointDropRate = Comms::packetGetFloat(packet, 28);
        float v_m_PressureSetpointMinimum = Comms::packetGetFloat(packet, 32);
        float v_m_StaticPressureSetpoint = Comms::packetGetFloat(packet, 36);
        return PacketERConfig(v_m_PressureSetpointStart, v_m_POuterNominal, v_m_IOuterNominal, v_m_DOuterNominal, v_m_PInner, v_m_IInner, v_m_DInner, v_m_PressureSetpointDropRate, v_m_PressureSetpointMinimum, v_m_StaticPressureSetpoint);
    }

         
template<bool f0set, bool f1set, bool f2set, bool f3set, bool f4set, bool f5set, bool f6set, bool f7set, bool f8set, bool f9set>    
class Builder_    
{    
    private:    
    float m_PressureSetpointStart;    
    float m_POuterNominal;    
    float m_IOuterNominal;    
    float m_DOuterNominal;    
    float m_PInner;    
    float m_IInner;    
    float m_DInner;    
    float m_PressureSetpointDropRate;    
    float m_PressureSetpointMinimum;    
    float m_StaticPressureSetpoint;    
    
    public:    
    Builder_(float PressureSetpointStartIn, float POuterNominalIn, float IOuterNominalIn, float DOuterNominalIn, float PInnerIn, float IInnerIn, float DInnerIn, float PressureSetpointDropRateIn, float PressureSetpointMinimumIn, float StaticPressureSetpointIn)    
        : m_PressureSetpointStart(PressureSetpointStartIn), m_POuterNominal(POuterNominalIn), m_IOuterNominal(IOuterNominalIn), m_DOuterNominal(DOuterNominalIn), m_PInner(PInnerIn), m_IInner(IInnerIn), m_DInner(DInnerIn), m_PressureSetpointDropRate(PressureSetpointDropRateIn), m_PressureSetpointMinimum(PressureSetpointMinimumIn), m_StaticPressureSetpoint(StaticPressureSetpointIn)    
    {}    
    
    Builder_() {}    
    
    PacketERConfig build() const    
    {            
        static_assert( f0set &&  f1set &&  f2set &&  f3set &&  f4set &&  f5set &&  f6set &&  f7set &&  f8set &&  f9set, "All fields must be set before building."); // Added static assert    
        return PacketERConfig(this->m_PressureSetpointStart, this->m_POuterNominal, this->m_IOuterNominal, this->m_DOuterNominal, this->m_PInner, this->m_IInner, this->m_DInner, this->m_PressureSetpointDropRate, this->m_PressureSetpointMinimum, this->m_StaticPressureSetpoint);    
    }    
    
            
    Builder_<true, f1set, f2set, f3set, f4set, f5set, f6set, f7set, f8set, f9set> withPressureSetpointStart(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'PressureSetpointStart', it is already set");    
        return Builder_<true, f1set, f2set, f3set, f4set, f5set, f6set, f7set, f8set, f9set>(input, this->m_POuterNominal, this->m_IOuterNominal, this->m_DOuterNominal, this->m_PInner, this->m_IInner, this->m_DInner, this->m_PressureSetpointDropRate, this->m_PressureSetpointMinimum, this->m_StaticPressureSetpoint);    
    }    
    
            
    Builder_<f0set, true, f2set, f3set, f4set, f5set, f6set, f7set, f8set, f9set> withPOuterNominal(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'POuterNominal', it is already set");    
        return Builder_<f0set, true, f2set, f3set, f4set, f5set, f6set, f7set, f8set, f9set>(this->m_PressureSetpointStart, input, this->m_IOuterNominal, this->m_DOuterNominal, this->m_PInner, this->m_IInner, this->m_DInner, this->m_PressureSetpointDropRate, this->m_PressureSetpointMinimum, this->m_StaticPressureSetpoint);    
    }    
    
            
    Builder_<f0set, f1set, true, f3set, f4set, f5set, f6set, f7set, f8set, f9set> withIOuterNominal(float input) const     
    {    
        static_assert(! f2set, "Cannot set field 'IOuterNominal', it is already set");    
        return Builder_<f0set, f1set, true, f3set, f4set, f5set, f6set, f7set, f8set, f9set>(this->m_PressureSetpointStart, this->m_POuterNominal, input, this->m_DOuterNominal, this->m_PInner, this->m_IInner, this->m_DInner, this->m_PressureSetpointDropRate, this->m_PressureSetpointMinimum, this->m_StaticPressureSetpoint);    
    }    
    
            
    Builder_<f0set, f1set, f2set, true, f4set, f5set, f6set, f7set, f8set, f9set> withDOuterNominal(float input) const     
    {    
        static_assert(! f3set, "Cannot set field 'DOuterNominal', it is already set");    
        return Builder_<f0set, f1set, f2set, true, f4set, f5set, f6set, f7set, f8set, f9set>(this->m_PressureSetpointStart, this->m_POuterNominal, this->m_IOuterNominal, input, this->m_PInner, this->m_IInner, this->m_DInner, this->m_PressureSetpointDropRate, this->m_PressureSetpointMinimum, this->m_StaticPressureSetpoint);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, true, f5set, f6set, f7set, f8set, f9set> withPInner(float input) const     
    {    
        static_assert(! f4set, "Cannot set field 'PInner', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, true, f5set, f6set, f7set, f8set, f9set>(this->m_PressureSetpointStart, this->m_POuterNominal, this->m_IOuterNominal, this->m_DOuterNominal, input, this->m_IInner, this->m_DInner, this->m_PressureSetpointDropRate, this->m_PressureSetpointMinimum, this->m_StaticPressureSetpoint);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, f4set, true, f6set, f7set, f8set, f9set> withIInner(float input) const     
    {    
        static_assert(! f5set, "Cannot set field 'IInner', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, f4set, true, f6set, f7set, f8set, f9set>(this->m_PressureSetpointStart, this->m_POuterNominal, this->m_IOuterNominal, this->m_DOuterNominal, this->m_PInner, input, this->m_DInner, this->m_PressureSetpointDropRate, this->m_PressureSetpointMinimum, this->m_StaticPressureSetpoint);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, f4set, f5set, true, f7set, f8set, f9set> withDInner(float input) const     
    {    
        static_assert(! f6set, "Cannot set field 'DInner', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, f4set, f5set, true, f7set, f8set, f9set>(this->m_PressureSetpointStart, this->m_POuterNominal, this->m_IOuterNominal, this->m_DOuterNominal, this->m_PInner, this->m_IInner, input, this->m_PressureSetpointDropRate, this->m_PressureSetpointMinimum, this->m_StaticPressureSetpoint);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, f4set, f5set, f6set, true, f8set, f9set> withPressureSetpointDropRate(float input) const     
    {    
        static_assert(! f7set, "Cannot set field 'PressureSetpointDropRate', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, f4set, f5set, f6set, true, f8set, f9set>(this->m_PressureSetpointStart, this->m_POuterNominal, this->m_IOuterNominal, this->m_DOuterNominal, this->m_PInner, this->m_IInner, this->m_DInner, input, this->m_PressureSetpointMinimum, this->m_StaticPressureSetpoint);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, f4set, f5set, f6set, f7set, true, f9set> withPressureSetpointMinimum(float input) const     
    {    
        static_assert(! f8set, "Cannot set field 'PressureSetpointMinimum', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, f4set, f5set, f6set, f7set, true, f9set>(this->m_PressureSetpointStart, this->m_POuterNominal, this->m_IOuterNominal, this->m_DOuterNominal, this->m_PInner, this->m_IInner, this->m_DInner, this->m_PressureSetpointDropRate, input, this->m_StaticPressureSetpoint);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, f4set, f5set, f6set, f7set, f8set, true> withStaticPressureSetpoint(float input) const     
    {    
        static_assert(! f9set, "Cannot set field 'StaticPressureSetpoint', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, f4set, f5set, f6set, f7set, f8set, true>(this->m_PressureSetpointStart, this->m_POuterNominal, this->m_IOuterNominal, this->m_DOuterNominal, this->m_PInner, this->m_IInner, this->m_DInner, this->m_PressureSetpointDropRate, this->m_PressureSetpointMinimum, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false, false, false, false, false, false, false, false, false>;

    float m_PressureSetpointStart;
    float m_POuterNominal;
    float m_IOuterNominal;
    float m_DOuterNominal;
    float m_PInner;
    float m_IInner;
    float m_DInner;
    float m_PressureSetpointDropRate;
    float m_PressureSetpointMinimum;
    float m_StaticPressureSetpoint;

private:

    uint8_t id = 3;

    PacketERConfig(float PressureSetpointStartIn, float POuterNominalIn, float IOuterNominalIn, float DOuterNominalIn, float PInnerIn, float IInnerIn, float DInnerIn, float PressureSetpointDropRateIn, float PressureSetpointMinimumIn, float StaticPressureSetpointIn)
        : m_PressureSetpointStart(PressureSetpointStartIn), m_POuterNominal(POuterNominalIn), m_IOuterNominal(IOuterNominalIn), m_DOuterNominal(DOuterNominalIn), m_PInner(PInnerIn), m_IInner(IInnerIn), m_DInner(DInnerIn), m_PressureSetpointDropRate(PressureSetpointDropRateIn), m_PressureSetpointMinimum(PressureSetpointMinimumIn), m_StaticPressureSetpoint(StaticPressureSetpointIn)
    {}
};

