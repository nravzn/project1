class Display() {

  const byte hexCodes[] = {0x03, 0x9f, 0x25, 0x0d, 0x99, 0x49, 0x41, 0x1f, 0x01, 0x09};
  const byte hexCodesDot[] = {0x02, 0x9e, 0x24, 0x0e, 0x98, 0x48, 0x40, 0x1e, 0x00, 0x08};
  const byte displayDelay = 11;

  byte currentDigitLeft = 0x00;
  byte currentDigitRight = 0x00;
  boolean dotMode = false;

                        
  Display::Display(byte dataPin, byte latchPin, byte clockPin, byte dispAn1,  byte dispAn2) {
    const byte dataPin = dataPin;
    const byte latchPin = latchPin;
    const byte clockPin = clockPin;
    const byte dispAnode1 = dispAn1;
    const byte dispAnode2 = dispAn2;

    ShiftRegister595 shiftOut = ShiftRegister595(latchPin, clockPin, dataPin);
  }

  void Display::set(byte digitIndex, boolean dotMode) {
    byte indexLeft = digitIndex / 10;
    byte indexRight = digitIndex % 10;
    if (!dotMode) {
      currentDigitLeft = hexCodes[indexLeft];
      currentDigitRight = hexCodes[indexRight]; 
      }
    else {
      this.currentDigitLeft = hexCodesDot[indexLeft]; 
      this.currentDigitRight = hexCodesDot[indexRight];
    }
    return;
  }

  void Display::show() {
    digitalWrite(displayAnode1, LOW);
    digitalWrite(displayAnode2, HIGH);
    shiftOut.write(this.currentDigitLeft);
    delay(displayDelay);
    digitalWrite(displayAnode2, LOW);
    digitalWrite(displayAnode1, HIGH);
    shiftOut.write(this.currentDigitRight);
    delay(displayDelay);
    return;
  }
}


