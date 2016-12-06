#ifndef GFSK_Joystick_h
#define GFSK_Joystick_h

#include "Arduino.h"

class GFSK_Joystick
{
  public:
    GFSK_Joystick(int rX, int rY, int button);
    void init();
    int getRX();
    int getRY();
    int isPressed();
  private:
    int _deadzone = 5;
    int _rX;
    int _rY;
    int _button;
};

#endif