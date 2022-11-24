#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
    for (int i = 0; i < 5; i++) {
    Serial.print(i);
    Serial.print(" ");
    delay(1000);
  }
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