class Route {

    Route::Route(byte queueSize) {

      boolean directionUp = false;
      boolean queueUp[queueSize];
      boolean queueDown[queueSize];

      byte queueIndexUp  = 0;
      byte queueIndexDown = 0;

      for (int i = 0; i <= arraySize; i++) {
        queueUp[i] = false;
        queueDown[i] = false;
      }
        
    }

    void addToRoute(byte calledFloor, boolean selection) {
      if (selection) {
        queueUp[calledFloor] = true;
      }
      else {
        queueDown[calledFloor] = true;
      }
      return;
    }

    byte getNextStop() {
      if (directionUp) {
        for (byte floorIndex = queueIndexUp; floorIndex <= queueSize; floorIndex++) {
          if (queueUp[floorIndex]) {
            return floorIndex;
          }
        }
        directionUp = false;
        getNextStop();
      }
      else {
        for (byte floorIndex = queueIndexDown; floorIndex >= 0; floorIndex--) {
          if (queueDown[floorIndex]) {
            return floorIndex
          }
        }
        directionUp = true;
        getNextStop();
      }
      return 0;
    }

    
    void removefromRoute(byte floorNumber) {
      if (directionUp) {
        queueUp[calledFloor] = false;
      }
      else {
        queueDown[calledFloor] = false;
      }
      return;
    }

}

