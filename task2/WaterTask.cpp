#include "WaterTask.h"
#include "Arduino.h"

WaterTask::WaterTask(Potentiometer *pot, ServoTimer2 *servo,Led* led1,Led* led2)
{
  this->pot = pot;
  this->servo = servo;
  this->led1=led1;
  this->led2=led2;

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
  servo->write(750);
  updateState();
}

void WaterTask::preAlarmStateHandler()
{
  servo->write(750);
  updateState();
}

void WaterTask::alarmStateHandler()
{
  servo->write(map(sonarMeasure, 30, 70, 750, 2250));
  updateState();
}

void WaterTask::updateState()
{
  waterState = Utils::getWaterState(sonarMeasure);
}
