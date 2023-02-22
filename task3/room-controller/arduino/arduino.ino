#include "SoftwareSerial.h"
#include <Servo.h>
#include <String.h>

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
    if (msg == "on") {
      Serial.println("accendo");
    }else if (msg == "of") {
      Serial.println("spengo");
    }else {
      myservo.write(map(msg.toInt(), 0, 100, 0, 1023));
    }
  }

  if (Serial.available()) {
    bt.write(Serial.read());
  }
}