#ifndef TASK_ESPNOW_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_ESPNOW_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "globals.h"

// function declarations
void start_task_espnow(void);
void task_espnow_code(void *pvParameters);

#endif