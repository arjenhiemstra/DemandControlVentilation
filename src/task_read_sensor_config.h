#ifndef TASK_READ_SENSOR_CONFIG_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_READ_SENSOR_CONFIG_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "config_files.h"

// function declarations
void start_task_read_sensor_config(void);
void task_read_sensor_config_code(void *pvParameters);

#endif