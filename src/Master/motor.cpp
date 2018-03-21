#ifndef Motor
#define Motor

#include <Arduino.h>
#include "Lift.h"

class Motor{


  const byte maxSpeed = 20;
  const int stepsPerRotation = 2048;
  const byte someSteps = 16;


  long startInterval;
  long stopInterval;
  byte rpm;

  Motor::Motor(byte p1, byte p2, byte p3, byte p4) {
    byte phase1 = p1;
    byte phase2 = p2;
    byte phase3 = p3;
    byte phase4 = p4;

  Stepper stepper = Stepper(rpm, phase1, phase2, phase3, phase4);
  }

  void Motor::start(boolean direction) {
    if(!direction) {
      someSteps=~someSteps+1;
    }
    for (byte speed=1; speed<maxSpeed; speed++) {
      stepper.setSpeed(speed);
      stepper.step(speed * someSteps);
    }
    return;
  }
  
  void Motor::turn(boolean direction, byte speed) {
    if(!direction) {
      someSteps=~someSteps+1;
    }
    stepper.setSpeed(speed);
    stepper.step(someSteps);
    return;
  }
  
  void Motor::brake(boolean direction) {
    if(!direction) {
      someSteps=~someSteps+1;
    }
    for (byte speed=maxSpeed; speed>3; speed--) {
      stepper.setSpeed(speed);
      stepper.step(speed * someSteps);
    }
    return;
  }

  void Motor::stop() {
    stepper.setSpeed(0);
    stepper.step(0);
    return;
  }

  void Motor::initRoutine(boolean operation) {
    //continue here 
  }
}
 
