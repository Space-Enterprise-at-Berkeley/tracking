#include <Arduino.h>
#include <SPI.h>
#include <EthernetUdp.h>
#include <Ethernet.h>
#include <EspComms.h>

int count;
EthernetUDP Udp;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 21};
IPAddress groundStation1(10, 0, 0, 169);
IPAddress ip(10, 0, 0, 25);
int port = 42069;
char packetBuffer[sizeof(Comms::Packet)];

void setup()
{
  Serial.begin(921600);
  Ethernet.init(39);
  Ethernet.begin((uint8_t *)mac, ip, 37, 36, 38, 35);
  Udp.begin(port);
  Serial.println("running setup");
  Udp.beginPacket(groundStation1, port);
}

void loop()
{
  while(1) {
    // Serial.printf("%d\n", digitalRead(35));
    // delay(40);
    Udp.resetSendOffset();
    // Read IO9
    if (Ethernet.detectRead()) {
      Serial.printf("detect packet\n");
      if (Udp.parsePacket()) {
        long bruh = micros();
        Udp.read(packetBuffer, sizeof(Comms::Packet));
        Serial.printf("Recieved: %s delta: %ld \n", packetBuffer, micros() -  bruh);
      }
    }
    Udp.resetSendOffset();
    char tosend[] = "itimelckdatadatadatadata";
    Udp.write((unsigned char *) tosend, 24);
    Udp.endPacket();
  }
}