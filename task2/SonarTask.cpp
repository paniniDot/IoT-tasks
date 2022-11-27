#include "SonarTask.h"
#include "Arduino.h"
#include "Event.h"

SonarTask::SonarTask(Sonar *sonar)
{
  this->sonar = sonar;
}

void SonarTask::init(int period)
{
  Task::init(period);
}

void SonarTask::tick()
{
  this->notify();
}

double SonarTask::measureWaterLevel()
{
  Serial.print("Sonar = ");
  Serial.println(sonar->measure());
  sonarMeasure = sonar->measure();
  return this->sonar->measure();
}

void SonarTask::notify()
{
  std::double *d = &this->measureWaterLevel();
  Event<double> *e = new Event<double>(d);
  for (auto observer : this->*getObservers()) {
    observer->update(e);
  }
}