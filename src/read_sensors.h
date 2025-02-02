#ifndef READ_SENSORS_H
#define READ_SENSORS_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <DHT20.h>
#include <Adafruit_AHTX0.h>
#include <SensirionI2cScd4x.h>

#include "globals.h"
#include "config_files.h"

#define I2C_SCL1 38
#define I2C_SDA1 39
#define I2C_SCL2 40
#define I2C_SDA2 41

//TCA9548 address
#define TCAADDR 0x70

//Function definitions
void read_bus0(void);
void read_bus1(void);
void display(void);

#endif
