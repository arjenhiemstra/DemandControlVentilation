#include "globals.h"

SemaphoreHandle_t sensor_config_file_mutex = NULL;

//Global for valve control data
JsonDocument valve_control_data;

//Define globals for sensor configuration
JsonDocument wire_sensor_data;
JsonDocument wire1_sensor_data;

/*
JsonObject wire_sensor0 = wire_sensor_data.add<JsonObject>();
JsonObject wire_sensor1 = wire_sensor_data.add<JsonObject>();
JsonObject wire_sensor2 = wire_sensor_data.add<JsonObject>();
JsonObject wire_sensor3 = wire_sensor_data.add<JsonObject>();
JsonObject wire_sensor4 = wire_sensor_data.add<JsonObject>();
JsonObject wire_sensor5 = wire_sensor_data.add<JsonObject>();
JsonObject wire_sensor6 = wire_sensor_data.add<JsonObject>();
JsonObject wire_sensor7 = wire_sensor_data.add<JsonObject>();

JsonObject wire1_sensor0 = wire1_sensor_data.add<JsonObject>();
JsonObject wire1_sensor1 = wire1_sensor_data.add<JsonObject>();
JsonObject wire1_sensor2 = wire1_sensor_data.add<JsonObject>();
JsonObject wire1_sensor3 = wire1_sensor_data.add<JsonObject>();
JsonObject wire1_sensor4 = wire1_sensor_data.add<JsonObject>();
JsonObject wire1_sensor5 = wire1_sensor_data.add<JsonObject>();
JsonObject wire1_sensor6 = wire1_sensor_data.add<JsonObject>();
JsonObject wire1_sensor7 = wire1_sensor_data.add<JsonObject>();
*/

//Sensor data arrays for Wire and Wire1
float sensor1_data[8][3] = { 0 };
float sensor2_data[8][3] = { 0 };

String wire_sensor_config_string = {};
String wire1_sensor_config_string = {};

/*struct wire_sensors_data {
    int sensor_id;
    String type;
    String addresss;
    int valve;
    String location;
    bool rh;
    bool co2;
};

struct wire1_sensors_data {
    int sensor_id;
    String type;
    String addresss;
    int valve;
    String location;
    bool rh;
    bool co2;
};*/

