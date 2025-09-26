#include "Ducers.h"
#include "EEPROM.h"

//TODO - zeroing for PTs

namespace Ducers {
    ADS8167 adc1;
    SPIClass *spi2; 
    

    uint32_t ptUpdatePeriod = 50 * 1000;
    Comms::Packet ptPacket = {.id = 2};
    float data[8];
    float offset[8];
    bool persistentOffset = true;


    // float pressurantPTValue = 0.0;
    // float loxTankPTValue = 0.0;
    // float fuelTankPTValue = 0.0;
    // float loxInjectorPTValue = 0.0;
    // float fuelInjectorPTValue = 0.0;
    // float loxDomePTValue = 0.0;
    // float fuelDomePTValue = 0.0;

    void handleFastReadPacket(Comms::Packet tmp, uint8_t ip) {
        if(tmp.data[0]) {
            ptUpdatePeriod = 1 * 1000;
        } else {
            ptUpdatePeriod = 100 * 1000;
        }
    }

    float interpolate1000(uint16_t rawValue) {
        // TODO multiply rawValue by 2
        float tmp = (float) (rawValue - 6406);
        return tmp / 51.7;
    }

    float interpolate5000(uint16_t rawValue) {
        float tmp = (float) rawValue;
        return tmp / 12.97;
    }

    void zeroChannel(uint8_t channel){
        offset[channel] = -data[channel] + offset[channel];
        Serial.println("zeroed channel " + String(channel) + " to " + String(offset[channel]));
        if (persistentOffset){
            EEPROM.begin(8*sizeof(float));
            EEPROM.put(channel*sizeof(float),offset[channel]);
            EEPROM.end();
        }
    }

    void onZeroCommand(Comms::Packet packet, uint8_t ip){
        uint8_t channel = Comms::packetGetUint8(&packet, 0);
        zeroChannel(channel);
        return;
    }

    void init() {
        // Comms::registerCallback(140, handleFastReadPacket);
        spi2 = new SPIClass(HSPI);
        spi2->begin(41, 42, 40, 39);
        adc1.init(spi2, 39, 38);

        adc1.setAllInputsSeparate();
        adc1.enableOTFMode();

        Comms::registerCallback(100, onZeroCommand);

        //load offset from flash or set to 0
        if (persistentOffset){
            EEPROM.begin(8*sizeof(float));
            for (int i = 0; i < 8; i++){
                EEPROM.get(i*sizeof(float),offset[i]);
                if (isnan(offset[i])){
                    offset[i] = 0;
                }
            }
            EEPROM.end();
        } else {
            for (int i = 0; i < 8; i++){
                offset[i] = 0;
            }
        }

    }


    float samplePT(uint8_t channel) {
        adc1.setChannel(channel);
        data[channel] = interpolate1000(adc1.readChannelOTF(channel)) + offset[channel];
        return data[channel];
    }

    float noSamplePT(uint8_t channel){
        return data[channel];
    }

    uint32_t task_ptSample() {
        // read from all 8 PTs in sequence
        
        adc1.setChannel(0); // switch mux back to channel 0
        data[0] = interpolate1000(adc1.readChannelOTF(1)) + offset[0];
        data[1] = interpolate1000(adc1.readChannelOTF(2)) + offset[1];
        data[2] = interpolate1000(adc1.readChannelOTF(3)) + offset[2];
        data[3] = interpolate1000(adc1.readChannelOTF(4)) + offset[3];
        data[4] = interpolate1000(adc1.readChannelOTF(5)) + offset[4];
        data[5] = interpolate1000(adc1.readChannelOTF(6)) + offset[5]; 
        data[6] = interpolate1000(adc1.readChannelOTF(7)) + offset[6];
        data[7] = interpolate1000(adc1.readChannelOTF(0)) + offset[7];

        DEBUG("Read all PTs\n");
        DEBUG_FLUSH();

        // emit a packet with data
        ptPacket.len = 0;
        for (int i = 0; i < 8; i++){
            Comms::packetAddFloat(&ptPacket, data[i]);
        }

        Comms::emitPacketToGS(&ptPacket);
        // Comms::emitPacket(&ptPacket, &RADIO_SERIAL, "\r\n\n", 3);
        // return the next execution time
        DEBUG("PT Packet Sent\n");
        DEBUG_FLUSH();

        return ptUpdatePeriod;
    }

    void print_ptSample(){
        for (int i = 0; i < 8; i ++){
            Serial.print("  PT"+String(i)+": " + String(data[i]));
        }
        Serial.println();
    }

};
