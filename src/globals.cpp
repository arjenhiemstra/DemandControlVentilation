#include "globals.h"

SemaphoreHandle_t sensor_config_file_mutex = NULL;          // For sensor configuration files
SemaphoreHandle_t valve_position_file_mutex = NULL;         // For valve position file
SemaphoreHandle_t valve_control_data_mutex = NULL;          // For valve control data variable
SemaphoreHandle_t date_time_mutex = NULL;                   // For time variables
SemaphoreHandle_t settings_network_mutex = NULL;            // For netowrk settings
SemaphoreHandle_t settings_mqtt_mutex = NULL;
SemaphoreHandle_t settings_i2c_mutex = NULL;
SemaphoreHandle_t settings_fan_mutex = NULL;
SemaphoreHandle_t settings_statemachine_mutex = NULL;
SemaphoreHandle_t statemachine_state_mutex = NULL;          // for state of statemechine
SemaphoreHandle_t fanspeed_mutex = NULL;                    // for state of fan

SemaphoreHandle_t settings_state_day_mutex = NULL;
SemaphoreHandle_t settings_state_night_mutex = NULL;
SemaphoreHandle_t settings_state_highco2day_mutex = NULL;
SemaphoreHandle_t settings_state_highco2night_mutex = NULL;
SemaphoreHandle_t settings_state_highrhday_mutex = NULL;
SemaphoreHandle_t settings_state_highrhnight_mutex = NULL;
SemaphoreHandle_t settings_state_cooking_mutex = NULL;
SemaphoreHandle_t settings_state_cyclingday_mutex = NULL;
SemaphoreHandle_t settings_state_cyclingnight_mutex = NULL;

QueueHandle_t sensor_queue;

//Global for valve control data
JsonDocument valve_control_data;

//Define globals for sensor configuration
JsonDocument wire_sensor_data;
JsonDocument wire1_sensor_data;

//Define lobal for settings configuration
JsonDocument settings_network_data;
JsonDocument settings_mqtt_data;
JsonDocument settings_i2c_data;
JsonDocument settings_fan_data;
JsonDocument settings_statemachine_data;

//Define globals for valve settings per state
JsonDocument settings_state_day;
JsonDocument settings_state_night;
JsonDocument settings_state_highco2day;
JsonDocument settings_state_highco2night;
JsonDocument settings_state_highrhday;
JsonDocument settings_state_highrhnight;
JsonDocument settings_state_cooking;
JsonDocument settings_state_cyclingday;
JsonDocument settings_state_cyclingnight;


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
String fanspeed = "";

