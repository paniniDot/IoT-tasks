#include "Sonar.h"
#include "Arduino.h"
const float vs = 331.45 + 0.62 * 20;
Sonar::Sonar(int triggerPin, int echoPin)
{
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

double Sonar::measure()
{
  /* invio impulso */
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(3);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);

  /* ricevi l’eco */
  float tUS = pulseIn(echoPin, HIGH);
  float t = tUS / 100.0 / 100.0 / 2;
  float d = t * vs;
  return d;
};