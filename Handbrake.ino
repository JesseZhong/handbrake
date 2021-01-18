#include <Joystick.h>

const int potPin = A2;
Joystick_ Joystick;

void setup() {
  Joystick.begin();
}

void loop() {
  int rawValue = analogRead(potPin);
  int value = map(rawValue, -1023, 1023, -32767, 32767);
  Joystick.setXAxis(value);
}
