#include "Button.h"

Button::Button(int pin)
{
  pin = pin;
  prevts = 0;
}

void Button::press()
{
  long ts = micros();
  if (ts - prevts > 1000000)
  {
    prevts = ts;
    return true;
  }else {
    return false;
  }
};