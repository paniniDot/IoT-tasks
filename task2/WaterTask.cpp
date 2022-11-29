#include "WaterTask.h"
#include "Arduino.h"
#include "GlobalVar.h"
WaterTask::WaterTask(Potentiometer *pot, ServoTimer2 *servo, Led *led)
{
  this->pot = pot;
  this->servo = servo;
  this->led = led;
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
  this->led->switchOn();
  servo->write(750);
  updateState();
}

void WaterTask::preAlarmStateHandler()
{
  Serial.println("PRE_ALARM");
  this->led->switchOn();
  servo->write(750);
  updateState();
}

void WaterTask::alarmStateHandler()
{
  Serial.println("ALARM");
  this->led->switchOff();
  servo->write(map(sonarMeasure, WL_MAX, WL2, 750, 2250));
  updateState();
}

void WaterTask::updateState()
{
  waterState = Utils::getWaterState(sonarMeasure);
}
