#ifndef INFLUXDB_H
#define INFLUXDB_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <InfluxDbClient.h>
#include <ArduinoJson.h>

#include "globals.h"
#include "config_files.h"
#include "general.h"

// function declarations
void write_sensor_data(void);
void write_avg_sensor_data(void);
void write_valve_position_data(void);
void write_system_uptime(void);
void write_state_info(void);
void write_fanspeed(void);
void write_heap_info(void);

#endif