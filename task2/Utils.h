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
            return PRESENT_DAY;
    }

};

#endif