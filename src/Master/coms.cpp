class Coms() {

  const byte cmd_clear_address = 30;
  const byte cmd_read_sensor = 31;
  const byte flag_unknown_address =250;
  const byte flag_unknown_position = 251;

  Coms::Coms(byte floors, byte sdaPin, byte sclPin) {
    byte noOfFloors = floors;   
    byte addressCounter = noOfFloors + 8;
    pinMode(sdaPin, OUTPUT);
    pinMode(sclPin, OUTPUT);
    digitalWrite(sdaPin, LOW);
    digitalWrite(sclPin, LOW);
  }
  
  void Coms::start(){
    Serial.begin(9600);
    Wire.begin();
  }

  void Coms::setAddress(byte address) {
    Wire.beginTransmission(address);
    Wire.write(cmd_clear_address);
    Wire.write(addressCounter);
    addressCounter--;
    if (addressCounter == 8) {
      addressCounter += noOfFloors;
    }
    return;
  }

  byte Coms::scanAddresses() {
    for (address = 20; address < noOfFloors+20; adress++) {
      Wire.beginTransmission(address);
      exitCode = Wire.endTransmission();

      if (exitCode == 0) {
        return address;
      }

      else if (exitCode == 4) {
        return flag_unknown_address;
      }
    }
  }

    byte Coms::requestPosition() {
      for (address = 8; address < noOfFloors+8; address++) {
        Wire.beginTransmission(address);
        Wire.write(cmd_read_sensor);
        Wire.endTransmission();
        Wire.requestFrom(address, 1);
        boolean positionFound = Wire.read();
        if (positionFound) {
          return address- 8;
        } 
      }
      return flag_unknow_position;
      }

      void Coms::requestSlavePanel() {
        for (address = 8; address < noOfFloors+8; address++) {
          Wire.beginTransmission(address);
          Wire.write(cmd_read_buttons);
          Wire.endTransmission();
          Wire.requestFrom(address, 1);
          byte buttonState = Wire.read(); 
          if (buttonState == 1) {
            Route::addToRoute(byte address, true);
          }
          if (buttonState == 2) {
            Route::addToRoute(byte address, false);
          }
        }
        return;
      }

    void Coms::announcePosition(byte position) {
      for (address = 8; address < noOfFloors+8; address++) {
        Wire.beginTransmission(address);
        Wire.write(cmd_set_display);
        Wire.write(position);
        Wire.endTransmission();
      }
      return;
    }

    void Coms::getSensorState(byte floorNumber) {
      byte address = floor + 8;
      Wire.beginTransmission(address);
      Wire.write(cmd_read_sensor);
      Wire.endTransmission();
      Wire.requestFrom(address, 1);
      boolean sensor_state = Wire.read();
      return sensor_state;
    }
}
