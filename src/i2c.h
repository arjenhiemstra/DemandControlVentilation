#ifndef I2C_H
#define I2C_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <DHT20.h>
#include <Adafruit_AHTX0.h>
#include <SensirionI2cScd4x.h>
#include <RTClib.h>

#include "globals.h"
#include "config_files.h"
#include "LiquidCrystal_I2C.h"          //Not library version but adjusted for using Wire1

//Function definitions
void read_sensors(void);
void display_sensors(void);
void display_valve_positions(void);
void display_time_and_date(void);
void sync_rtc_ntp(void);
void current_time(void);

#endif
