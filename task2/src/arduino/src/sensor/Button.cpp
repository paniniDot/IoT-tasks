#include "Button.h"

Button::Button()
{
  this->prevts = 0;
}

bool Button::press()
{
  long ts = millis();
  if (ts - this->prevts > 1000)
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
    return true;
  }
  return false;
}
