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
    void writeInstant(int position);
    int getPosition();
    void loop();
  private:
    int _steering;
    Servo _servo;
    int _pos;
    int _targetPos;
    long _lastTime;
    int _speed;
};

#endif