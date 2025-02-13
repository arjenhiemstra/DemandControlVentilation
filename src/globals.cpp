#include "globals.h"

SemaphoreHandle_t sensor_config_file_mutex = NULL;
SemaphoreHandle_t sensor_variable_mutex = NULL;
SemaphoreHandle_t valve_position_mutex = NULL;
SemaphoreHandle_t date_time_mutex = NULL;
SemaphoreHandle_t settings_mutex = NULL;

//Global for valve control data
JsonDocument valve_control_data;

//Define globals for sensor configuration
JsonDocument wire_sensor_data;
JsonDocument wire1_sensor_data;

//Define lobal for settings configuration
JsonDocument settings_data;

//Sensor data arrays for Wire and Wire1
float sensor_data[2][8][3] = { 0 };

String wire_sensor_config_string = {};
String wire1_sensor_config_string = {};

//Settings for MQTT
const char* mqtt_server = "192.168.0.15";
const int mqtt_port = 1883;

//Settings for RTC
RTC_DS3231 rtc;
const char* ntp_server = "pool.ntp.org";
const long gmt_offset_sec = 3600;                // Offset for GMT in seconds, 3600 for Europe/Amsterdam
const int daylight_offset_sec = 3600;            // Daylight savings time in seconds, 3600 for Europe/Amsterdam

//Date time data from RTC
String yearStr = "";
String monthStr = "";
String dayStr = "";
String hourStr = "";
String minuteStr = "";
String secondStr = "";
String dayOfWeek = "";

//Statemachine globals
String state = "";

