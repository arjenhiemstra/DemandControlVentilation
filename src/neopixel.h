#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#include "globals.h"
#include <Adafruit_NeoPixel.h>

#define PIN_WS2812B 42                      // The ESP32 pin GPIO10 connected to WS2812B
#define NUM_PIXELS 8                        // The number of LEDs (pixels) on WS2812B LED strip

//Function definitions
void ws2812b_test(void);

void led_red_on(int, int);
void led_green_on(int, int);
void led_blue_on(int, int);
void led_yellow_on(int, int);
void led_purple_on(int, int);
void led_white_on(int, int);

void led_red_blink(int, int);
void led_green_blink(int, int);
void led_blue_blink(int, int);
void led_yellow_blink(int, int);
void led_purple_blink(int, int);
void led_white_blink(int, int);

#endif
