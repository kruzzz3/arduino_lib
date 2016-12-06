#ifndef GFSK_Sensor_Temp_h
#define GFSK_Sensor_Temp_h

#include "Arduino.h"

class GFSK_Sensor_Temp
{
  public:
    GFSK_Sensor_Temp(int tempPin);
    void init();
    double getTempInC();
  private:
    int _tempPin;
};

#endif