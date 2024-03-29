#ifndef __LCDSCREENTASK__
#define __LCDSCREENTASK__

#include "task/Task.h"
#include "observer/Observer.h"
#include "sensor/LiquidCrystal_I2C.h"
#include "observer/EventSourceType.h"
#include "task/Utils.h"
#include "Arduino.h"

class LcdScreenTask : public Task, public Observer<double>, public Observer<WaterState>, public Observer<LightState>
{
private:
    LiquidCrystal_I2C *lcd;
    double sonarMeasure;
    double servoMeasure;
    WaterState waterState;
    LightState lightState;

public:
    LcdScreenTask(LiquidCrystal_I2C *lcdScreen);
    void init(int period);
    void tick();
    void update(Event<double> *e);
    void update(Event<WaterState> *e);
    void update(Event<LightState> *e);
};

#endif