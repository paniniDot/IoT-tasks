#include "PhotoResistor.h"
#define TRESHOLD 1000

PhotoResistor::PhotoResistor(int pin) : JSONSensor<int>("photo_resistor"), pin(pin)
{
  pinMode(pin, INPUT);
}

int PhotoResistor::isDark()
{
  return analogRead(pin) <= TRESHOLD;
};