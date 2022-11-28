#ifndef __LCDSCREENTASK__
#define __LCDSCREENTASK__

#include "Task.h"
#include "Observer.h"
#include "LiquidCrystal_I2C.h"
#include "LcdEventArg.h"

class LcdScreenTask : public Task, public Observer<LcdEventArg> {
    private:
        LiquidCrystal_I2C *lcdScreen;
        double sonarMeasure;
        double servoMeasure;

    public:
        LcdScreenTask(LiquidCrystal_I2C *lcdScreen);
        void init(int period);
        void tick();
        void update(Event<LcdEventArg> *e);
};

#endif