#ifndef GFSK_Sensor_Tracking_h
#define GFSK_Sensor_Tracking_h

#include "Arduino.h"

class GFSK_Sensor_Tracking
{
  public:
    GFSK_Sensor_Tracking(int tracingPin);
    void init();
    int getSurface();
  private:
    int _tracingPin;
};

#endif