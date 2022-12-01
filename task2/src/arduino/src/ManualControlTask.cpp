#include "ManualControlTask.h"

ManualControlTask::ManualControlTask(Button *button)
{
    this->button = button;
    this->manual = false;
}

void ManualControlTask::init(int period)
{
    Task::init(period);
}

void ManualControlTask::tick()
{
    if (button->isPressed())
    {
        this->manual = !this->manual;
        button->resetPressed();
        notify();
    }
}

void ManualControlTask::notify()
{
    Event<bool> *e = new Event<bool>(EventSourceType::SERVO, new bool(this->manual));
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}