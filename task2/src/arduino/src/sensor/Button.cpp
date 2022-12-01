#include "Button.h"

Button::Button()
{
  this->prevts = 0;
  this->pressed = false;
}

void Button::press()
{
  long ts = millis();
  if (ts - this->prevts > 1000)
  {
      this->pressed = true;
    this->prevts = ts;
  }
}

bool Button::isPressed()
{
  return this->pressed;
}


void Button::resetPressed()
{
    this->pressed = false;
}