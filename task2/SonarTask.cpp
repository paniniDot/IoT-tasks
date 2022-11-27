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
  return sonar->measure();
}

void SonarTask::attach(Observer* o)
{
  this->observers[nObservers] = o;
  this->nObservers++;
}

void SonarTask::detach(Observer* o)
{
  for (int i = 0; i < nObservers; i++) {
    if (this->observers[i] == o) {
      this->observers[i] = this->observers[nObservers - 1];
      this->nObservers--;
      break;
    }
  }
}

void SonarTask::notify()
{
  Event<double> *e = new Event<double>(this->measureWaterLevel());
  for (int i = 0; i < nObservers; i++) {
    this->observers[i]->update(e);
  }
}