#include "Pir.h"

Pir::Pir(int pin) : JSONSensor<bool>("pir_sensor"), pin(pin)
{
  pinMode(pin, INPUT);
  for (int i = 0; i < 5; i++)
  {
    delay(1000);
  }
}

bool Pir::getMotion()
{
  return digitalRead(this->pin) == HIGH;
};
