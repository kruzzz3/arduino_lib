/*
  GFSK_Joystick.h - Library for controlling a joystick.
  Created by Fabian Kruse
  2016-10-29

  Wiring:
    rX      = "analog"
    rY      = "analog"
    button  = "digital"
    
*/

#include "Arduino.h"
#include "GFSK_Joystick.h"

GFSK_Joystick::GFSK_Joystick(int rX, int rY, int button)
{
  _rX = rX;
  _rY = rY;
  _button = button;
}

void GFSK_Joystick::init()
{
  pinMode(_rX, INPUT);
  pinMode(_rY, INPUT);
  pinMode(_button, INPUT);

  digitalWrite(_button, HIGH);
}

/*
  value 0-1023
  about 512 is center
*/
int GFSK_Joystick::getRX()
{
  int rX = analogRead(_rX);
  if (rX >= (512 - _deadzone) && rX <= (512 + _deadzone)) {
    return 512;
  } else {
    return rX;
  }

}

/*
  value 0-1023
  about 512 is center
*/
int GFSK_Joystick::getRY()
{
  int rY = analogRead(_rY);
  if (rY >= (512 - _deadzone) && rY <= (512 + _deadzone)) {
    return 512;
  } else {
    return rY;
  }
}

/*
  return 1 if pressed
*/
int GFSK_Joystick::isPressed()
{
  int button = digitalRead(_button);
  if (button == 1) {
    return 0;
  } else {
    return 1;
  }
}
