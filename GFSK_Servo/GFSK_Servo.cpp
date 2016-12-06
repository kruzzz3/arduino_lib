/*
  GFSK_Servo.h - Library for controlling a Servo.
  Created by Fabian Kruse && Gregor Spitzer
  2016-11-10

  Wiring:
    pin1 = "digital pwm"   // oragne/ yellow  --> steering
    pin2 = "5v" // red
    pin1 = "gnd" // black / brown
*/

#include "Arduino.h"
#include "GFSK_Servo.h"
#include "Servo.h"

Servo _servo;

GFSK_Servo::GFSK_Servo(int pin)
{
  _pin = pin;
  _pos = 90;
  _targetPos = 90;
  _speed = 10;
  _lastTime = millis();
}

// call to set up the Servo
void GFSK_Servo::init()
{
  _servo.attach(_pin);
  _servo.write(90);
  delay(100);
}

void GFSK_Servo::loop()
{
  if ((millis() - _speed) > _lastTime && _pos != _targetPos) {
    _lastTime = millis();
    if (_targetPos > _pos)
    {
      _pos++;
      _servo.write(_pos);
    } 
    else 
    {
      _pos--;
      _servo.write(_pos);
    }
  }
}

/*
  aim in degree:
  takes values from -90 to 90 
  
  speed for a servo:
  lower value = faster
  lowest value = 0
  highest value = 500
*/
void GFSK_Servo::write(int aim, int speed)
{
  if (speed > 500) {speed = 500;}
  if (speed < 0) {speed = 0;}
  _speed = speed;

  if(aim < -90) aim = -90;
  if(aim > 90) aim = 90;
  _targetPos = aim + 90; // needed to work with negativ values
}

/*
  return current position
*/
int GFSK_Servo::getPosition()
{
  return _pos - 90;
}