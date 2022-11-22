#include "Servo.h"
#include "Arduino.h"

Servo::Servo(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

 void Servo::setServo(int cm){
    servo_9.write(cm);
};