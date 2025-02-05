#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "globals.h"
#include "config_files.h"

#define LCDADDR 0x27

//Function definitions
void display_sensors(void);
void display_valve_positions(void);

#endif