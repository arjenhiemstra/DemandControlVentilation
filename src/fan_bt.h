#ifndef FAN_BT_H
#define FAN_BT_H

#include <Arduino.h>
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "BluetoothSerial.h"

#include "globals.h"

// function declarations
void set_fanspeed(void);

#endif