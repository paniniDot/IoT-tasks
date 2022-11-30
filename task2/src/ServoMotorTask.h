#ifndef __SERVOMOTORTASK__
#define __SERVOMOTORTASK__

#include "Task.h"
#include "observer/Observer.h"
#include "sensor/ServoTimer2.h"
#include "observer/Subject.h"
#include "observer/EventSourceType.h"
#include "sensor/Utils.h"

class ServoMotorTask : public Task, public Observer<double>, public Subject<double>
{

private:
    ServoTimer2 *servo;
    double currentAngle;
    void notify();

public:
    ServoMotorTask(ServoTimer2 *servo);
    void init(int period);
    void tick();
    void update(Event<double> *e);
};

#endif
