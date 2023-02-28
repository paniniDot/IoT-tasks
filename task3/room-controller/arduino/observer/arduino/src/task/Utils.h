#ifndef __UTILS__
#define __UTILS__
#include "Arduino.h"

enum LightState
{
  LIGHT_ON,
  LIGHT_OFF
};

class Utils
{

public:
  static LightState getLightState(double light)
  {
    if (light > 0)
    {
      return LIGHT_ON;
    }
    else
    {
      return LIGHT_OFF;
    }
  }
};

#endif
