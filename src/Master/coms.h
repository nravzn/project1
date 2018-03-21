#ifndef Coms
#define Coms

#include <Wire.h>
#include <Arduino.h>

class Coms {
 public:
  Coms(byte noOfFloors, byte sdaPin, byte sclPin);
  void start();
  void setAddress(byte initAddress);
  void scanAdresses();
  void requestPosition();
  void announcePosition(byte position);
  void getSensorState(byte floorAddress);
 private:
}

