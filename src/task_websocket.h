#ifndef TASK_WEBSOCKET_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_WEBSOCKET_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <MycilaWebSerial.h>

//Other includes
#include "globals.h"
#include "general.h"

// function declarations
void start_task_websocket(void);
void task_websocket_code(void * pvParameters);

#endif