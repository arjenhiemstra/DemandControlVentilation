#include "globals.h"

//Global for valve control data
JsonDocument valve_control_data;

//Define globals for sensor configuration
JsonDocument wire_sensor_data;
JsonDocument wire1_sensor_data;

//Make array of sensors inside JsonDocument for each sensor
JsonArray wire_sensors = wire_sensor_data["wire_sensors"].to<JsonArray>();
JsonObject wire_sensors0 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors1 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors2 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors3 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors4 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors5 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors6 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors7 = wire_sensors.add<JsonObject>();

JsonArray wire1_sensors = wire1_sensor_data["wire1_sensors"].to<JsonArray>();
JsonObject wire1_sensors0 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors1 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors2 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors3 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors4 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors5 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors6 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors7 = wire1_sensors.add<JsonObject>();