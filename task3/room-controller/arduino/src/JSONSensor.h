#ifndef __JSONSENSOR_H__
#define __JSONSENSOR_H__

#include "ArduinoJson.h"
#include "Arduino.h"

template <typename T>
class JSONSensor {
private:
    String _name;

protected:
    String getJson(T measure) {
        DynamicJsonDocument doc(JSON_OBJECT_SIZE(4));
        doc["name"] = _name;
        doc["measure"] = measure;
      
        String json;
        serializeJson(doc, json);
        return json;
    }

public:
    JSONSensor(const char* name) : _name(name) {}
};

#endif
