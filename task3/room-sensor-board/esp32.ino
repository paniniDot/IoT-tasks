#include <WiFi.h>
#include <PubSubClient.h>

//define wifi
const char* ssid = "nome_wifi";
const char* password = "pass";

//forse la room service
const char* mqtt_server = "broker";

//define topics 
const char* topic_light = "esp32/light";
const char* topic_motion = "esp32/motion";

//initialize this client
PubSubClient publisher(new WiFiClient());

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  publisher.setServer(mqtt_server, 1883);

  while (!publisher.connected()) {
    if (publisher.connect("ESP32_room_sensor_board")) {
      Serial.println("Connected to MQTT broker succesfully!");
    } else {
      delay(5000);
    }
  }

}

void loop() {
  publisher.publish(topic_light, topic_light);
  publisher.publish(topic_motion, topic_motion);

  delay(5000);
}