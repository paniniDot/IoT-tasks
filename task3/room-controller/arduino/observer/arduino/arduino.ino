#include "SoftwareSerial.h"
#include <Servo.h>
#include <String.h>
#include "src/Light.h"
#include "src/Bluetooth.h"

void setup()
{
  Light *light = new Light(9);
  Bluetooth *bluetooth = new Bluetooth(2, 3);
  Light->attach(bluetooth);
  Bluetooth->attach(light);
}

void loop()
{
}