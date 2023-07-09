#ifndef __LIGHT__
#define __LIGHT__
#include "Arduino.h"
#include <TimeLib.h>

class Light
{

private:
  int pin;

public:
  Light(int pin);
  void gradualBrightness();
};

#endif