#include <Arduino.h>
#include <SPI.h>
#include <EthernetUdp.h>
#include <Ethernet.h>

const int DRV_EN = 11;
const int DRV_FAULT = 12;

const int DRV_CS = 10;
const int MADC_CS = 13;
const int ETH_CS = 39;
const int PTADC_CS = 21;


const int MOTOR_MISO = 8;
const int MOTOR_MOSI = 9;
const int MOTOR_SCLK = 7;

const int ETH_MISO = 37;
const int ETH_MOSI = 36;
const int ETH_SCLK = 38;
const int ETH_INTn = 35;


int DRVSPISpeed = 1000000;
int ADCSPISpeed = 5000000;
volatile bool motorDriverFault = false;
uint8_t SPIBUFF[2]; // spi buffer for all SPI except ethernet.
SPIClass *ethSPI = NULL;
SPIClass *motorSPI = NULL;

EthernetUDP Udp;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x99};
IPAddress groundStation1(10, 0, 0, 169);
IPAddress ip(10, 0, 0, 99);
int port = 42069;

void sendSPICommand(void* dataBuffer, int numBytes, SPIClass* spi, int csPin, int clkSpeed, int spiMode) {
  spi->beginTransaction(SPISettings(clkSpeed, MSBFIRST, spiMode));
  digitalWrite(csPin, LOW);
  spi->transfer((uint8_t *)dataBuffer, numBytes);
  spi->endTransaction();
  digitalWrite(csPin, HIGH);
}

float readADC(SPIClass* spi, uint8_t csPin, int8_t channel) {
  if ((channel > 3) || (channel < 0)) {
      Serial.println("bad channel index");
      return 0;
  }
  SPIBUFF[0] = 0;
  SPIBUFF[0] |= (channel << 3);
  SPIBUFF[0] &= 0b00011000;
  SPIBUFF[1] = 0;
  sendSPICommand(SPIBUFF, 2, spi, csPin, ADCSPISpeed, SPI_MODE0);

  uint16_t val = ((SPIBUFF[0] & 0b00001111) << 8) + SPIBUFF[1];
//   uint16_t val = SPIBUFF[0];
  
  float f = (((float) val) / 4096.0) * 5.0;
//   f = (5 - f) / (20*0.005);
  return (float) val;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("PT ADC / current DRV Test");
  Serial.println("========");
  Serial.println();

  Ethernet.init(39);

  ethSPI = new SPIClass(FSPI);
  motorSPI = new SPIClass(HSPI);

  ethSPI->begin(ETH_SCLK, ETH_MISO, ETH_MOSI);
  motorSPI->begin(MOTOR_SCLK, MOTOR_MISO, MOTOR_MOSI);

  pinMode(MADC_CS, OUTPUT);
  digitalWrite(MADC_CS, HIGH);
  pinMode(DRV_CS, OUTPUT);
  digitalWrite(DRV_CS, HIGH);
  pinMode(DRV_EN, OUTPUT);
  digitalWrite(DRV_EN, LOW);
  pinMode(PTADC_CS, OUTPUT);
  digitalWrite(PTADC_CS, HIGH);
  pinMode(ETH_CS, OUTPUT);
  digitalWrite(ETH_CS, HIGH);


  Ethernet.begin((uint8_t *)mac, ip, ETH_MISO, ETH_MOSI, ETH_SCLK, ETH_INTn);
  Udp.begin(port);

  Udp.beginPacket(groundStation1, port);
}

void loop()
{
    // Serial.printf("M  ADC 0: %f ", readADC(motorSPI, MADC_CS, 0));
    // Serial.printf("M  ADC 1: %f ", readADC(motorSPI, MADC_CS, 1));
    // Serial.printf("M  ADC 2: %f ", readADC(motorSPI, MADC_CS, 2));
    // Serial.printf("M  ADC 3: %f\n", readADC(motorSPI, MADC_CS, 3));
    Serial.printf("PT0: %f ", readADC(ethSPI, PTADC_CS, 0));
    Serial.printf("PT1: %f ", readADC(ethSPI, PTADC_CS, 1));
    Serial.printf("PT2: %f ", readADC(ethSPI, PTADC_CS, 2));
    Serial.printf("PT3: %f\n", readADC(ethSPI, PTADC_CS, 3));

    Udp.resetSendOffset();
    char tosend[] = "itimelckdatadatadatadata";
    Udp.write((unsigned char *) tosend, 24);
    Udp.endPacket();

    delay(10);
}

