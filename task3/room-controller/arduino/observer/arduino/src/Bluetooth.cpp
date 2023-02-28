#include "Bluetooth.h"

Bluetooth::Bluetooth(SoftwareSerial *bluetooth)
{
    this->bt = bluetooth;
    while (true)
    {
        this->notify();
    }
}

void Bluetooth::update(Event<LightState> *e)
{
    EventSourceType src = e->getSrcType();
    if (src == EventSourceType::SERVO)
    {
        bool value = *e->getEventArgs();
        this->bt->print("lightstate: ");
        this->bt->println(value);
    }
    else if (src == EventSourceType::LIGHT)
    {
        double value = *e->getEventArgs();
        this->bt->print("roll: ");
        this->bt->println(value);
    }
}

void Bluetooth::notify()
{
    if (this->bt->available())
    {
        // Serial.write(bt.read());
        String msg = this->bt->readStringUntil('\n');
        Serial.println(msg);
    }
}