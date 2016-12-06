#ifndef GFSK_LED_Matrix_h
#define GFSK_LED_Matrix_h

#include <Arduino.h>

class GFSK_LED_Matrix {
 private :
  void spiTransfer(byte opcode, byte data); // method for sending out a single command to the device
  byte status[8]; // status array (used for setLed())
  byte spidata[16]; // array for shifting the data to the devices
  int _dinPin; // Data is shifted out of this pin*/
  int _clkPin; // The clock is signaled on this pin
  int _csPin; // This one is driven LOW for chip selectzion
 public:
  GFSK_LED_Matrix(int dinPin, int clkPin, int csPin);
  void init();
  void clear();
  void setLed(int row, int col, boolean state);
  void setRow(int row, byte value);
  void drawArray(byte array[]);
};

#endif