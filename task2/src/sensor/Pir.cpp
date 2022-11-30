#include "Pir.h"

Pir::Pir(int pin)
{
  this->pin = pin;
  pinMode(pin, INPUT);
  for (int i = 0; i < 5; i++)
  {
    Serial.print(i);
    Serial.print(" ");
    delay(1000);
  }
}

bool Pir::getMotion()
{
  if (digitalRead(pin) == HIGH)
  {
    return true;
  }
  // Questo IF permette di stabilire se non c'è più nessun movimento
  if (digitalRead(pin) == LOW)
  {
    return false;
  }
};