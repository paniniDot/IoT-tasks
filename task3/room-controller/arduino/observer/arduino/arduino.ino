#include <String.h>
#include "src/Light.h"
#include "src/Bluetooth.h"
void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  Light *light = new Light(9);
  Bluetooth *bluetooth = new Bluetooth(2,3);
  bluetooth->attach(light);
  light->attach(bluetooth);
  bluetooth->start();
}

void loop() {
}