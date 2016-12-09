/*
  GFSK_Ultrasonic.h - Library for distance measuring.
  Created by Fabian Kruse
  2016-10-29

  Wiring:
    pin1      = "digital" (trigPin)
    pin2      = "digital" (echoPin)

  Pins on Sensor:
    trigPin = [trigPin]
    echoPin = [echoPin]

*/

#include "Arduino.h"
#include "GFSK_Ultrasonic.h"

GFSK_Ultrasonic::GFSK_Ultrasonic(int trigPin, int echoPin, int interval)
{
  _trigPin = trigPin;
  _echoPin = echoPin;
  _interval = interval;
  _lastDistances = 1;
  _lastTime = millis();
}

void GFSK_Ultrasonic::init()
{
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

int GFSK_Ultrasonic::getDistanceInCM()
{
  if ((millis() - _interval) > _lastTime) {
    _lastTime = millis();
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    int microseconds = pulseIn(_echoPin, HIGH, 30000); // wait max 30ms

    // convert the time into a distance
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    int distance = (microseconds / 29 / 2);
    
    if (distance <= 0)
    {
      return _lastDistances;
    } else if (distance > 500) {
      return 500;
    } else {
      _lastDistances = distance;
      return distance;
    }
  } else {
    return _lastDistances;
  }
}