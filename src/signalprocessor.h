#ifndef SIGNALPROCESSOR_H
#define SIGNALPROCESSOR_H

#define SENSOR_SAMPLES 20

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "globals.h"

// function declarations
float average(int,int,int,float);

#endif