#include "Bluetooth.h"

Bluetooth::Bluetooth(int rx, int tx)
{
    this->bt = new SoftwareSerial(rx, tx);
    bt->begin(9600);
    Serial.println("ready to go.");
}
void Bluetooth::start()
{
    while (true)
    {
        this->notify();
    }
}
void Bluetooth::update(Event<bool> *e)
{
    EventSourceType src = e->getSrcType();
    if (src == EventSourceType::LIGHT)
    {
        bool value = *e->getEventArgs();
        this->bt->print("lightstate: ");
        this->bt->println(value);
    }
    else if (src == EventSourceType::SERVO)
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
        String msg = this->bt->readStringUntil('\n');
        Serial.println(msg);
        if (msg.startsWith("connesso"))
        {
            Event<bool> *e = new Event<bool>(EventSourceType::BLUETOOTH, new bool(false));
            for (int i = 0; i < this->getNObservers(); i++)
            {
                this->getObservers()[i]->update(e);
            }
            delete e;
        }
        else if (msg.startsWith("light"))
        {
            if (msg.endsWith("true"))
            {
                Event<bool> *e = new Event<bool>(EventSourceType::LIGHT, new bool(true));
                for (int i = 0; i < this->getNObservers(); i++)
                {
                    this->getObservers()[i]->update(e);
                }
                delete e;
            }
            else if (msg.endsWith("false"))
            {
                Event<bool> *e = new Event<bool>(EventSourceType::LIGHT, new bool(false));
                for (int i = 0; i < this->getNObservers(); i++)
                {
                    this->getObservers()[i]->update(e);
                }
                delete e;
            }
        }
    }
}