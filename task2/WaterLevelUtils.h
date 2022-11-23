#ifndef __WATERLEVELUTILS__
#define __WATERLEVELUTILS__

#define WL1 100
#define WL2 70
#define WL_MAX 30

class WaterLevelUtils {

    enum State { NORMAL, PRE_ALARM, ALARM };


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