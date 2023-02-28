#ifndef __BLUETOOTH__
#define __BLUETOOTH__

#include "task/Utils.h"
#include "observer/Observer.h"
#include "Arduino.h"
#include "observer/Subject.h"
#include "SoftwareSerial.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"

class Bluetooth : public Subject<LightState>, public Observer<LightState>
{
private:
    SoftwareSerial *bt;
    LightState lightState;

public:
    Bluetooth(SoftwareSerial *bluetooth);
    void update(Event<LightState> *e);
    void notify();
};

#endif