#ifndef __BUTTON__
#define __BUTTON__
#include "Arduino.h"
class Button
{

private:
  long prevts;
  bool pressed;

public:
  Button();
  void press();
  bool isPressed();
  void resetPressed();
};

#endif