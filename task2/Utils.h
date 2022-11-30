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

enum PeopleState
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

  static PeopleState getPeopleState(bool pir, double light, long ms, double sonarMeasure)
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

  static void print_bytes(const void *object, size_t size)
{
#ifdef __cplusplus
  const unsigned char * const bytes = static_cast<const unsigned char *>(object);
#else // __cplusplus
  const unsigned char * const bytes = object;
#endif // __cplusplus

  size_t i;

  Serial.print("[ ");
  for(i = 0; i < size; i++)
  {
    Serial.print(bytes[i]);
  }
  Serial.println("]");
}

};

#endif
