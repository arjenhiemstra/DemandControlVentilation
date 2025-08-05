#pragma once

#include <cstdio>
#include <string>

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
extern AsyncWebSocket ws;

// extern AsyncWebSocket ws;
extern SemaphoreHandle_t mutexWSsend;

extern size_t content_len;

void notifyClients(const char* message);
void notifyClients(JsonObject obj);
void wsSendAll(void* arg, const char* message);
