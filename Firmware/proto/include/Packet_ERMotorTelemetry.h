
#pragma once

#include "common.h"

#ifndef BOARD_ER
#ifndef BOARD_GD
#error
#endif
#endif


#define PACKET_ID_ERMotorTelemetry 2

class PacketERMotorTelemetry 
{
public:

    void writeRawPacket(Comms::Packet *packet)
    {
        packet->len = 0;
        packet->id = 2;
        Comms::packetAddFloat(packet, m_EncoderAngle);
        Comms::packetAddFloat(packet, m_AngleSetpoint);
        Comms::packetAddFloat(packet, m_PressureSetpoint);
        Comms::packetAddFloat(packet, m_MotorPower);
        Comms::packetAddFloat(packet, m_PressureControlP);
        Comms::packetAddFloat(packet, m_PressureControlI);
        Comms::packetAddFloat(packet, m_PressureControlD);
    }

    static PacketERMotorTelemetry fromRawPacket(Comms::Packet *packet)
    {
        float v_m_EncoderAngle = Comms::packetGetFloat(packet, 0);
        float v_m_AngleSetpoint = Comms::packetGetFloat(packet, 4);
        float v_m_PressureSetpoint = Comms::packetGetFloat(packet, 8);
        float v_m_MotorPower = Comms::packetGetFloat(packet, 12);
        float v_m_PressureControlP = Comms::packetGetFloat(packet, 16);
        float v_m_PressureControlI = Comms::packetGetFloat(packet, 20);
        float v_m_PressureControlD = Comms::packetGetFloat(packet, 24);
        return PacketERMotorTelemetry(v_m_EncoderAngle, v_m_AngleSetpoint, v_m_PressureSetpoint, v_m_MotorPower, v_m_PressureControlP, v_m_PressureControlI, v_m_PressureControlD);
    }

         
template<bool f0set, bool f1set, bool f2set, bool f3set, bool f4set, bool f5set, bool f6set>    
class Builder_    
{    
    private:    
    float m_EncoderAngle;    
    float m_AngleSetpoint;    
    float m_PressureSetpoint;    
    float m_MotorPower;    
    float m_PressureControlP;    
    float m_PressureControlI;    
    float m_PressureControlD;    
    
    public:    
    Builder_(float EncoderAngleIn, float AngleSetpointIn, float PressureSetpointIn, float MotorPowerIn, float PressureControlPIn, float PressureControlIIn, float PressureControlDIn)    
        : m_EncoderAngle(EncoderAngleIn), m_AngleSetpoint(AngleSetpointIn), m_PressureSetpoint(PressureSetpointIn), m_MotorPower(MotorPowerIn), m_PressureControlP(PressureControlPIn), m_PressureControlI(PressureControlIIn), m_PressureControlD(PressureControlDIn)    
    {}    
    
    Builder_() {}    
    
    PacketERMotorTelemetry build() const    
    {            
        static_assert( f0set &&  f1set &&  f2set &&  f3set &&  f4set &&  f5set &&  f6set, "All fields must be set before building."); // Added static assert    
        return PacketERMotorTelemetry(this->m_EncoderAngle, this->m_AngleSetpoint, this->m_PressureSetpoint, this->m_MotorPower, this->m_PressureControlP, this->m_PressureControlI, this->m_PressureControlD);    
    }    
    
            
    Builder_<true, f1set, f2set, f3set, f4set, f5set, f6set> withEncoderAngle(float input) const     
    {    
        static_assert(! f0set, "Cannot set field 'EncoderAngle', it is already set");    
        return Builder_<true, f1set, f2set, f3set, f4set, f5set, f6set>(input, this->m_AngleSetpoint, this->m_PressureSetpoint, this->m_MotorPower, this->m_PressureControlP, this->m_PressureControlI, this->m_PressureControlD);    
    }    
    
            
    Builder_<f0set, true, f2set, f3set, f4set, f5set, f6set> withAngleSetpoint(float input) const     
    {    
        static_assert(! f1set, "Cannot set field 'AngleSetpoint', it is already set");    
        return Builder_<f0set, true, f2set, f3set, f4set, f5set, f6set>(this->m_EncoderAngle, input, this->m_PressureSetpoint, this->m_MotorPower, this->m_PressureControlP, this->m_PressureControlI, this->m_PressureControlD);    
    }    
    
            
    Builder_<f0set, f1set, true, f3set, f4set, f5set, f6set> withPressureSetpoint(float input) const     
    {    
        static_assert(! f2set, "Cannot set field 'PressureSetpoint', it is already set");    
        return Builder_<f0set, f1set, true, f3set, f4set, f5set, f6set>(this->m_EncoderAngle, this->m_AngleSetpoint, input, this->m_MotorPower, this->m_PressureControlP, this->m_PressureControlI, this->m_PressureControlD);    
    }    
    
            
    Builder_<f0set, f1set, f2set, true, f4set, f5set, f6set> withMotorPower(float input) const     
    {    
        static_assert(! f3set, "Cannot set field 'MotorPower', it is already set");    
        return Builder_<f0set, f1set, f2set, true, f4set, f5set, f6set>(this->m_EncoderAngle, this->m_AngleSetpoint, this->m_PressureSetpoint, input, this->m_PressureControlP, this->m_PressureControlI, this->m_PressureControlD);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, true, f5set, f6set> withPressureControlP(float input) const     
    {    
        static_assert(! f4set, "Cannot set field 'PressureControlP', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, true, f5set, f6set>(this->m_EncoderAngle, this->m_AngleSetpoint, this->m_PressureSetpoint, this->m_MotorPower, input, this->m_PressureControlI, this->m_PressureControlD);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, f4set, true, f6set> withPressureControlI(float input) const     
    {    
        static_assert(! f5set, "Cannot set field 'PressureControlI', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, f4set, true, f6set>(this->m_EncoderAngle, this->m_AngleSetpoint, this->m_PressureSetpoint, this->m_MotorPower, this->m_PressureControlP, input, this->m_PressureControlD);    
    }    
    
            
    Builder_<f0set, f1set, f2set, f3set, f4set, f5set, true> withPressureControlD(float input) const     
    {    
        static_assert(! f6set, "Cannot set field 'PressureControlD', it is already set");    
        return Builder_<f0set, f1set, f2set, f3set, f4set, f5set, true>(this->m_EncoderAngle, this->m_AngleSetpoint, this->m_PressureSetpoint, this->m_MotorPower, this->m_PressureControlP, this->m_PressureControlI, input);    
    }    
    
            
};

    uint8_t getId() const
    {
        return id;
    }

    using Builder = Builder_<false, false, false, false, false, false, false>;

    float m_EncoderAngle;
    float m_AngleSetpoint;
    float m_PressureSetpoint;
    float m_MotorPower;
    float m_PressureControlP;
    float m_PressureControlI;
    float m_PressureControlD;

private:

    uint8_t id = 2;

    PacketERMotorTelemetry(float EncoderAngleIn, float AngleSetpointIn, float PressureSetpointIn, float MotorPowerIn, float PressureControlPIn, float PressureControlIIn, float PressureControlDIn)
        : m_EncoderAngle(EncoderAngleIn), m_AngleSetpoint(AngleSetpointIn), m_PressureSetpoint(PressureSetpointIn), m_MotorPower(MotorPowerIn), m_PressureControlP(PressureControlPIn), m_PressureControlI(PressureControlIIn), m_PressureControlD(PressureControlDIn)
    {}
};

