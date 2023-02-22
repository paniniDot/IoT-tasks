#include "SoftwareSerial.h"
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
SoftwareSerial bt(2, 3);  // RX pin, TX pin

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  bt.begin(9600);
  Serial.println("sending cmd..");
  bt.print("AT");
  delay(1000);
  bt.print("AT+NAMEisi00");  // Set the name to isiXX
  delay(1000);

  myservo.attach(6);
}

void loop() {
  if (bt.available()) {
    Serial.write(bt.read());
    myservo.write(0);
  }

  if (Serial.available()) {
    bt.write(Serial.read());
    myservo.write(1023);
  }
  
  delay(15);
}