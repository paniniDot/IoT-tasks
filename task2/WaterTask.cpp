#include "WaterTask.h"
#include "Arduino.h"

WaterTask::WaterTask(Potentiometer *pot, ServoTimer2 *servo,Led* ledB,Led* ledC)
{
  this->pot = pot;
  this->servo = servo;
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
  else
  {
    Serial.print("POT = ");
    Serial.println(pot->measure());
    servo->write(map(pot->measure(), 0, 1023, 750, 2250));
  }
}

void WaterTask::normalStateHandler()
{
  Serial.println("NORMAL");
  this->ledB->switchOn();
  this->ledC->switchOff();
  servo->write(750);
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
  servo->write(750);
  updateState();
}

void WaterTask::alarmStateHandler()
{
  Serial.println("ALARM");
  this->ledB->switchOff();
  this->ledC->switchOn();
  servo->write(map(sonarMeasure, 30, 70, 750, 2250));
  updateState();
}

void WaterTask::updateState()
{
  waterState = Utils::getWaterState();
}
