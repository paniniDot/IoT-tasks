#include "Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int triggerPin, int echoPin){
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
  pinMode(pin,OUTPUT);
}

 int Sonar::waterLevel(){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return = 0.01723 *pulseIn(echoPin, HIGH);
};