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
  Event<double> *e = new Event<double>(new double(this->measureWaterLevel()));

  for(int i = 0; i < this->getNObservers(); i++) {
    this->getObservers()[i]->update(e);
  }
}