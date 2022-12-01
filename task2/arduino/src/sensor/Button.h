#ifndef __BUTTON__
#define __BUTTON__
#include "Arduino.h"
class Button
{

private:
  int pin;
  long prevts;

public:
  Button(int pin);
  bool press();
};

#endif