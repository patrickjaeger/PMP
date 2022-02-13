void setup() {
  initializePins();
  // pixels.begin();
  // pixels.show();
  paPixels.begin();
  paPixels.show();

}

void loop() {

  
  // Calibrate atmospheric pressure
  if (readBtn(BLUE) && state == STANDBY) {
    int atmosphericPressure = calibratePressure();
    delay(1000);
    state = CALIBRATED;
  }

  if (readBtn(BLUE) && state == CALIBRATED) {

  }



  // Open valves to connect to plate
  triggerWithLongPress(BLUE, 250, &activateVenting);

  // Pump until pressure X is reached, (hold,) and vent
  // triggerWithLongPress(RED, 500, &pumpToPressure(targetPressure));

  togglePump(RED);


}

