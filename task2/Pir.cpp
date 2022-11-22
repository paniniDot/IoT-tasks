#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

 double Pir::getMotion(){
  if (digitalRead(pin) == HIGH) {
      Serial.println("rilevato");
  }
  // Questo IF permette di stabilire se non c'è più nessun movimento
  if (digitalRead(pin) == LOW) {
      Serial.println("non rilevo");      //output
    
  }
};