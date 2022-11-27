#ifndef __UTILS__
#define __UTILS__
#include "Arduino.h"

#define WL1 100
#define WL2 70
#define WL_MAX 30
#define THL 100
#define T1 5000000

extern bool manual;
extern double sonarMeasure;
enum WaterState
{
  NORMAL,
  PRE_ALARM,
  ALARM
};

enum PeopleState
{
  LIGHT_ON,
  LIGHT_OFF
};
class Utils
{

public:
  static WaterState getWaterState()
  {
    if (sonarMeasure > WL_MAX && sonarMeasure <= WL2)
    {
      return ALARM;
    }
    else if (sonarMeasure > WL2 && sonarMeasure <= WL1)
    {
      return PRE_ALARM;
    }
    else
    {
      return NORMAL;
    }
  }

  static PeopleState getPeopleState(bool pir, double light, long ms)
  {
    if(sonarMeasure < WL_MAX){
      return LIGHT_OFF;
    }
    else if ((pir && light < THL) || (!pir && ms < T1))
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
