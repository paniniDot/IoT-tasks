#ifndef __LCDSCREENTASK__
#define __LCDSCREENTASK__

#include "Task.h"
#include "Observer.h"
#include "LiquidCrystal_I2C.h"
#include "EventSourceType.h"
#include "Utils.h"

class LcdScreenTask : public Task, public Observer<double>, public Observer<WaterState> {
    private:
        LiquidCrystal_I2C *lcd;
        double sonarMeasure;
        double servoMeasure;
        WaterState waterState;

    public:
        LcdScreenTask(LiquidCrystal_I2C *lcdScreen);
        void init(int period);
        void tick();
        void update(Event<double> *e);
        void update(Event<WaterState> *e);
};

#endif