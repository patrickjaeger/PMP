int atmosphericPressure = 0;
unsigned long openTime = 0;
int targetPressure = 0;
double pressureGain = 1.5;

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
    atmosphericPressure = calibratePressure();
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

  // Pump to specified pressure
  if (readBtn(RED) && state == READY) {
    targetPressure = atmosphericPressure * pressureGain;
    Serial.println(targetPressure);
    pumpToPressure(targetPressure);
    delay(1000);
    // state = DONE;
    state = READY;
  }

  // Reset state to CALIBRATED
  // if (longPress(BLUE, 1000)) {
  //   state = CALIBRATED;
  //   delay(1000);
  // }

  // Reset state to STANDBY
  // if (readBtn(RED) && state != READY) {
  //   state = STANDBY;
  //   delay(1000);
  // }

  if (state == STANDBY) setLEDs(10, 0, 0);
  if (state == CALIBRATED) setLEDs(17, 5, 0);
  if (state == OPEN) setLEDs(5, 5, 0);
  if (state == READY) setLEDs(0, 10, 0);
  if (state == DONE) setLEDs(0, 0, 50);

// if (state == STANDBY) {
//   triggerWithLongPress(RED, 1000, &setLEDs(10, 0 , 10));
// }
// if (longPress(RED, 1000)) setLEDs(10, 0, 10);
// longPress(RED, 1000);
// if (readBtn(RED)) {
//   static int redState = 0;
//   static unsigned long depressTime = 0;
//   static int protocolState = 0;
//   if (redState == 0) {
//     depressTime = millis();
//     redState = 1;
//   }
//   if (redState == 1 && millis() - depressTime > 1000) {
//     redState = 0;
//     depressTime = millis();
//     Serial.println("FU");
//   }
// }

}

