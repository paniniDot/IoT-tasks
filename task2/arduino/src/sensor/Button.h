#ifndef __BUTTON__
#define __BUTTON__
#include "Arduino.h"
class Button
{

private:
  int pin;
  bool manual;
  long prevts;

public:
  Button(int pin);
  void press();
};

#endif