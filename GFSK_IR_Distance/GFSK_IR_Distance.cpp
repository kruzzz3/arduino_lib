/*
  GFSK_IR_Distance.h - Library for distance measuring.
  Created by Fabian Kruse & Gregor Spitzer
  2016-10-29

  Wiring:
    pin1      = "analog" (trigPin)

  Pins on Sensor:
    irReadPin = [irReadPin] (yellow)

*/

#include "Arduino.h"
#include "GFSK_IR_Distance.h"

GFSK_IR_Distance::GFSK_IR_Distance(int irReadPin)
{
  _irReadPin = irReadPin;
  _lastDistances = 1;
}

void GFSK_IR_Distance::init()
{
  pinMode(_irReadPin, INPUT);
}

int GFSK_IR_Distance::getDistanceInCM()
{
  return analogRead(_irReadPin);
  // digitalWrite(_trigPin, LOW);
  // delayMicroseconds(2);
  // digitalWrite(_trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(_trigPin, LOW);

  // int microseconds = pulseIn(_echoPin, HIGH);

  // // convert the time into a distance
  // // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // // The ping travels out and back, so to find the distance of the
  // // object we take half of the distance travelled.
  // int distance = (microseconds / 29 / 2);
  
  // if (distance < 0)
  // {
  //   return _lastDistances;
  // } else if (distance > 300) {
  //   return 300;
  // } else {
  //   _lastDistances = distance;
  //   return distance;
  // }
}