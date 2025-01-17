#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <DHT.h>
#include <SparkFun_SCD4x_Arduino_Library.h>

#include "read_sensors.h"

//TCA9548 address
#define TCAADDR 0x70;  

//Function definitions
void display(void);

#endif