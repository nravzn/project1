#ifndef Lift
#define Lift

#define circBuff(objP, data)

#include<Arduino.h>
#include"motor.h"
#include"coms.h"
#include"display.h"
#include"panel.h"
#include"ringbuffer.h"

class Lift {
 public:
  Lift(byte fl, byte dP, byte lP, byte cP, byte bD, byte bU, byte bS, byte bDL, byte bUL, byte bSL); 
  void initialize();
  void moveTo(byte destination);
  void sortQueue(byte floorNumber);
 private:
}
 
