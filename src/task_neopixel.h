#ifndef TASK_NEOPIXEL_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_NEOPIXEL_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "neopixel.h"
#include "globals.h"

// function declarations
void start_task_neopixel(void);
void task_neopixel_code(void *pvParameters);

#endif