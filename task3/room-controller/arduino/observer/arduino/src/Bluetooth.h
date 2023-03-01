#ifndef __BLUETOOTH__
#define __BLUETOOTH__

#include "SoftwareSerial.h"
#include "Arduino.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"

class Bluetooth : public Observer<bool>, public Subject<bool>
{
private:
    SoftwareSerial *bt;
    void notify();

public:
    Bluetooth(int rx, int tx);
    void update(Event<bool> *e);
    void start();
};

#endif