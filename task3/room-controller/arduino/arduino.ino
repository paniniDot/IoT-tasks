
#include "src/Light.h"
#include "src/Bluetooth.h"
#include "src/Roll.h"
Bluetooth *bluetooth;
void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  bluetooth = new Bluetooth(2,3);
  Light *light = new Light(9);
  Roll *roll = new Roll(6);
  bluetooth->attach(light);
  bluetooth->attach(roll);
  light->attach(bluetooth);
  roll->attach(bluetooth);
}

void loop() {
  bluetooth->notify();
}