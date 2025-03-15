#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <WiFi.h>

#include "globals.h"
#include "config_files.h"
#include "PubSubClient.h"
#include "uptime_formatter.h"
//#include <uptime.h>

//Function definitions
void publish_sensor_data(void);
void publish_valve_positions(void);
void publish_uptime(void);
void publish_fanspeed(void);
void publish_state(void);
void publish_queues(void);
void subscribe(void);

#endif