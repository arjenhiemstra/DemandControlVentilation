#include "globals.h"

SemaphoreHandle_t sensor_config_file_mutex = NULL;
SemaphoreHandle_t sensor_variable_mutex = NULL;
SemaphoreHandle_t valve_position_mutex = NULL;

//Global for valve control data
JsonDocument valve_control_data;

//Define globals for sensor configuration
JsonDocument wire_sensor_data;
JsonDocument wire1_sensor_data;

//Sensor data arrays for Wire and Wire1
float sensor_data[2][8][3] = { 0 };

String wire_sensor_config_string = {};
String wire1_sensor_config_string = {};

const char* mqtt_server = "mqtt.lourens.cloud";
const char* mqtt_port = "1883";


