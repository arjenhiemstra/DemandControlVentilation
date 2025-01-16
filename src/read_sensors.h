#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <DHT.h>
#include <SparkFun_SCD4x_Arduino_Library.h>

#define I2C_SCL1 38
#define I2C_SDA1 39
#define I2C_SCL2 40
#define I2C_SDA2 41

#define TCAADDR 0x70;  //TCA9548 address

//Function definitions
void read_bus0(void);
void read_bus1(void);
//void read_DHT22(void);
void read_SCD41(void);
//void TCA9548A(char*, uint8_t);

#endif
