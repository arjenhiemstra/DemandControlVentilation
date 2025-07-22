#ifndef TASK_INFLUXDB_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_INFLUXDB_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <WiFi.h>

#include "influxdb.h"
#include "general.h"

// function declarations
void start_task_influxdb(void);
void task_influxdb_code(void *pvParameters);

#endif