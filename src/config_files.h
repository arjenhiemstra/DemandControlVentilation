#ifndef CONFIG_FILES_H
#define CONFIG_FILES_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

//Function definitions
void valve_status_file_create(void);
void valve_status_file_delete(const char*);
bool check_valve_position_file_exists(void);
bool verify_valve_position_file_contents(void);
void write_new_valve_positions_to_file(void);

#endif