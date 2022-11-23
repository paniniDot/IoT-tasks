#include "PotentioMeter.h"
#include "Arduino.h"

PotentioMeter::PotentioMeter(string pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

 double PotentioMeter::measure(){
  return analogRead(pin);
};