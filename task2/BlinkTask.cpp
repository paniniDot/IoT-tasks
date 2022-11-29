#include "HardwareSerial.h"
#include "BlinkTask.h"

BlinkTask::BlinkTask(Led *led)
{
  this->led = led;
}

void BlinkTask::init(int period)
{
  Task::init(period);
  state = OFF;
}

void BlinkTask::tick()
{
  if (waterState == PRE_ALARM)
  {
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
  }
  else if (waterState == ALARM)
  {
    this->led->switchOn();
  }
  else if (waterState == NORMAL)
  {
    this->led->switchOff();
  }
}
