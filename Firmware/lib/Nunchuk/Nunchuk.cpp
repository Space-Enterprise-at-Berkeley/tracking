/*
 * ArduinoNunchuk.cpp - Improved Wii Nunchuk library for Arduino
 *
 * Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *
 * Based on the following resources:
 *   http://www.windmeadow.com/node/42
 *   http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
 *   http://wiibrew.org/wiki/Wiimote/Extension_Controllers
 *
 */

#include "Nunchuk.h"

void Nunchuk::init(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);

  Nunchuk::_sendByte(0x55, 0xF0);
  delay(10);
  Nunchuk::_sendByte(0x00, 0xFB);

  Nunchuk::update();
}

void Nunchuk::init()
{
  Wire.begin();

  Nunchuk::_sendByte(0x55, 0xF0);
  delay(10);
  Nunchuk::_sendByte(0x00, 0xFB);

  Nunchuk::update();
}


void Nunchuk::update()
{
  int count = 0;
  int values[6];

  if (Wire.requestFrom(0x52, 6) != 6)
  {
    Nunchuk::connected = false;
    return;
  } else {
    Nunchuk::connected = true;
  }

  while(Wire.available())
  {
    values[count] = Wire.read();
    count++;
  }

  Nunchuk::analogX = values[0];
  Nunchuk::analogY = values[1];
  Nunchuk::accelX = (values[2] << 2) | ((values[5] >> 2) & 3);
  Nunchuk::accelY = (values[3] << 2) | ((values[5] >> 4) & 3);
  Nunchuk::accelZ = (values[4] << 2) | ((values[5] >> 6) & 3);
  Nunchuk::zButton = !((values[5] >> 0) & 1);
  Nunchuk::cButton = !((values[5] >> 1) & 1);

  Nunchuk::_sendByte(0x00, 0x00);
}

void Nunchuk::_sendByte(byte data, byte location)
{
  Wire.beginTransmission(0x52);

  Wire.write(location);
  Wire.write(data);

  Wire.endTransmission();

  //delay(10);
}