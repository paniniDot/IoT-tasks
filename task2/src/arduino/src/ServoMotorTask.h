#ifndef __SERVOMOTORTASK__
#define __SERVOMOTORTASK__

#include "task/Task.h"
#include "observer/Observer.h"
#include "sensor/ServoTimer2.h"
#include "observer/Subject.h"
#include "observer/EventSourceType.h"
#include "task/Utils.h"

class ServoMotorTask : public Task, public Observer<double>, public Observer<bool>, public Subject<double>
{

private:
    ServoTimer2 *servo;
    double currentAngle;
    bool manual;
    void notify();

public:
    ServoMotorTask(ServoTimer2 *servo);
    void init(int period);
    void tick();
    void update(Event<double> *e);
    void update(Event<bool> *e);
};

#endif
