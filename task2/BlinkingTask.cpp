#include "BlinkingTask.h"
#include "Arduino.h"

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
    Serial.println("BLINKING TASK: tick()");
  if (this->waterState == PRE_ALARM)
  {
    Serial.println("BLINKING TASK: PRE_ALARM");
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
  else if (this->waterState == ALARM)
  {
    Serial.println("BLINKING TASK: ALARM");
    this->led->switchOn();
  }
  else if (this->waterState == NORMAL)
  {
    Serial.println("BLINKING TASK: NORMAL");
    this->led->switchOff();
  }
}

void BlinkingTask::update(Event<WaterState> *e)
{
  this->waterState = *e->getEventArgs();
  Serial.print("BLINKING TASK: update() - ");
  Utils::displayEnum(this->waterState);
}