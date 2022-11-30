#include "WaterTask.h"
#include "Arduino.h"
<<<<<<< HEAD
#include "GlobalVar.h"
WaterTask::WaterTask(Potentiometer *pot, ServoTimer2 *servo, Led *led)
{
  this->pot = pot;
  this->servo = servo;
  this->led = led;
=======

WaterTask::WaterTask(Potentiometer *pot, Led* ledB)
{
  this->pot = pot;
  this->ledB=ledB;
  this->currentWaterLevel = 0.0;
>>>>>>> develop/observer
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
<<<<<<< HEAD
  this->led->switchOn();
  servo->write(750);
=======
  this->ledB->switchOn();
>>>>>>> develop/observer
  updateState();
}

void WaterTask::preAlarmStateHandler()
{
  Serial.println("PRE_ALARM");
<<<<<<< HEAD
  this->led->switchOn();
  servo->write(750);
=======
  this->ledB->switchOn();
>>>>>>> develop/observer
  updateState();
}

void WaterTask::alarmStateHandler()
{
  Serial.println("ALARM");
<<<<<<< HEAD
  this->led->switchOff();
  servo->write(map(sonarMeasure, WL_MAX, WL2, 750, 2250));
=======
  this->ledB->switchOff();
>>>>>>> develop/observer
  updateState();
}

void WaterTask::updateState()
{
<<<<<<< HEAD
  waterState = Utils::getWaterState(sonarMeasure);
=======
  waterState = Utils::getWaterState(this->currentWaterLevel);
>>>>>>> develop/observer
}

void WaterTask::update(Event<double> *e)
{
  this->currentWaterLevel = *e->getEventArgs();
}

void WaterTask::notify()
{
  Event<WaterState> *e = new Event<WaterState>(EventSourceType::WATER_TASK, new WaterState(this->waterState));
  for(int i = 0; i < this->getNObservers(); i++) {
    this->getObservers()[i]->update(e);
  }
  delete e;
}