//implements Task header

#include "SonarTask.h"
#include "Arduino.h"

SonarTask::SonarTask(Sonar* sonar) {
    this->sonar = sonar;
}

void SonarTask::init() {
}

void SonarTask::tick() {
    Serial.println(sonar->measure());
}