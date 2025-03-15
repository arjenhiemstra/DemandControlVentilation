#ifndef INFLUXDB_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define INFLUXDB_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <InfluxDbClient.h>

#include "globals.h"
#include "config_files.h"

#define INFLUXDB_URL "http://192.168.0.14:8086"
#define INFLUXDB_TOKEN "Z5AXzctdQG4lLoQXryfDsbBXXRlaw3DoVTmalzvEJBCJwyn3RBLPz5uIMNOJUOA6E_zFB4gMcwuvRG7zN3Vjdw=="
#define INFLUXDB_ORG "Lourens"
#define INFLUXDB_BUCKET "OSVentilationC"

// function declarations
void write_sensor_data(void);
void write_valve_position_data(void);
void write_system_uptime(void);
void write_state_info(void);
void write_fanspeed(void);

#endif