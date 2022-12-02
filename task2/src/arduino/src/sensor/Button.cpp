#include "Button.h"
#define TIME_TO_WAIT 1000

Button::Button()
{
  this->prevts = 0;
  this->pressed = false;
}

void Button::press()
{
  long ts = millis();
  if (ts - this->prevts > TIME_TO_WAIT)
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