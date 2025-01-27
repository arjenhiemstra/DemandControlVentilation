#ifndef CONFIG_FILES_H
#define CONFIG_FILES_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

//#include "globals.h"

//Function definitions
void valve_status_file_create(void);
void delete_file(const char*);
bool check_file_exists(const char*);
String read_config_file(const char*);
bool verify_valve_position_file_contents(void);
void write_config_file(const char*, String);
void sensor_config_data_read(void);

#endif