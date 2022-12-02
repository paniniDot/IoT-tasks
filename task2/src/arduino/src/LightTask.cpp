#include "LightTask.h"

LightTask::LightTask(PhotoResistor *pho, Pir *pir, Led *ledA)
{
  this->pho = pho;
  this->pir = pir;
  this->ledA = ledA;
}

void LightTask::init(int period)
{
  Task::init(period);
  this->prevs_time = 0;
  this->lightState = LIGHT_OFF;
  this->waterState = WaterState::NORMAL;
}

void LightTask::tick()
{
  if (this->waterState != ALARM)
  {
    switch (this->lightState)
    {
    case LIGHT_OFF:
      lightOff();
      break;
    case LIGHT_ON:
      lightOn();
      break;
    }
  }
  else
  {
    lightOff();
  }
}

void LightTask::lightOn()
{
  ledA->switchOn();
  if (CheckPeopleLevel() == true)
  {
    long ts = micros();
    this->prevs_time = ts;
  }

  updateState();
}

void LightTask::lightOff()
{
  ledA->switchOff();
  updateState();
}

bool LightTask::CheckPeopleLevel()
{
  return pir->getMotion();
}

double LightTask::CheckLightLevel()
{
  return pho->measure();
}

void LightTask::updateState()
{
  long ts = micros();
  this->lightState = Utils::getLightState(LightTask::CheckPeopleLevel(), LightTask::CheckLightLevel(), ts - this->prevs_time);
}

void LightTask::update(Event<WaterState> *e)
{
  this->waterState = *e->getEventArgs();
}

void LightTask::notify()
{
  Event<LightState> *e = new Event<LightState>(EventSourceType::LIGHT_TASK, new LightState(this->lightState));
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}