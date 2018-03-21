

/*** Pin declaration ***/
// Display interface
const byte dataPin = 10;
const byte latchPin = 11;
const byte clockPin = 12;
const byte dispAnode1 = 20;
const byte dispAnode2 = 21;

// I2C
const byte serialData = A4;
const byte serialClock = A0;

// Control panel
const byte buttonDown = 2;
const byte buttonUp = 3;
const byte buttonSet = 4;
const byte buttonDownLed = 5;
const byte buttonUpLed = 6;
const byte buttonSetLed = 7;

// Motor connections
const byte phase1 = 14;
const byte phase2 = 15;
const byte phase3 = 16;
const byte phase4 = 17;

/*** Field declaration ***/
// General vonstants
const byte noOfFloors = 9;


void setup() {
  Lift Lift(byte noOfFloors, byte dataPin, byte latchPin, byte clockPin, byte buttonDown, byte buttonUp, byte buttonSet, byte buttonDownLed, byte buttonUpLed, byte buttonSetLed, byte phase1, byte phase2, byte phase3, byte phase4, byte serialData, byte serialClock);
  Lift::initialize();
}

void loop() {

  byte position = Coms::requestPosition();
  Display::set(position);
  for (;;) {
    Display::show();
    Coms::requestSlavePanel();
    Lift::getPanelStatus(position);
    byte nextStop = Route::getNextStop();
    if (nextStop) {
      Lift::moveTo(position, nextStop);
      break;
    }
  }
}


