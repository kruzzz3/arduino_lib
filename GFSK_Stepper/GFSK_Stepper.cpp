/*
  GFSK_Stepper.h - Library for controlling stepper motor.
  Created by Fabian Kruse
  2016-11-10

  use method [checkSteps()] for finding the correct results
  28BYJ-48 = 4096
  17HS4401 = 400

  Wiring:
    pin1 = "digital"
    pin2 = "digital"
    pin3 = "digital"
    pin4 = "digital"

  Pins on Sensor:
    pin1 = [pin1]
    pin2 = [pin2]
    pin3 = [pin3]
    pin4 = [pin4]

  Wiring motor:
    17HS4401
      black = pin1
      blue  = pin2
      green = pin3
      red   = pin4

*/

#include "Arduino.h"
#include "GFSK_Stepper.h"

GFSK_Stepper::GFSK_Stepper(int pin1, int pin2, int pin3, int pin4)
{
  _halfStepping = 1;
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pin4 = pin4;
  _i = 0;
  _j = 0;
  _speed = 10;
  _stepsPerRevolution = 200;
  _stepsLeft = 0;
  _direction = 0;
  _lastTime = millis();
}

void GFSK_Stepper::init()
{
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  pinMode(_pin3, OUTPUT);
  pinMode(_pin4, OUTPUT);

  digitalWrite(_pin1, _pinStates[0]);
  digitalWrite(_pin2, _pinStates[1]);
  digitalWrite(_pin3, _pinStates[2]);
  digitalWrite(_pin4, _pinStates[3]);
}


void GFSK_Stepper::setHalfStepping(int halfStepping)
{
  _halfStepping = halfStepping;
}

/*
  set the correct steps amount for a motor 
*/
void GFSK_Stepper::setStepsPerRevolution(int stepsPerRevolution)
{
  _stepsPerRevolution = stepsPerRevolution;
}

/*
  set speed for a motor.
  lower value = faster
  lowest value = 2
  highest value = 500
*/
void GFSK_Stepper::setSpeed(long speed)
{
  if (speed > 500) {speed = 500;}
  if (speed < 0) {speed = 0;}
  _speed = speed;
}

/*
  turn the motor by given degrees
  this method blocks the rest of the code
*/
void GFSK_Stepper::stepSync(int degree)
{
  int d = 0;
  if (degree >= 0) {d = degree;} else {d = -1 * degree;}

  float revolution = 360;
  int steps = (_stepsPerRevolution / revolution) * d;
  for(int i = 0; i < steps; i++)
  {
    delay(_speed);
    nextPinStates(degree);
    digitalWrite(_pin1, _pinStates[0]);
    digitalWrite(_pin2, _pinStates[1]);
    digitalWrite(_pin3, _pinStates[2]);
    digitalWrite(_pin4, _pinStates[3]);
  }
}

/*
  turn the motor by given degrees
  this method does not block the rest of the code.
  ! The motor will turn slower than the given speed
*/
void GFSK_Stepper::stepAsync(int degree)
{
  if (_stepsLeft == 0) {
    int d = 0;
    if (degree >= 0) {d = degree;} else {d = -1 * degree;}

    float revolution = 360;
    _stepsLeft = (_stepsPerRevolution / revolution) * d;
    _direction = degree;
    _lastTime = millis();
  }
  long now = millis();
  if ((now - _speed) > _lastTime && _stepsLeft > 0) {
    _lastTime = millis();
    _stepsLeft--;

    nextPinStates(_direction);
    digitalWrite(_pin1, _pinStates[0]);
    digitalWrite(_pin2, _pinStates[1]);
    digitalWrite(_pin3, _pinStates[2]);
    digitalWrite(_pin4, _pinStates[3]);
  }
}

/*
  stops the motor if it turn with [stepAsync()]
*/
void GFSK_Stepper::stop()
{
  _stepsLeft = 0;
}

/*
  run this method to check how many steps a motor needs for a full 360 turn.
  read the number in the serial monitor
*/
void GFSK_Stepper::checkSteps()
{
  int steps = 0;
  while(true)
  {
    Serial.println(steps);
    delay(50);
    nextPinStates(360);
    digitalWrite(_pin1, _pinStates[0]);
    digitalWrite(_pin2, _pinStates[1]);
    digitalWrite(_pin3, _pinStates[2]);
    digitalWrite(_pin4, _pinStates[3]);
    steps++;
  }
}

/*
  only internal used
*/
void GFSK_Stepper::nextPinStates(int degree)
{
  _pinStates[0] = 0;
  _pinStates[1] = 0;
  _pinStates[2] = 0;
  _pinStates[3] = 0;

  _pinStates[_i] = 1;

  if (_halfStepping == 1)
  {
    if (_j == 0)
    {
      _j++;
    } else {
      int k = 0;
      if (degree > 0) {k = _i + _j;} else {k = _i - _j;}
      if (k > 3){k = 0;} else if (k < 0) {k = 3;}
      _pinStates[k] = 1;
      _j = 0;
      if (degree > 0) {_i++;} else {_i--;}
      if (_i > 3){_i = 0;} else if (_i < 0) {_i = 3;}
    }
  } else {
    if (degree > 0) {_i++;} else {_i--;}
    if (_i > 3){_i = 0;} else if (_i < 0) {_i = 3;}
  }
}
