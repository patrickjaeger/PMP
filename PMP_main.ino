
bool calibrated = false;
int atmosphericPressure;
bool streamPressure = false;

void setup() {
  initializePins();
  // pixels.begin();
  // pixels.show();
  paPixels.begin();
  paPixels.show();

}

int calibratePressure() {
  int atmosphericPressure = calibratePressure();
  Serial.println("Calibration complete. Atmospheric pressure:");
  Serial.println(atmosphericPressure);
  return(atmosphericPressure);
}

void loop() {
  // Calibrate atmospheric pressure
  if (!calibrated) {

    atmosphericPressure = calibratePressure();
    Serial.println("Calibration complete. Atmospheric pressure:");
    Serial.println(atmosphericPressure);
    calibrated = true;
  }



  // Open valves to connect to plate
  triggerWithLongPress(BLUE, 250, &activateVenting);

  // Pump until pressure X is reached, (hold,) and vent
  // triggerWithLongPress(RED, 500, &pumpToPressure(targetPressure));

  togglePump(RED);


}

