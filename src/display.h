#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "globals.h"

#define LCDADDR 0x70

//Function definitions
void display(void);

#endif