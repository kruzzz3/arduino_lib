#ifndef GFSK_Servo_h
#define GFSK_Servo_h

#include "Arduino.h"
#include "Servo.h"

class GFSK_Servo
{
  public:
    GFSK_Servo(int pin);
    void init();
    void write(int position, int speed);
    int getPosition();
    void loop();
  private:
    int _pin;
    Servo _servo;
    int _pos;
    int _targetPos;
    long _lastTime;
    int _speed;
};

#endif