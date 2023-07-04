#ifndef __BLUETOOTH__
#define __BLUETOOTH__

#include "SoftwareSerial.h"
#include "Arduino.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"
#include "ArduinoJson.h"
#include "Msg.h"

class Bluetooth : public Observer<Msg>, public Subject<Msg>
{
private:
    SoftwareSerial *bt;
    StaticJsonDocument<JSON_OBJECT_SIZE(2)> doc;
    
public:
    Bluetooth(int rx, int tx);
    void update(Event<Msg> *e);
    void notify();
};

#endif