int atmosphericPressure = 0;
unsigned long openTime = 0;
int targetPressure = 0;

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

  // Pump
  if (readBtn(RED) && state == READY) {
    targetPressure = atmosphericPressure * 1.5;
    Serial.println(targetPressure);
    pumpToPressure(targetPressure);
    delay(1000);
    state == DONE;
  }

  if (readBtn(BLUE) && state == DONE) {
    state = CALIBRATED;
    delay(1000);
  }

  // Reset to standby
  if (readBtn(RED) && state != READY) {
    state = STANDBY;
  }

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

