#ifndef TASK1_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK1_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// function declarations
void startTask1code(void);
void Task1code(void *pvParameters);

#endif