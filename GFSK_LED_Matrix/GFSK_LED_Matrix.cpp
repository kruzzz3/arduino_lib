/*
  GFSK_LED_Matrix.h - Library for led-matrix controlling.
  Created by Fabian Kruse
  2016-11-11

  Wiring:
    dinPin  = "digital"
    clkPin  = "digital"
    csPin   = "digital"

  Pins on Sensor:
    VCC = 5V
    GND = GND
    DIN = [dinPin]
    CS  = [csPin]
    CLK = [clkPin]

*/

#include "GFSK_LED_Matrix.h"

GFSK_LED_Matrix::GFSK_LED_Matrix(int dinPin, int clkPin, int csPin) {
  _dinPin = dinPin;
  _clkPin = clkPin;
  _csPin = csPin;
}

void GFSK_LED_Matrix::init() {
  pinMode(_dinPin, OUTPUT);
  pinMode(_clkPin, OUTPUT);
  pinMode(_csPin, OUTPUT);

  digitalWrite(_csPin, HIGH);
  for(int i = 0; i < 8; i++) {
    status[i] = 0x00;
  } 

  spiTransfer(11, 7);
  spiTransfer(12, 0);
  spiTransfer(12, 1);
  clear();
  spiTransfer(10, 8);
  clear();
  spiTransfer(15, 0);
  spiTransfer(9, 0);
  clear();
}

/*
  clears the complete matrix
*/
void GFSK_LED_Matrix::clear() {
  for(int i = 0; i < 8; i++) {
    status[i] = 0;
    spiTransfer(i + 1, status[i]);
  }
}

/*
  set state of a specific led
*/
void GFSK_LED_Matrix::setLed(int row, int column, boolean state) {
  byte val = 0x00;
  if(row < 0 || row > 7 || column < 0 || column > 7) {
    return;
  } else {
    val=B10000000 >> column;
    if(state) {
      status[row] = status[row]|val;
    } else {
      val =~ val;
      status[row] = status[row]&val;
    }
    spiTransfer(row + 1, status[row]);
  }
}

/*
  set state of a complete led row (bottom-up)
  example: setRow(0, B01111110);
*/
void GFSK_LED_Matrix::setRow(int row, byte value) {
  if(row < 0 || row > 7) {
    return;
  } else {
    status[row] = value;
    spiTransfer(row + 1, status[row]);
  }
}

/*
  draw full array
*/
void GFSK_LED_Matrix::drawArray(byte array[]) {
  for(int i = 0; i < 8; i++) {
    setRow(i, array[i]);
  }
}

void GFSK_LED_Matrix::spiTransfer(volatile byte opcode, volatile byte data) {
  int maxbytes = 2;

  for(int i = 0; i < maxbytes; i++) {
    spidata[i] = (byte)0;
  }
  
  spidata[1] = opcode;
  spidata[0] = data;
  
  digitalWrite(_csPin, LOW);
  
  for(int i = maxbytes; i > 0; i--) {
    shiftOut(_dinPin, _clkPin, MSBFIRST, spidata[i-1]);
  }

  digitalWrite(_csPin, HIGH);
}