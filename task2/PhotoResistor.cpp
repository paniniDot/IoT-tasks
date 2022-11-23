#include "PhotoResistor.h"
#include "Arduino.h"

PhotoResistor::PhotoResistor(string pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

 double PhotoResistor::measure(){
  return analogRead(pin);
};