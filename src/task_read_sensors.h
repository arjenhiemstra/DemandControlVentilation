#ifndef TASK_READ_SENSORS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_READ_SENSORS_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "read_sensors.h"

// function declarations
void start_task_read_sensors(void);
void task_read_sensors_code(void *pvParameters);

#endif