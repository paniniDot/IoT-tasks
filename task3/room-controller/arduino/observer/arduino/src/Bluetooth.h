#ifndef __BLUETOOTH__
#define __BLUETOOTH__

#include "observer/Observer.h"
#include "observer/Subject.h"
#include "task/Utils.h"
#include "Arduino.h"
#include "SoftwareSerial.h"

class Bluetooth : public Subject<LightState>, public Observer<LightState>, public Subject<double>, public Observer<double>
{
private:
    SoftwareSerial bluetooth;

public:
    Bluetooth(int rxPin, int txPin);
    void update(Event<LightState> *e);
    void update(Event<double> *e);
};

#endif