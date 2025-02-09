#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Ethernet.h>
#include <WiFi.h>

#include "globals.h"
#include "config_files.h"
#include "PubSubClient.h"

//Function definitions
void publish_sensor_data(void);
void publish_valve_data(void);
void publish_state(void)
void subscribe(void);

#endif