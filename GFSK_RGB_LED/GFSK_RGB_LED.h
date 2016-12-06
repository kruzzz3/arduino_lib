#ifndef GFSK_RGB_LED_h
#define GFSK_RGB_LED_h

#include "Arduino.h"

class GFSK_RGB_LED
{
  public:
    GFSK_RGB_LED(int redPin, int greenPin, int bluePin);
    void init();
    void setColor(unsigned char red, unsigned char green, unsigned char blue);
  private:
    int _redPin;
    int _greenPin;
    int _bluePin;
};

#endif