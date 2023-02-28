#include "PhotoResistor.h"
#define TRESHOLD 1000

PhotoResistor::PhotoResistor(int pin) : JSONSensor<bool>("photo_resistor"), pin(pin)
{
  pinMode(pin, INPUT);
}

bool PhotoResistor::isDark()
{
  return analogRead(pin) <= TRESHOLD;
};