#ifndef __UTILS__
#define __UTILS__
#include "Arduino.h"

#define WL1 30
#define WL2 15
#define WL_MAX 5
#define THL 100
#define T1 5000000
enum WaterState
{
  NORMAL,
  PRE_ALARM,
  ALARM
};

enum LightState
{
  LIGHT_ON,
  LIGHT_OFF
};

class Utils
{

public:
  static WaterState getWaterState(double currentWaterLevel)
  {
    if (currentWaterLevel <= WL2)
    {
      return ALARM;
    }
    else if (currentWaterLevel > WL2 && currentWaterLevel <= WL1)
    {
      return PRE_ALARM;
    }
    else
    {
      return NORMAL;
    }
  }

  static LightState getLightState(bool pir, double light, long ms)
  {
    if ((pir && light < THL) || (!pir && ms < T1))
    {
      return LIGHT_ON;
    }
    else if ((!pir && ms >= T1) || (pir && light >= THL))
    {
      return LIGHT_OFF;
    }
    else
    {
      return LIGHT_OFF;
    }
  }
};

#endif
