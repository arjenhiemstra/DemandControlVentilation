#include "globals.h"

SemaphoreHandle_t sensor_config_file_mutex = NULL;              // Sensor configuration files
SemaphoreHandle_t valve_position_file_mutex = NULL;             // Valve position file
SemaphoreHandle_t valve_control_data_mutex = NULL;              // Valve control data variable
SemaphoreHandle_t date_time_mutex = NULL;                       // Time variables
SemaphoreHandle_t settings_network_mutex = NULL;                // Network settings
SemaphoreHandle_t settings_mqtt_mutex = NULL;                   // MQTT settings
SemaphoreHandle_t settings_i2c_mutex = NULL;                    // I2C settings
SemaphoreHandle_t settings_fan_mutex = NULL;                    // Fan control settings
SemaphoreHandle_t settings_statemachine_mutex = NULL;           // Statemachine settings
SemaphoreHandle_t statemachine_state_mutex = NULL;              // for state of statemechine
SemaphoreHandle_t fanspeed_mutex = NULL;                        // for state of fan

SemaphoreHandle_t settings_state_day_mutex = NULL;              // Day state settings
SemaphoreHandle_t settings_state_night_mutex = NULL;            // Night state settings
SemaphoreHandle_t settings_state_highco2day_mutex = NULL;       // High CO2 day state settings
SemaphoreHandle_t settings_state_highco2night_mutex = NULL;     // High CO2 Night settings
SemaphoreHandle_t settings_state_highrhday_mutex = NULL;        // High RH day state settings
SemaphoreHandle_t settings_state_highrhnight_mutex = NULL;      // High RH night state settings
SemaphoreHandle_t settings_state_cooking_mutex = NULL;          // Cooking state settings 
SemaphoreHandle_t settings_state_cyclingday_mutex = NULL;       // Valve cycle day state settings
SemaphoreHandle_t settings_state_cyclingnight_mutex = NULL;     // Valve cycle night state settings

QueueHandle_t sensor_queue;                                     // Handle for sensor queue data

JsonDocument valve_control_data;                                // Global for valve control data

JsonDocument wire_sensor_data;                                  // Global for bus0 sensor configuration
JsonDocument wire1_sensor_data;                                 // Global for bus1 sensor configuration

JsonDocument settings_network_data;                             // Define global network settings
JsonDocument settings_mqtt_data;                                // Define global mqtt settings
JsonDocument settings_i2c_data;                                 // Define global i2c settings
JsonDocument settings_fan_data;                                 // Define global fanspeed settings
JsonDocument settings_statemachine_data;                        // Define global statemachine settings

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

