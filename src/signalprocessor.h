#ifndef SIGNALPROCESSOR_H
#define SIGNALPROCESSOR_H

#define MAX_FIFO_SIZE 20

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "globals.h"

// function declarations
void sensor_data_average(void);
void fifoPush(int,int,int,float,int);

#endif