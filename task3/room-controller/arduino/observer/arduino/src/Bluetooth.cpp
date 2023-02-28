#include "Bluetooth.h"

Bluetooth::Bluetooth(int rxPin, int txPin)
{
    this->bluetooth = new bt(rxPin, txPin);
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
        bt.print("lightstate: ");
        bt.println(value);
    }
    else if (src == EventSourceType::LIGHT)
    {
        double value = *e->getEventArgs();
        bt.print("roll: ");
        bt.println(value);
    }
}

void Bluetooth::notify()
{
    if (bt.available())
    {
        // Serial.write(bt.read());
        String msg = bt.readStringUntil('\n');
        Serial.println(msg);
        else if (msg.startsWith("light"))
        {
            if (msg.endsWith("true"))
            {
                Event<LightState> *e = new Event<LightState>(EventSourceType::LIGHT, new LightState(this->lightState));
                for (int i = 0; i < this->getNObservers(); i++)
                {
                    this->getObservers()[i]->update(e);
                }
                delete e;
            }
            else if (msg.endsWith("false"))
            {
                Event<LightState> *e = new Event<LightState>(EventSourceType::LIGHT, new LightState(this->lightState));
                for (int i = 0; i < this->getNObservers(); i++)
                {
                    this->getObservers()[i]->update(e);
                }
                delete e;
            }
        }
        else
        {
            Event<double> *e = new Event<double>(EventSourceType::SERVO, new LightState(this->lightState));
            for (int i = 0; i < this->getNObservers(); i++)
            {
                this->getObservers()[i]->update(e);
            }
            delete e;
        }
    }
}