#ifndef __UTILS__
#define __UTILS__

#include "State.h"
#include "Arduino.h"

#define WL1 100
#define WL2 70
#define WL_MAX 30
#define THL 100
#define T1 5000000 

extern bool manual;
extern double sonarMeasure;

class Utils {

public:
 
  static WaterState getWaterState(double waterLevel) {
    if (waterLevel > WL_MAX && waterLevel <= WL2){
      return ALARM;
    } else if (waterLevel > WL2 && waterLevel <= WL1) {
      return PRE_ALARM;
    } else {
      return NORMAL;
    } 
  }

  static PeopleState getPeopleState(bool pir, double light, long ms) {
    if ((pir && light < THL) || (!pir && ms < T1)) {
      return LIGHT_ON;
    } else if ((!pir && ms >= T1) || (pir && light >= THL)) {
      return LIGHT_OFF;
    } else {
      Serial.println("Dio cacca");
      return LIGHT_OFF;
    }
  }
};

#endif
