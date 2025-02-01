#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <ArduinoJson.h>

extern SemaphoreHandle_t sensor_config_file_mutex;

//Global for valve control data
extern JsonDocument valve_control_data;

//Define globals for sensor configuration
extern JsonDocument wire_sensor_data;
extern JsonDocument wire1_sensor_data;

//Make array of sensors inside JsonDocument for each sensor
/*
extern JsonArray wire_sensors;
extern JsonObject wire_sensors0;
extern JsonObject wire_sensors1;
extern JsonObject wire_sensors2;
extern JsonObject wire_sensors3;
extern JsonObject wire_sensors4;
extern JsonObject wire_sensors5;
extern JsonObject wire_sensors6;
extern JsonObject wire_sensors7;

extern JsonArray wire1_sensors;
extern JsonObject wire1_sensors0;
extern JsonObject wire1_sensors1;
extern JsonObject wire1_sensors2;
extern JsonObject wire1_sensors3;
extern JsonObject wire1_sensors4;
extern JsonObject wire1_sensors5;
extern JsonObject wire1_sensors6;
extern JsonObject wire1_sensors7;
*/

extern String wire_sensor_config1_string;
extern String sensor_config2_string;

//Sensor data arrays for Wire and Wire1
extern float sensor1_data[8][3];
extern float sensor2_data[8][3];

extern String wire_sensor_config_string;
extern String wire1_sensor_config_string;


//Function definitions

#endif