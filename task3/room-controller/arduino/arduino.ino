#include "SoftwareSerial.h"
#include <Servo.h>
#include <String.h>
#define RX_PIN 2 // Define the RX pin for BT communication
#define TX_PIN 3 // Define the TX pin for BT communication

Servo myservo;            // create servo object to control a servo
SoftwareSerial bt(RX_PIN, TX_PIN); // RX pin, TX pin
bool lightstate = false;
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
    if (msg.startsWith("connesso")) {
      bt.print("lightstate: ");
      bt.println(lightstate);
      delay(100);
      bt.print("roll: ");
      bt.println(servo);
    } else if (msg.startsWith("light")) {
        if (msg.endsWith("true")) {
          Serial.println("accendo");
          lightstate = true;
        } else if (msg.endsWith("false")) {
          Serial.println("spengo");
          lightstate = false;
        }
    } else {
      myservo.write(map(msg.toInt(), 0, 100, 0, 1023));
      servo = msg.toInt();
    }
  }

  if (Serial.available()) {
     bt.write(Serial.read());
  }
}