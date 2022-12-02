#include "SonarTask.h"

SonarTask::SonarTask(Sonar *sonar)
{
  this->sonar = sonar;
  this->currentWaterState = WaterState::NORMAL;
}

void SonarTask::init(int period)
{
  Task::init(period);
}

void SonarTask::tick()
{
  switch (this->currentWaterState)
  {
  case WaterState::NORMAL:
    Task::updatePeriod(1000);
    break;
  case WaterState::PRE_ALARM:
    Task::updatePeriod(500);
    break;
  case WaterState::ALARM:
    Task::updatePeriod(100);
    break;
  }
  this->notify();
}

double SonarTask::measureWaterLevel()
{
  return this->sonar->measure();
}

void SonarTask::notify()
{
  Event<double> *e = new Event<double>(EventSourceType::SONAR, new double(this->measureWaterLevel()));
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}

void SonarTask::update(Event<WaterState> *e)
{
  this->currentWaterState = *e->getEventArgs();
}