#include "ServoMotorTask.h"
#include "Arduino.h"
#include "Utils.h"

#define MIN_ANGLE 750
#define MAX_ANGLE 2250

ServoMotorTask::ServoMotorTask(ServoTimer2 *servo){
  this->servo = servo;
  this->currentAngle = MIN_ANGLE;
}

void ServoMotorTask::init(int period){
  Task::init(period);
}

void ServoMotorTask::tick(){
    this->servo->write(map(this->currentAngle, WL2, WL_MAX, MIN_ANGLE, MAX_ANGLE));
}

void ServoMotorTask::update(Event<double> *e){
  this->currentAngle = *e->getEventArgs();
}
