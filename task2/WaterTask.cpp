#include "WaterTask.h"
#include "Arduino.h"

WaterTask::WaterTask(Potentiometer *pot, Led* ledB)
{
  this->pot = pot;
  this->ledB=ledB;
  this->currentWaterLevel = 0.0;
}

void WaterTask::init(int period)
{
  Task::init(period);
  this->waterState = NORMAL;
}

void WaterTask::tick()
{
  if (manual == false)
  {
    switch (this->waterState)
    {
    case NORMAL:
      normalStateHandler();
      break;
    case PRE_ALARM:
      preAlarmStateHandler();
      break;
    case ALARM:
      alarmStateHandler();
      break;
    }
  }
  this->notify();
}

void WaterTask::normalStateHandler()
{
  Serial.println("NORMAL");
  this->ledB->switchOn();
  updateState();
}

void WaterTask::preAlarmStateHandler()
{
  Serial.println("PRE_ALARM");
  this->ledB->switchOn();
  updateState();
}

void WaterTask::alarmStateHandler()
{
  Serial.println("ALARM");
  this->ledB->switchOff();
  updateState();
}

void WaterTask::updateState()
{
  waterState = Utils::getWaterState(this->currentWaterLevel);
}

void WaterTask::update(Event<double> *e)
{
  this->currentWaterLevel = *e->getEventArgs();
}

void WaterTask::notify()
{
  Event<WaterState> *e = new Event<WaterState>(EventSourceType::WATER_TASK, &this->waterState);
  for(int i = 0; i < this->getNObservers(); i++) {
    this->getObservers()[i]->update(e);
  }
  delete e;
}