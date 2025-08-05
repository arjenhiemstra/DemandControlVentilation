#ifndef TASK_WEB_H // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_WEB_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#include "valvecontrol.h"
#include "config_files.h"
#include "task_web_processors.h"
#include "globals.h"
#include "general.h"
#include "websocket.h"

// function declarations
void startTaskwebcode(void);
void Taskwebcode(void *pvParameters);

#endif
