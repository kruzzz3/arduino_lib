/*
  GFSK_Sensor_Tracking.h - Library for black surface detection.
  Created by Fabian Kruse
  2016-11-11

  Wiring:
    tracingPin = "digital"

  Pins on Sensor:
    G = GND
    V = 5V
    S = [tracingPin]

*/

#include "Arduino.h"
#include "GFSK_Sensor_Tracking.h"

GFSK_Sensor_Tracking::GFSK_Sensor_Tracking(int tracingPin)
{
  _tracingPin = tracingPin;
}

void GFSK_Sensor_Tracking::init()
{
  pinMode(_tracingPin, INPUT);
}

/*
  return 1 if "dark"
  return 0 if "light"
*/
int GFSK_Sensor_Tracking::getSurface()
{
  if(digitalRead(_tracingPin) == HIGH) { return 1; } else { return 0; }
}