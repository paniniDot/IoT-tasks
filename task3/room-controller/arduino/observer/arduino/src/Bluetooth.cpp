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
void Bluetooth::update(Event<int> *e)
{
    EventSourceType src = e->getSrcType();
    if (src == EventSourceType::LIGHT)
    {
        int value = *e->getEventArgs();
        this->bt->print("lightstate: ");
        this->bt->println(value != 0);
    }
    else if (src == EventSourceType::SERVO)
    {
        int value = *e->getEventArgs();
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
            Event<int> *e = new Event<int>(EventSourceType::BLUETOOTH, new int(0));
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
                Event<int> *e = new Event<int>(EventSourceType::LIGHT, new int(1));
                for (int i = 0; i < this->getNObservers(); i++)
                {
                    this->getObservers()[i]->update(e);
                }
                delete e;
            }
            else if (msg.endsWith("false"))
            {
                Event<int> *e = new Event<int>(EventSourceType::LIGHT, new int(0));
                for (int i = 0; i < this->getNObservers(); i++)
                {
                    this->getObservers()[i]->update(e);
                }
                delete e;
            }
        }
        else
        {
            int value = msg.toInt();
            Event<int> *e = new Event<int>(EventSourceType::SERVO, new int(value));
            for (int i = 0; i < this->getNObservers(); i++)
            {
                this->getObservers()[i]->update(e);
            }
            delete e;
        }
    }
}