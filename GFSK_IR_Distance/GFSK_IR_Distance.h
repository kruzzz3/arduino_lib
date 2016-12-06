#ifndef GFSK_IR_Distance_h
#define GFSK_IR_Distance_h

#include "Arduino.h"

class GFSK_IR_Distance
{
  public:
    GFSK_IR_Distance(int irReadPin);
    void init();
    int getDistanceInCM();
  private:
    int _irReadPin;
    int _lastDistances;
};

#endif