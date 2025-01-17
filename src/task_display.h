#ifndef TASK_DISPLAY_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_DISPLAY_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "display.h"

// function declarations
void start_task_display(void);
void task_display_code(void *pvParameters);

#endif