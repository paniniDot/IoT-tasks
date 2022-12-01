#include "Button.h"

Button::Button()
{
  this->prevts = 0;
  this->manual = false;
}

bool Button::press()
{
  long ts = millis();
  if (ts - this->prevts > 1000)
  {
    Serial.print("button = ");
    Serial.println(this->manual);
    if (this->manual == false)
    {
      this->manual = true;
    }
    else
    {
      this->manual = false;
    }
    this->prevts = ts;
    return true;
  }
  return false;
}
