#include "WaterTask.h"
#include "Arduino.h"

WaterTask::WaterTask(Potentiometer *pot, Led* ledB,Led* ledC)
{
  this->pot = pot;
  this->ledB=ledB;
  this->ledC=ledC;
}

void WaterTask::init(int period)
{
  Task::init(period);
  waterState = NORMAL;
}

void WaterTask::tick()
{
  if (manual == false)
  {
    switch (waterState)
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
}

void WaterTask::normalStateHandler()
{
  Serial.println("NORMAL");
  this->ledB->switchOn();
  this->ledC->switchOff();
  updateState();
}

void WaterTask::preAlarmStateHandler()
{
  Serial.println("PRE_ALARM");
  this->ledB->switchOn();
  if(this->ledC->isOn()) {
    this->ledC->switchOff();
  } else {
    this->ledC->switchOn();
  }
  updateState();
}

void WaterTask::alarmStateHandler()
{
  Serial.println("ALARM");
  this->ledB->switchOff();
  this->ledC->switchOn();
  updateState();
}

void WaterTask::updateState()
{
  waterState = Utils::getWaterState();
}
