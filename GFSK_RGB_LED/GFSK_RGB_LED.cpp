/*
  GFSK_RGB_LED.h - Library for rgb led.
  Created by Fabian Kruse
  2016-10-29

  Wiring:
    redPin    = "digital pwm"
    greenPin  = "digital pwm"
    bluePin   = "digital pwm"

*/

#include "Arduino.h"
#include "GFSK_RGB_LED.h"

// all pins must be analog output
GFSK_RGB_LED::GFSK_RGB_LED(int redPin, int greenPin, int bluePin)
{
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
}

void GFSK_RGB_LED::init()
{
  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  pinMode(_bluePin, OUTPUT);

  setColor(255, 255, 255);
}

// value 0-255 for each color
void GFSK_RGB_LED::setColor(unsigned char red, unsigned char green, unsigned char blue)
{
  analogWrite(_redPin, red);
  analogWrite(_greenPin, green);
  analogWrite(_bluePin, blue);
}