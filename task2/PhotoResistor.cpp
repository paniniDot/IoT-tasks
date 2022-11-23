#include "PhotoResistor.h"
#include "Arduino.h"

PhotoResistor::PhotoResistor(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

 double PhotoResistor::measure(){
  return analogRead(pin);
};