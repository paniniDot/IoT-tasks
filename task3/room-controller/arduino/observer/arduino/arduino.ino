#include "SoftwareSerial.h"
#include <String.h>
#include "src/Light.h"
#include "src/sensor/Led.h"
#include "src/Bluetooth.h"
SoftwareSerial *bt = new SoftwareSerial(2, 3);
void setup() {
  Light *light = new Light(new Led(9));
  Serial.begin(9600);
  while (!Serial) {};
  bt->begin(9600);
  Serial.println("ready to go.");
  Bluetooth *bluetooth = new Bluetooth(bt);
  light->attach(bluetooth);
}

void loop() {
}