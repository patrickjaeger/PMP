unsigned long openTime = 0;

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

  // Open valves to connect plate
  if (readBtn(BLUE) && state == CALIBRATED) {
    switchOffPumps();
    vent();
    state = OPEN;
    openTime = millis();
  } else if (readBtn(BLUE) && state == OPEN && (millis() - openTime > 500)) {
    closeAllValves();
    state = READY;
  } else if (state == OPEN && millis() - openTime > 30000) {
    closeAllValves();
    state = READY;
  }

  // Pump
  if (readBtn(RED) && state == READY) {
    
  }





  // Open valves to connect to plate
  triggerWithLongPress(BLUE, 250, &activateVenting);

  // Pump until pressure X is reached, (hold,) and vent
  // triggerWithLongPress(RED, 500, &pumpToPressure(targetPressure));

  togglePump(RED);


}

