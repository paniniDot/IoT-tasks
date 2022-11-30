#include "WaterTask.h"

WaterTask::WaterTask(Potentiometer *pot, Led *ledB)
{
  this->pot = pot;
  this->ledB = ledB;
  this->currentWaterLevel = 0.0;
}

void WaterTask::init(int period)
{
  Task::init(period);
  this->waterState = NORMAL;
}

void WaterTask::tick()
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

  // if (manual == false)
  // {
  //   switch (this->waterState)
  //   {
  //   case NORMAL:
  //     normalStateHandler();
  //     break;
  //   case PRE_ALARM:
  //     preAlarmStateHandler();
  //     break;
  //   case ALARM:
  //     alarmStateHandler();
  //     break;
  //   }
  // }
  this->notify();
}

void WaterTask::normalStateHandler()
{
  this->ledB->switchOn();
  updateState();
}

void WaterTask::preAlarmStateHandler()
{
  this->ledB->switchOn();
  updateState();
}

void WaterTask::alarmStateHandler()
{
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
  Event<WaterState> *e = new Event<WaterState>(EventSourceType::WATER_TASK, new WaterState(this->waterState));
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}