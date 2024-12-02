#ifndef TASK2_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK2_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void startTask2code(void);
void Task2code(void *pvParameters);

#endif