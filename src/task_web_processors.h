#ifndef TASK_WEB_PROCESSORS_H
#define TAKS_WEB_PROCESSORS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

//Function definitions
String valvecontrol_processor(const String&);
String sensor_config_processor(const String&);

#endif