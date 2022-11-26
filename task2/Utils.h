#ifndef __UTILS__
#define __UTILS__

#include "State.h"

#define WL1 100
#define WL2 70
#define WL_MAX 30
#define THL 100
 
extern bool manual;

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

  static PeopleState getPeopleState(bool pir, double light) {
    if (pir == true && light < THL) {
      return LIGHT_ON;
    } else {
      return LIGHT_OFF;
    }
  }
};

#endif
