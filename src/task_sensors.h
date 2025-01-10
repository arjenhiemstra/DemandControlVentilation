#ifndef TASK_SENSORS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_SENSORS_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void start_task_sensors(void);
void task_sensors_code(void *pvParameters);

#endif