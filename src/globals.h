#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <ArduinoJson.h>

//Wire I/O settings (SDA1/SCL1) and Wire1 I/O settings
#define I2C_SCL1 38
#define I2C_SDA1 39
#define I2C_SCL2 40
#define I2C_SDA2 41

//LCD display
#define LCD_ROWS 4
#define LCD_COLUMNS 16
#define LCDADDR 0x27

//TCA9548 address
#define TCAADDR 0x70

//MQTT
extern const char* mqtt_server;
extern const char* mqtt_port;

//Mutexes
extern SemaphoreHandle_t sensor_config_file_mutex;
extern SemaphoreHandle_t sensor_variable_mutex;
extern SemaphoreHandle_t valve_position_mutex;

//Global for valve control data
extern JsonDocument valve_control_data;

//Define globals for sensor configuration
extern JsonDocument wire_sensor_data;
extern JsonDocument wire1_sensor_data;

extern String wire_sensor_config1_string;
extern String sensor_config2_string;

//Sensor data arrays for Wire and Wire1
extern float sensor_data[2][8][3];

extern String wire_sensor_config_string;
extern String wire1_sensor_config_string;

//Settings for MQTT
extern const char* mqtt_server;
extern const char* mqtt_port;

//Settings for RTC
extern const char* ntp_server;
extern const long gmt_offset_sec;
extern const int daylight_offset_sec;

//Function definitions

#endif