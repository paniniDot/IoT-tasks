#ifndef __SERVOMOTORTASK__
#define __SERVOMOTORTASK__

#include "Task.h"
#include "Observer.h"
#include "ServoTimer2.h"

class ServoMotorTask : public Task, public Observer {

    private:
        ServoTimer2 *servo;
        int currentAngle;

    public:
        ServoMotorTask(ServoTimer2 *servo);
        void init(int period);
        void tick();
        void update(Event<double> *e);
};

#endif
