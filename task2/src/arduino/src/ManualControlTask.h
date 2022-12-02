#ifndef __MANUAL_CONTROL_TASK_H__
#define __MANUAL_CONTROL_TASK_H__

#include "task/Task.h"
#include "observer/Subject.h"
#include "sensor/Button.h"

class ManualControlTask : public Task, public Subject<bool>
{
private:
    Button *button;
    bool manual;

    void notify();

public:
    ManualControlTask(Button *button);
    void init(int period);
    void tick();
};

#endif