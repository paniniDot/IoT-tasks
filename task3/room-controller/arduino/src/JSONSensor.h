#ifndef __JSONSENSOR_H__
#define __JSONSENSOR_H__

#include "ArduinoJson.h"
#include "Arduino.h"

template <typename T>
class JSONSensor {
private:
    String _name;
    StaticJsonDocument<JSON_OBJECT_SIZE(3)> doc;

protected:
    String getJson(T measure) {
        doc["name"] = _name;
        doc["measure"] = measure;
        String json;
        serializeJson(doc, json);
        doc.clear();
        return json;
    }

public:
    JSONSensor(const char* name) : _name(name) {}
};

#endif
