/*
  GFSK_Sensor_Temp.h - Library for black surface detection.
  Created by Fabian Kruse
  2016-11-20

  Wiring:
    tempPin = "analog"

  Pins on Sensor:
    G = GND
    V = 5V
    S = [tempPin]

  Important:
    Switch GND & V5 if temp is changing the wrong way

*/

#include "Arduino.h"
#include "GFSK_Sensor_Temp.h"
#include "math.h"

GFSK_Sensor_Temp::GFSK_Sensor_Temp(int tempPin)
{
  _tempPin = tempPin;
}

void GFSK_Sensor_Temp::init()
{
  pinMode(_tempPin, INPUT);
}

double GFSK_Sensor_Temp::getTempInC()
{
  int raw = analogRead(_tempPin);
  double temp = log(((10240000 / raw) - 10000));
  temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp ))* temp );
  temp = temp - 273.15;// convert kelvin to celcius

  return temp;
}