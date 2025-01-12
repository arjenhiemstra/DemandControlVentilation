#ifndef SENSORS_H
#define SENSORS_H

#include <Wire.h>
#include <Arduino.h>
#include <DHT.h>
#include <SparkFun_SCD4x_Arduino_Library.h>

#define I2C_SCL1 38
#define I2C_SDA1 39
#define I2C_SCL2 40
#define I2C_SDA2 41

//Function definitions
void read_DHT22(void);
void read_SCD41(void);
void TCA9548A(uint8_t);

#endif
