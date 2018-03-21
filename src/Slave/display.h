#ifndef Display
#define Display

#include"ShiftRegister595.h"

class Display {
 public:
  Display(byte dataPin, byte latchPin, byte clockPin, byte dispAn1, byte dispAn2);
  void set(byte digit);
  void show();
 private:

}
 
