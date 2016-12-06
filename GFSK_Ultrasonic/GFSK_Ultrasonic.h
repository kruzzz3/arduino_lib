#ifndef GFSK_Ultrasonic_h
#define GFSK_Ultrasonic_h

#include "Arduino.h"

class GFSK_Ultrasonic
{
  public:
    GFSK_Ultrasonic(int trigPin, int echoPin);
    void init();
    int getDistanceInCM();
  private:
    int _trigPin;
    int _echoPin;
    int _lastDistances;
};

#endif