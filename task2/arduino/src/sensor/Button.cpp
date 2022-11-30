#include "Button.h"

Button::Button(int pin)
{
  pin = pin;
  manual = false;
  prevts = 0;
}

void Button::press()
{
  long ts = micros();
  if (ts - prevts > 1000000)
  {
    Serial.print("button = ");
    Serial.println(manual);
    if (manual == false)
    {
      manual = true;
    }
    else
    {
      manual = false;
    }
    prevts = ts;
  }
};