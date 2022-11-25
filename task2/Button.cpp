#include "Button.h"
#include "Arduino.h"

Button::Button(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
}

 bool Button::press(){
  return digitalRead(pin);
};