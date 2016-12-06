#ifndef GFSK_DC_h
#define GFSK_DC_h

#include "Arduino.h"

class GFSK_DC
{
  public:
    GFSK_DC(int pin1, int pin2, int speedPin);
    void init();
    void setSpeed(int speed);
    void setDirection(int direction);
    void stop();
    void loop();
  private:
    int _pin1;
    int _pin2;
    int _speed;
    int _targetSpeed;
    long _lastTime;
    int _currentDirection;
    int _speedPin;
    int _direction;
    int _pinStates[2] = {0, 0};
    void run();
};

#endif