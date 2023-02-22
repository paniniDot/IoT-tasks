#include "SoftwareSerial.h"
#include <Servo.h>
#include <String.h>

Servo myservo;            // create servo object to control a servo
SoftwareSerial bt(2, 3);  // RX pin, TX pin
bool ledstatus = false;
int servo = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  bt.begin(9600);
  Serial.println("ready to go.");
  myservo.attach(6);
}

void loop() {
  if (bt.available()) {
    //Serial.write(bt.read());
    String msg = bt.readStringUntil('\n');
    Serial.println(msg);
    if (msg == "connesso") {
      bt.print("ledstatus");
      bt.println(ledstatus);
      delay(100);
      bt.print("servo");
      bt.println(servo);
    } else if (msg == "on") {
      Serial.println("accendo");
      ledstatus = true;
    } else if (msg == "of") {
      Serial.println("spengo");
      ledstatus = false;
    } else {
      myservo.write(map(msg.toInt(), 0, 100, 0, 1023));
      servo = msg.toInt();
    }
  }

  if (Serial.available()) {
  }
}