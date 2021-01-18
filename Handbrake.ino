#include <HX711.h>
#include <Joystick.h>

const int potPin = 6;
const int clockPin = 7;
const int ledPin = 13;
const int ledThreshold = 30;

Joystick_ Joystick;
HX711 scale;

void setup() {
  // Setup indicator LED.
  pinMode(ledPin, OUTPUT);

  // Setup load cell.
  scale.begin(dataPin, clockPin);  
  
  Joystick.begin();
}

void loop() {
  int raw = scale.get_units(5);

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
