#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <ArduinoJson.h>

extern SemaphoreHandle_t sensor_config_file_mutex;
extern SemaphoreHandle_t sensor_variable_mutex;

//Global for valve control data
extern JsonDocument valve_control_data;

//Define globals for sensor configuration
extern JsonDocument wire_sensor_data;
extern JsonDocument wire1_sensor_data;

extern String wire_sensor_config1_string;
extern String sensor_config2_string;

//Sensor data arrays for Wire and Wire1
extern float sensor1_data[8][3];
extern float sensor2_data[8][3];

extern String wire_sensor_config_string;
extern String wire1_sensor_config_string;

//Function definitions

#endif