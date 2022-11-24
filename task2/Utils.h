#ifndef __UTILS__
#define __UTILS__

#include "State.h"

#define WL1 100
#define WL2 70
#define WL_MAX 30

class Utils {

public:

    static WaterState getWaterState(double waterLevel) {
        if (waterLevel < WL1) {
            return NORMAL;
        } else if (waterLevel >= WL1 && waterLevel < WL2) {
            return PRE_ALARM;
        } else {
            return ALARM;
        }
    }

        static PeopleState getPeopleState(int pir, double light) {
          if(pir==1 && light > 100){
            return PRESENT_DAY;
          }else if(pir==1 && light < 100){
            return PRESENT_NIGHT;
          } else if(pir==0 && light > 100){
            return NOT_PRESENT_DAY;
          } else{
            return NOT_PRESENT_NIGHT;
          }
            
    }

};

#endif