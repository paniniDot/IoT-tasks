/*#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd_1(0);
Servo servo_9;

int cm =0 ;
int triggerPin = 8;
int echoPin = 7;
int pirPin = 10;
int servoPin = 4;
#define fotoPin A0

void readUltrasonicDistance()
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  cm = 0.01723 *pulseIn(echoPin, HIGH);
  Serial.print(cm);
  Serial.println("cm");
}

void readPir()
{
  if (digitalRead(pirPin) == HIGH) {
      Serial.println("rilevato");
  }
  // Questo IF permette di stabilire se non c'è più nessun movimento
  if (digitalRead(pirPin) == LOW) {
      Serial.println("non rilevo");      //output

  }
}

void readfoto()
{
  Serial.println(analogRead(fotoPin));
}

void readServo(){
    servo_9.write(cm);
}

void setup()
{
  lcd_1.begin(16, 2);
 lcd_1.print("hello world");
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin , INPUT);
  pinMode(fotoPin,INPUT);
  for (int i = 0; i < 5; i++) {
    Serial.print(i);
    Serial.print(" ");
    delay(1000);
  }
  servo_9.attach(servoPin, 500, 2500);
}

void loop()
{
  readUltrasonicDistance();
  readPir();
  readServo();
  readfoto();
  delay(1000); // Wait for 100 millisecond(s)
}*/