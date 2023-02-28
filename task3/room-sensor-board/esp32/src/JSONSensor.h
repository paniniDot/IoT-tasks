#ifndef __JSONSENSOR_H__
#define __JSONSENSOR_H__
#include "ArduinoJson.h"
#include <ctime>
#include "Arduino.h"

template <typename T>

class JSONSensor {
    private:
        String _name;
    public:
        JSONSensor(const char* name) : _name(name) {};
        String getJson(T measure) {
            DynamicJsonDocument doc(JSON_OBJECT_SIZE(4));
            doc["name"] = _name;
            doc["measure"] = measure;
            doc["timestamp"] = std::time(nullptr);
            //to test print it to serial
            //serializeJson(doc, Serial);
            String json;
            serializeJson(doc, json);
            return json; 
        }
};

#endif