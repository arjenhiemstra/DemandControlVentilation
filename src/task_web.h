#ifndef TASK_WEB_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TASK_WEB_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <LittleFS.h>

void startTaskwebcode(void);
void Taskwebcode(void *pvParameters);
//void notFound(AsyncWebServerRequest *request)

#endif

