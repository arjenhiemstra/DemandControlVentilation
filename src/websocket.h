#pragma once

#include <Arduino.h>

#include <string.h>
#include <unordered_map>

#include "notifyClients.h"
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "config_files.h"
#include "globals.h"

// #include "LittleFS.h"

void websocketInit();
void jsonWsSend(const char *rootName);
