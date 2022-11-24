#ifndef __UTILS__
#define __UTILS__

#include "State.h"

#define WL1 100
#define WL2 70
#define WL_MAX 30

class Utils {

public:

  static WaterState getWaterState(double waterLevel) {
    if (waterLevel < WL_MAX){
      return ALARM;
    } else if (waterLevel < WL2) {
      return PRE_ALARM;
    } else {
      return NORMAL;
    } 
  }

  static PeopleState getPeopleState(int pir, double light) {
    if (pir == 1 && light < 100) {
      return LIGHT_ON;
    } else {
      return LIGHT_OFF;
    }
  }
};

#endif
