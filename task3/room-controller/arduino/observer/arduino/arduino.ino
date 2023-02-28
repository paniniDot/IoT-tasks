#include "SoftwareSerial.h"
#include <String.h>
#include "src/Light.h"
#include "src/sensor/Led.h"
#include "src/Bluetooth.h"

void setup()
{
  Light *light = new Light(new Led(9));
  SoftwareSerial *bt = new SoftwareSerial(2, 3);
  Bluetooth *bluetooth = new Bluetooth(bt);
  light->attach(bluetooth);
}

void loop()
{
}