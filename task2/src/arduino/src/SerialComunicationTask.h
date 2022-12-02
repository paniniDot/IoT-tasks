#ifndef __SERIALCOMUNICATIONTASK__
#define __SERIALCOMUNICATIONTASK__

#include "task/Task.h"
#include "observer/Observer.h"
#include "sensor/LiquidCrystal_I2C.h"
#include "observer/EventSourceType.h"
#include "task/Utils.h"
#include "Arduino.h"
#include "observer/Subject.h"

class SerialComunicationTask : public Task, public Subject<double>
{

private:
    void notify();

public:
    String content;
    String currentMsg;
    bool msgAvailable;
    SerialComunicationTask();
    void init(int period);
    void tick();
    bool isMsgAvailable();
    String receiveMsg();
    void update(Event<double> *e);
};
extern SerialComunicationTask serialComunicationTask;

#endif