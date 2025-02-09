#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>

#include "globals.h"
#include "config_files.h"
#include "LiquidCrystal_I2C.h"          //Not library version but adjusted for using Wire1

//Function definitions
void display_sensors(void);
void display_valve_positions(void);
void display_time_and_date(void);

#endif