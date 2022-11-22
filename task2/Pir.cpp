#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

 int Pir::getMotion(){
  if (digitalRead(pin) == HIGH) {
      return 1;
  }
  // Questo IF permette di stabilire se non c'è più nessun movimento
  if (digitalRead(pin) == LOW) {
      return 0;
    
  }
};