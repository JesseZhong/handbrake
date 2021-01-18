#include <HX711.h>
#include <Joystick.h>

// Pinning.
const int dataPin = 3;
const int clockPin = 2;
const int ledPin = 4;

// Load cell settings.
const int loadSamples = 4;
const float loadScale = 400.f; // If scale is too low, there's a short overflow.
const long loadOffset = 90;

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
  loadCell.tare();
  
  Joystick.begin();
}

void loop() {
  // Get scaled and offset value.
  int raw = loadCell.get_units(loadSamples);

  // Map load cell output to intended range.
  int value = map(raw, 0, 2500, 0, 255);

  // Turn LED on when there is load; off otherwise.
  if (value >= ledThreshold) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print(", Adjusted: ");
  Serial.println(value);

  // Set the throttle value the mapped.
  Joystick.setThrottle(value);
}
