#ifndef CONFIG_FILES_H
#define CONFIG_FILES_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

//Function definitions
void valve_status_file_create(void);
void valve_status_file_delete(void);
bool check_valve_position_file_exists(void);

#endif