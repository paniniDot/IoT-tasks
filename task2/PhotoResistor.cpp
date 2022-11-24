#include "PhotoResistor.h"
#include "Arduino.h"

PhotoResistor::PhotoResistor(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
}

 double PhotoResistor::measure(){
  return analogRead(pin);
};