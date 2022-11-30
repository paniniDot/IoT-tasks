#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin)
{
  this->pin = pin;
  pinMode(pin, INPUT);
}

double Potentiometer::measure()
{
  return analogRead(pin);
};