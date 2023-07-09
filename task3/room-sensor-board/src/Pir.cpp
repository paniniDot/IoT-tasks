#include "Pir.h"

Pir::Pir(int pin) : JSONSensor<int>("pir_sensor"), pin(pin)
{
  pinMode(pin, INPUT);
  for (int i = 0; i < 5; i++)
  {
    delay(1000);
  }
}

int Pir::getMotion()
{
  return digitalRead(this->pin) == HIGH;
};
