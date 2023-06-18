#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT_Client.h"
#include <esp_system.h>
#include "src/Pir.h"
#include "src/PhotoResistor.h"
#define PIR_PIN 34
#define PHOTO_RESISTOR_PIN 24

/* wifi network info */
const char* ssid = "asus";
const char* password = "0123456789";
/* MQTT server address */
const char* mqtt_server = "192.168.2.2";
const int mqtt_port = 1883;
/* MQTT topics */
const char* topic_light = "/esp/light";
const char* topic_motion = "/esp/motion";
/* MQTT client management */
WiFiClient espClient;
Adafruit_MQTT_Client mqttClient(&espClient, mqtt_server, mqtt_port);
Adafruit_MQTT_Publish publisher_light(&mqttClient, topic_light);
Adafruit_MQTT_Publish publisher_motion(&mqttClient, topic_motion);

/* Hardware objects */
PhotoResistor* resistor;
Pir* pir;

void setup_wifi() {
  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
}

void connectToMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT server...");
    if (!mqttClient.connect()) {
      Serial.print("failed, rc=");
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
  Serial.println("connected");
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  resistor = new PhotoResistor(PHOTO_RESISTOR_PIN);
  pir = new Pir(PIR_PIN);
}

void loop() {
  if (!mqttClient.connected()) {
    connectToMQTT();
  }
  // Publish light value
  String lightValue = resistor->toJson();
  if (publisher_light.publish(lightValue.c_str())) {
    Serial.println("Published light value");
  } else {
    Serial.println("Failed to publish light value");
  }

  // Publish motion value
  String motionValue = pir->toJson();
  if (publisher_motion.publish(motionValue.c_str())) {
    Serial.println("Published motion value");
  } else {
    Serial.println("Failed to publish motion value");
  }

  delay(1000);  // Publish every 5 seconds
}