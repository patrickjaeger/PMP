#include <programmable_air.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel paPixels(3, 12, NEO_GRB + NEO_KHZ800);

#define DEBUG 1
#define TESTING -7

int state = 0;
#define STANDBY 0
#define CALIBRATED 1
#define OPEN 2
#define READY 3
#define DONE 4


// unsigned long execTime = 0;
// unsigned long activationTime = 0;
// int pressureReportInterval = 100;


int calibratePressure() {
  vent();
  delay(1000);
  int _atmosphericPressure = readPressure(1, 10);
  closeAllValves();
  Serial.println("Calibration complete. Atmospheric pressure:");
  Serial.println(_atmosphericPressure);
  return(_atmosphericPressure);
}

void togglePump(int _button) {
  static unsigned long execTime = 0;
  static unsigned long activationTime = 0;
  static int pressure;

  // Toggle pump
  if (readBtn(_button) && state == 0) {
    switchOnPump(2, 100);
    switchOffPump(1);
    blow();
    state = 1;
    activationTime = millis();
  } else if (readBtn(_button) && state == 1 && (millis() - activationTime) > 250) {
    switchOffPumps();
    vent();
    delay(1000);
    closeAllValves();
    state = 0;
  }

  // Toggle pressure reporting while pump is active
  if (state == 1) {
    if (millis() >= execTime + 200) {
      pressure = readPressure(1, 3);    
      Serial.println(pressure);
      execTime = millis();
    }
  }
}

void setPixelsColor(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0) {
  // Set neoPixel brightness for all 3 LEDs with values between 0 to 255
  // Requires Adafruit_NeoPixel paPixels instance to be declared
  for (int i = 0; i < 3; i++) {
    paPixels.setPixelColor(i, paPixels.Color(red, green, blue));
  }
}

void setLEDs(int R, int G, int B) {
  setPixelsColor(R, G, B);
  paPixels.show();
}

void flashLEDs() {
  // Flash neopixel LEDs for 2secs and send a serial comment
  // Serial.println("Executing test protocol 1"); 
  setPixelsColor(100, 0 ,0);
  paPixels.show();
  delay(2000);
  setPixelsColor(0, 0 ,0);
  paPixels.show();
}

void triggerWithLongPress(int button, int time, void (*fun)()) {
  // Trigger a function with a long press of a button
  // button: color of button (RED or BLUE)
  // time: minimum time button has to be pressed to trigger in milliseconds
  // fun: name of function to trigger; function must return void; supply as address to fun, i.e. &fun
  static int last_state = 0;
  static unsigned long depress_timepoint;
  static bool longPressActive = false;

  if (readBtn(button)) {

		if (last_state == 0) {
			last_state = 1;
			depress_timepoint = millis();
		}

		if ((millis() - depress_timepoint > time) && (longPressActive == false)) {
			longPressActive = true;

      // Start protocol
      fun();
      // End protocol
		}

	} else {
    if (last_state == 1) {

			if (longPressActive == true) {
				longPressActive = false;
			}

			last_state = false;

		}
  }
}

bool longPress(int button, int time) {
  // Trigger a function with a long press of a button
  // button: color of button (RED or BLUE)
  // time: minimum time button has to be pressed to trigger in milliseconds
  static int last_state = 0;
  static unsigned long depress_timepoint;
  static bool longPressActive = false;

  if (readBtn(button)) {

		if (last_state == 0) {
			last_state = 1;
			depress_timepoint = millis();
		}

		if ((millis() - depress_timepoint > time) && (longPressActive == false)) {
			longPressActive = true;

      // Start protocol
      return(true);
      // End protocol
		}

	} else {
    if (last_state == 1) {
      return(false);
			if (longPressActive == true) {
				longPressActive = false;
			}

			last_state = false;

		}
  }
}

void activateVenting() {
	switchOffPumps();
  vent();
    
  setPixelsColor(0, 30, 0);
  paPixels.show();

}

void pumpToPressure(int targetPressure) {
  // Pump to the designated pressure
  // ----

  delay(1000);
  static unsigned long startTime = millis();
  static int elapsedTime = 0;
  int currentPressure = 0;

  // Set LEDs to red
  // setPixelsColor(50, 0, 0);
  // paPixels.show();

  // Pump until target pressure is reached or 5 sec have passed
  switchOnPump(2, 50);
  switchOffPump(1);
  blow();
  startTime = millis();
  while (currentPressure < targetPressure && elapsedTime < 5000) {
    currentPressure = readPressure(1, 3);
    elapsedTime = millis() - startTime;
    Serial.println(currentPressure);
  }

  // Switch of pumps and vent
  switchOffPumps();
  vent();

  // Set LEDs to blue
  // setPixelsColor(0, 0, 50);
  // paPixels.show();
}

void justPump() {
  switchOnPump(2, 50);
  switchOffPump(2);
  blow();
  // switchOffPumps();
  // vent();
  // delay(1000);
  // closeAllValves();
}

