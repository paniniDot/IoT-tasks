#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(string pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

 double Potentiometer::measure(){
  return analogRead(pin);
};