#include <HX711.h>
#include <Joystick.h>

// Pinning.
const int dataPin = 3;
const int clockPin = 2;
const int ledPin = 4;

// Load cell settings.
const int loadSamples = 6;
const float loadScale = 4.f;
const long loadOffset = 0;

// LED settings.
const int ledThreshold = 30;

HX711 loadCell;
Joystick_ Joystick;

void setup() {
  // Setup indicator LED.
  pinMode(ledPin, OUTPUT);

  // Setup load cell.
  loadCell.begin(dataPin, clockPin);
  loadCell.set_scale(loadScale);
  loadCell.set_offset(loadOffset);
  //loadCell.tare();
  
  Joystick.begin();
}

void loop() {
  int raw = loadCell.get_value(loadSamples);
  Serial.print(raw);
  Serial.println();

  // Map load cell output to intended range.
  int value = map(raw, 0, 2500, 0, 255);

  // Turn LED on when there is load; off otherwise.
  if (value >= ledThreshold) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }

  // Set the throttle value the mapped.
  Joystick.setThrottle(value);
}
