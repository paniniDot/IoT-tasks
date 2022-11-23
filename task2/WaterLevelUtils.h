#ifndef __WATERLEVELUTILS__
#define __WATERLEVELUTILS__

#include "State.h"

#define WL1 100
#define WL2 70
#define WL_MAX 30

class WaterLevelUtils {

public:

    static State getState(double waterLevel) {
        if (waterLevel < WL1) {
            return NORMAL;
        } else if (waterLevel >= WL1 && waterLevel < WL2) {
            return PRE_ALARM;
        } else {
            return ALARM;
        }
    }

};

#endif