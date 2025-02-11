#ifndef TASK_STATEMACHINE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_STATEMACHINE_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "statemachine.h"
#include "rtc.h"
//#include "uptime_formatter.h"

// function declarations
void start_task_statemachine(void);
void task_statemachine_code(void *pvParameters);

#endif