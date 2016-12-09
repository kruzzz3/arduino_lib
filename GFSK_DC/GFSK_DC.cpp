/*
  GFSK_DC.h - Library for controlling DC motor.
  Created by Fabian Kruse
  2016-11-13

  Wiring:
    pin1      = "digital"
    pin2      = "digital"
    speedPin  = "digital pwm"

  Pins on Sensor:
    pin1/pin3 = [pin1]
    pin2/pin4 = [pin2]
    enable    = [speedPin]

*/

#include "Arduino.h"
#include "GFSK_DC.h"

GFSK_DC::GFSK_DC(int pin1, int pin2, int speedPin)
{
  _pin1 = pin1;
  _pin2 = pin2;
  _speedPin = speedPin;
  _speed = 200;
  _direction = 0;
  _currentDirection = 1;
}

void GFSK_DC::init()
{
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);

  _pinStates[0] = 1;
  _pinStates[1] = 0;

  digitalWrite(_pin1, _pinStates[0]);
  digitalWrite(_pin2, _pinStates[1]);
}

void GFSK_DC::loop()
{
}

/*
  set speed for a motor.
  lower value = faster
  lowest value = 0
  highest value = 255
*/
void GFSK_DC::setSpeed(int speed)
{
  if (speed > 255) {speed = 255;}
  if (speed < 0) {speed = 0;}
  _speed = speed;
  analogWrite(_speedPin, _speed);
}

int GFSK_DC::getSpeed()
{
  return _speed;
}


/*
  set direction
  1 or 0
*/
void GFSK_DC::setDirection(int direction)
{
  if (_currentDirection != _direction) {
    _direction = direction;
    _currentDirection = direction;
  }
  if (direction == 0) {
    _pinStates[0] = 1;
    _pinStates[1] = 0;
  } else {
    _pinStates[0] = 0;
    _pinStates[1] = 1;
  }
  run();
}

int GFSK_DC::getDirection()
{
  return _direction;
}

/*
  stop the motor
*/
void GFSK_DC::stop()
{
  _pinStates[0] = 0;
  _pinStates[1] = 0;
  run();
}

/*
  run the motor
*/
void GFSK_DC::run()
{
  digitalWrite(_pin1, _pinStates[0]);
  digitalWrite(_pin2, _pinStates[1]);
}