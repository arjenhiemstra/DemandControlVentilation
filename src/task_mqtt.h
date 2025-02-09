#ifndef TASK_MQTT_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_MQTT_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "mqtt.h"

// function declarations
void start_task_mqtt(void);
void task_mqtt_code(void * pvParameters);


#endif