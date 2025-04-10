#ifndef SIGNALPROCESSOR_H
#define SIGNALPROCESSOR_H

#define MAX_FIFO_SIZE 20

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "globals.h"

// function declarations
void fifo_average(void);
void fifoPush(float);
float fifoAverage(void);

#endif