#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#include "globals.h"
#include <Adafruit_NeoPixel.h>

#define PIN_WS2812B 10                      // The ESP32 pin GPIO10 connected to WS2812B
#define NUM_PIXELS 8                        // The number of LEDs (pixels) on WS2812B LED strip

//Function definitions
void ws2812b_test(void);
void led1_day_time(void);

#endif
