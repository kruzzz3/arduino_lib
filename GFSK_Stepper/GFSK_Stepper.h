#ifndef GFSK_Stepper_h
#define GFSK_Stepper_h

#include "Arduino.h"

class GFSK_Stepper
{
  public:
    GFSK_Stepper(int pin1, int pin2, int pin3, int pin4);
    void init();
    void stepSync(int degree);
    void stepAsync(int degree);
    void stop();
    void setStepsPerRevolution(int stepsPerRevolution);
    void setSpeed(long speed);
    void checkSteps();
    void setHalfStepping(int useHalfStepping);
  private:
    int _halfStepping;
    int _pin1;
    int _pin2;
    int _pin3;
    int _pin4;
    int _i;
    int _j;
    int _stepsLeft;
    int _direction;
    long _lastTime;
    long _speed;
    int _stepsPerRevolution;
    int _pinStates[4] = {1, 0, 0, 0};
    void nextPinStates(int degree);
};

#endif