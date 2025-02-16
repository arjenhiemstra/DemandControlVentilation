#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <LittleFS.h>

#include "task_valvecontrol.h"
#include "task_web.h"
#include "task_read_sensors.h"
#include "task_display.h"
#include "task_mqtt.h"
#include "task_statemachine.h"
#include "rtc.h"

#include "valvecontrol.h"
#include "globals.h"

// function declarations
void setup_wifi(void);
void init_registers(void);

#endif
