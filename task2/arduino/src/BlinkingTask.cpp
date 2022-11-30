#include "BlinkingTask.h"

BlinkingTask::BlinkingTask(Led *led)
{
  this->led = led;
}

void BlinkingTask::init(int period)
{
  Task::init(period);
  this->state = OFF;
  this->waterState = WaterState::NORMAL;
}

void BlinkingTask::tick()
{
  switch (this->waterState)
  {
  case NORMAL:
    this->led->switchOff();
    break;
  case PRE_ALARM:
    switch (state)
    {
    case OFF:
      this->led->switchOn();
      state = ON;
      break;
    case ON:
      this->led->switchOff();
      state = OFF;
      break;
    }
    break;
  case ALARM:
    this->led->switchOn();
    break;
  }
}

void BlinkingTask::update(Event<WaterState> *e)
{
  this->waterState = *e->getEventArgs();
}
