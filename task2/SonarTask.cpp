#include "SonarTask.h"
#include "Arduino.h"

SonarTask::SonarTask(Sonar* sonar) {
  this->sonar = sonar;
}

void SonarTask::init(int period) {
  Task::init(period);
}

void SonarTask::tick() {
   updateState();
}

double SonarTask::measureWaterLevel() {
  Serial.print("Sonar = ");
  Serial.println(sonar->measure());
  return sonar->measure();
}

void SonarTask::updateState() {
  waterState = Utils::getWaterState(SonarTask::measureWaterLevel());
}