#include "ShiftRegister595.h"

byte digits[10] = {0x30, 0xfc, 0xa2, 0xa4, 0x6c, 0x25, 0x21, 0xbc, 0x20, 0x24};
byte latchPin = 8, clockPin = 11, dataPin = 12;
byte button1 = 3, button2 = 4, buttonLed1 = 7, buttonLed2 = 6, doorLed = 5;
byte segAn1 = 9, segAn2 = 10;
int elevatorLevel [] = {0, 0, 0};
unsigned int floorLevel = 0;
boolean upNotDown = false, serialMessagePrinted = false, rng = false;
unsigned int buttonRecoverTime = 300;
unsigned long startTime;
unsigned int mpDelay = 11;
ShiftRegister595 shiftRegister595 = ShiftRegister595(latchPin , clockPin , dataPin);

void moveElevator()
{
  do
  {
    startTime = millis();
    if (elevatorLevel[2] > floorLevel)
    {
      for (unsigned long elapsed = 0; elapsed < 1000; elapsed = millis() - startTime)
      {
        digitalWrite(segAn1, LOW);
        digitalWrite(segAn2, HIGH);
        shiftRegister595.write(digits[elevatorLevel[0]]);
        delay(mpDelay);
        digitalWrite(segAn1, HIGH);
        digitalWrite(segAn2, LOW);
        shiftRegister595.write(digits[elevatorLevel[1]]);
        delay(mpDelay);
      }
      elevatorLevel[1]--;
      if (elevatorLevel[1] < 0)
      {
        elevatorLevel[1] = 9;
        elevatorLevel[0]--;
      }
      elevatorLevel[2] = 10 * elevatorLevel[0] + elevatorLevel[1];
    }
    else if (elevatorLevel[2] < floorLevel)
    {
      for (unsigned long elapsed = 0; elapsed < 1000; elapsed = millis() - startTime)
      {
        digitalWrite(segAn1, LOW);
        digitalWrite(segAn2, HIGH);
        shiftRegister595.write(digits[elevatorLevel[0]]);
        delay(mpDelay);
        digitalWrite(segAn1, HIGH);
        digitalWrite(segAn2, LOW);
        shiftRegister595.write(digits[elevatorLevel[1]]);
        delay(mpDelay);
      }
      elevatorLevel[1]++;
      if (elevatorLevel[1] > 9)
      {
        elevatorLevel[1] = 0;
        elevatorLevel[0]++;
      }
      elevatorLevel[2] = 10 * elevatorLevel[0] + elevatorLevel[1];
    }
  }
  while (elevatorLevel[2] != floorLevel);
  return;
}


void lightButton(byte button, boolean state)
{
  if (state && (button == 1))
  {
    digitalWrite(buttonLed1, HIGH);
  }
  else if (state && (button == 2))
  {
    digitalWrite(buttonLed2, HIGH);
  }
  else if (!state && (button == 1))
  {
    digitalWrite(buttonLed1, LOW);
  }
  else if (!state && (button == 2))
  {
    digitalWrite(buttonLed2, LOW);
  }
}

void lockDoor(boolean state)
{
  if (state)
  {
    digitalWrite(doorLed, HIGH);
  }
  else
  {
    digitalWrite(doorLed, LOW);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(buttonLed1, OUTPUT);
  pinMode(buttonLed2, OUTPUT);
  pinMode(segAn1, OUTPUT);
  pinMode(segAn2, OUTPUT);
  pinMode(doorLed, OUTPUT);
}

void loop()
{
  if (!rng)
  {
    floorLevel = random(0, 20);
    rng = true;
    Serial.printf("we are on floor: %d\n", floorLevel);
    Serial.printf("elevator is on floor: %d\n\n", elevatorLevel[2]);
  }

  if ((digitalRead(button1) != HIGH) && (digitalRead(button2) == HIGH))
  {
    upNotDown = true;
    lightButton(1, true);
    startTime = millis();
    for (unsigned long elapsed = 0; elapsed < 800; elapsed = millis() - startTime)
      {
        digitalWrite(segAn1, LOW);
        digitalWrite(segAn2, HIGH);
        shiftRegister595.write(digits[elevatorLevel[0]]);
        delay(mpDelay);
        digitalWrite(segAn1, HIGH);
        digitalWrite(segAn2, LOW);
        shiftRegister595.write(digits[elevatorLevel[1]]);
        delay(mpDelay);
      }
    lockDoor(1);
    startTime = millis();
    for (unsigned long elapsed = 0; elapsed < 1600; elapsed = millis() - startTime)
      {
        digitalWrite(segAn1, LOW);
        digitalWrite(segAn2, HIGH);
        shiftRegister595.write(digits[elevatorLevel[0]]);
        delay(mpDelay);
        digitalWrite(segAn1, HIGH);
        digitalWrite(segAn2, LOW);
        shiftRegister595.write(digits[elevatorLevel[1]]);
        delay(mpDelay);
      }
    moveElevator();
    startTime = millis();
    for (unsigned long elapsed = 0; elapsed < 1600; elapsed = millis() - startTime)
      {
        digitalWrite(segAn1, LOW);
        digitalWrite(segAn2, HIGH);
        shiftRegister595.write(digits[elevatorLevel[0]]);
        delay(mpDelay);
        digitalWrite(segAn1, HIGH);
        digitalWrite(segAn2, LOW);
        shiftRegister595.write(digits[elevatorLevel[1]]);
        delay(mpDelay);
      }
    lockDoor(0);
    startTime = millis();
    for (unsigned long elapsed = 0; elapsed < 800; elapsed = millis() - startTime)
      {
        digitalWrite(segAn1, LOW);
        digitalWrite(segAn2, HIGH);
        shiftRegister595.write(digits[elevatorLevel[0]]);
        delay(mpDelay);
        digitalWrite(segAn1, HIGH);
        digitalWrite(segAn2, LOW);
        shiftRegister595.write(digits[elevatorLevel[1]]);
        delay(mpDelay);
      }
    lightButton(1, false);
  elevatorLevel[2] = floorLevel;
    rng = false;

  }
  else if ((digitalRead(button1) == HIGH) && (digitalRead(button2) != HIGH))
  {
    upNotDown = false;
    lightButton(2, true);
    delay(800);
    lockDoor(true);
    delay(1600);
    moveElevator();
    delay(1600);
    lockDoor(false);
    delay(800);
    lightButton(2, false);
    elevatorLevel[2] = floorLevel;
    rng = false;
  }
  else {
    digitalWrite(segAn1, LOW);
    digitalWrite(segAn2, HIGH);
    shiftRegister595.write(digits[elevatorLevel[0]]);
    delay(mpDelay);
    digitalWrite(segAn1, HIGH);
    digitalWrite(segAn2, LOW);
    shiftRegister595.write(digits[elevatorLevel[1]]);
    delay(mpDelay);
  }
}

