#ifndef __SERVOMOTORTASK__
#define __SERVOMOTORTASK__

#include "task/Task.h"
#include "observer/Observer.h"
#include "sensor/ServoTimer2.h"
#include "sensor/Potentiometer.h"
#include "observer/Subject.h"
#include "observer/EventSourceType.h"
#include "task/Utils.h"

class ServoMotorTask : public Task, public Observer<double>, public Subject<double>
{

private:
    Potentiometer *pot;
    ServoTimer2 *servo;
    double currentAngle;
    void notify();

public:
    ServoMotorTask(ServoTimer2 *servo, Potentiometer *pot);
    void init(int period);
    void tick();
    void update(Event<double> *e);
};

#endif
