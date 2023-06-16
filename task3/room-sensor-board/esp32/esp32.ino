#include <WiFi.h>
#include "src/PubSubClient.h"
#include "src/Pir.h"
#include "src/PhotoResistor.h"
#include <esp_system.h>

/* wifi network info */
const char* ssid = "asus";
const char* password = "0123456789";
/* MQTT server address */
const char* mqtt_server = "broker.mqtt-dashboard.com";
//define topics 
const char* topic_light = "esp32/light";
const char* topic_motion = "esp32/motion";
//define hardware 
PhotoResistor* resistor;
Pir* pir;
/* MQTT client management */
WiFiClient espClient;
PubSubClient publisher(espClient);

void setup_wifi() {
  delay(100);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(" . ");
  }
  Serial.print(" WiFi connected ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  resistor = new PhotoResistor(4);
  pir = new Pir(34);
}

void reconnect() {
  while (!publisher.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (publisher.connect("ESP32 room sensor board")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(publisher.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);
  setup_wifi();
  publisher.setServer(mqtt_server, 1883);
}

void loop() {
  if (!publisher.connected()) {
    reconnect();
  }
  publisher.loop();
  publisher.publish(topic_light, resistor->toJson().c_str());
  publisher.publish(topic_motion, pir->toJson().c_str());  
  delay(1000);
}
