#include <WiFi.h>
#include "src/PubSubClient.h"
#include "src/Pir.h"
#include "src/PhotoResistor.h"
#include <esp_system.h>

/* wifi network info */

const char* ssid = "Tenda_A2E5A8";
const char* password = NULL;

/* MQTT server address */
const char* mqtt_server = "broker.mqtt-dashboard.com";

//define topics 
const char* topic_light = "esp32/light";
const char* topic_motion = "esp32/motion";

//define hardware 
PhotoResistor* resistor = new PhotoResistor(4);
Pir* pir = new Pir(5);


/* MQTT client management */

WiFiClient espClient;
PubSubClient publisher(espClient);

void setup_wifi() {

  delay(10);

  Serial.println(String("Connecting to ") + ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  
  // Loop until we're reconnected
  
  while (!publisher.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Attempt to connect
    if (publisher.connect("ESP32 room sensor board")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(publisher.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print("LOOL");
  setup_wifi();
  publisher.setServer(mqtt_server, 1883);
}

void loop() {

  if (!publisher.connected()) {
    reconnect();
  }

  publisher.loop();

  /* publishing the msg */
  publisher.publish(topic_light, resistor->toJson().c_str());
  publisher.publish(topic_motion, pir->toJson().c_str());  

  Serial.println(pir->toJson());
  Serial.println(resistor->toJson());
  delay(1000);
}
