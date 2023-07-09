#include "Pir.h"

Pir::Pir(int pir_pin, int led_pin) : JSONSensor<int>("pir_sensor"), pir_pin(pir_pin), led_pin(led_pin) {
  pinMode(pir_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  for (int i = 0; i < 5; i++) {
    delay(1000);
  }
}

int Pir::getMotion() {
  if (digitalRead(this->pir_pin) == HIGH) {
    analogWrite(this->led_pin, 255);
    return 1;
  } else {
    analogWrite(this->led_pin, 0);
    return 0;
  }
};
