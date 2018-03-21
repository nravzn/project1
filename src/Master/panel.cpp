#ifndef Panel
#define Panel

class Panel {

    Panel::Panel(byte bD, byte bU, byte bS, byte bDL, byte bUL, byte bSL) {
      byte buttonDown = bD;
      byte buttonUp = bU;
      byte buttonSet = bS;
      byte buttonDownLed = bDL;
      byte buttonUpLed = bUL;
      byte buttonSetLed = bSL;

      byte selection = 0;

      boolean prevStateUp = false;
      boolean prevStateDown = false;
      boolean prevStateSet = false;

      pinMode(buttonDown, INPUT_PULLUP);
      pinMode(buttonUp, INPUT_PULLUP);
      pinMode(buttonSet, INPUT_PULLUP);
      pinMode(buttonDownLed, OUTPUT);
      pinMode(buttonUpLed, OUTPUT);
      pinMode(buttonSetLed, OUTPUT);
    }


    byte readButtons(byte position) {

      boolean stateButtonUp = ~ digitalRead(buttonDown);
      boolean stateButtonDown = ~ digitalRead(buttonUp);
      boolean stateButtonSet = ~ digitalRead(buttonSet);


      if (!stateButtonUp && !stateButtonDown && !stateButtonSet && (prevStateUp || prevStateDown || )) {
        prevStateUp = false;
        prevStateDown = false;
      }
      setLeds(1);
      return 1;
    }

    else if (stateButtonUp && !stateButtonDown && !stateButtonSet && !prevStateUp) {
      prevStateUp = true;
      setLeds(2);
      return 2;
    }

    else if (!stateButtonUp && stateButtonDown && !stateButtonSet && !prevStateDown) {
      prevStateDown = true;
      setLeds(3);
      return 3;
    }

    else if (stateButtonSet && !stateButtonDown && !stateButtonUp && !prevStateSet) {
      prevStateSet = true;
      setLeds(4);
      return 4;
    }
    return 0;
}


void setLeds(byte case) {

if (case == 1) {
      digitalWrite(buttonUpLed, LOW);
      digitalWrite(buttonDownLed, LOW);
    }
else if (case == 2) {
      digitalWrite(buttonUpLed, LOW);
      digitalWrite(buttonDownLed, HIGH);
      digitalWrite(buttonSetLed, LOW);
    }
else if (case == 3) {
      digitalWrite(buttonUpLed, HIGH);
      digitalWrite(buttonDownLed, LOW);
      digitalWrite(buttonSetLed, LOW);
    }
else if (case == 4) {
      digitalWrite(buttonSetLed, HIGH);
    }

