#ifndef Motor
#define Motor

#include<Stepper.h>

class Motor {
  
 public:
  Motor(byte p1, byte p2, byte p3, byte p4);
  void initRoutine(boolean operation);
  void start(boolean direction);
  void turn(boolean direction, byte speed);
  void brake(boolean direction);
  void stop();
}
