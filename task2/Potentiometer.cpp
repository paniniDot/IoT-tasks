#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

 double Potentiometer::measure(){
  return analogRead(pin);
};