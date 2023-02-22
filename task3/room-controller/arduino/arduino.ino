#include "SoftwareSerial.h"
#include <Servo.h>

Servo myservo;            // create servo object to control a servo
SoftwareSerial bt(2, 3);  // RX pin, TX pin

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  while (!Serial) {};
  Serial.println("ready to go.");
  myservo.attach(6);
}

void loop() {
  if (bt.available()) {
    //Serial.write(bt.read());
    String msg = bt.readStringUntil('\n');
    Serial.println(msg);
    if (msg == "180") {
      Serial.println("1023");
      myservo.write(1023);
    } else if (msg == "0") {
      Serial.println("0");
      myservo.write(0);
    }
  }

  if (Serial.available()) {
    bt.write(Serial.read());
  }
}