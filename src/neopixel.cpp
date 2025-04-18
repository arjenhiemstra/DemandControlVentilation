/*
R	    G	    B					                R	    G	    B	
128	    128	    0	    High CO2			        128	    128	    0	    Statemachine not running
128	    128	    128	    Valve cycling		        128	    128	    128	
128	    0	    0	    Night				        128	    0	    0	    No WIFI
128	    0	    128	    Manual				        128	    0	    128	    Fan high
0	    128	    0	    Cooking				        0	    128	    0	    Valves moving
0	    128	    128	    High RH				        0	    128	    128	    Fan medium
0	    0	    0	    -				            0	    0	    0	
0	    0	    128	    Day				            0	    0	    128	    Fan low

calling ws2812b.clear() is not required

*/

#include "neopixel.h"

Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

void led_red_on(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(brightness, 0, 0));
    ws2812b.show();
    vTaskDelay(200);
}

void led_green_on(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(0, brightness, 0));
    ws2812b.show();
    vTaskDelay(200);
}

void led_blue_on(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(0, 0, brightness));
    ws2812b.show();
    vTaskDelay(200);
}

void led_yellow_on(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(brightness, brightness, 0));
    ws2812b.show();
    vTaskDelay(200);
}

void led_purple_on(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(brightness, 0, brightness));
    ws2812b.show();
    vTaskDelay(200);
}

void led_white_on(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(brightness, brightness, brightness));
    ws2812b.show();
    vTaskDelay(200);
}

void led_red_blink(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(brightness, 0, 0));
    ws2812b.show();
    vTaskDelay(200);
    ws2812b.setPixelColor(pixel, ws2812b.Color(0, 0, 0));
    ws2812b.show();  
    vTaskDelay(200);
}

void led_green_blink(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(0, brightness, 0));
    ws2812b.show();
    vTaskDelay(200);
    ws2812b.setPixelColor(pixel, ws2812b.Color(0, 0, 0));
    ws2812b.show();  
    vTaskDelay(200);
}

void led_blue_blink(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(0, 0, brightness));
    ws2812b.show();
    vTaskDelay(200);
    ws2812b.setPixelColor(pixel, ws2812b.Color(0, 0, 0));
    ws2812b.show();  
    vTaskDelay(200);
}

void led_yellow_blink(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(brightness, brightness, 0));
    ws2812b.show();
    vTaskDelay(200);
    ws2812b.setPixelColor(pixel, ws2812b.Color(0, 0, 0));
    ws2812b.show();  
    vTaskDelay(200);
}

void led_purple_blink(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(brightness, 0, brightness));
    ws2812b.show();
    vTaskDelay(200);
    ws2812b.setPixelColor(pixel, ws2812b.Color(0, 0, 0));
    ws2812b.show();  
    vTaskDelay(200);
}

void led_white_blink(int pixel, int brightness) {
    ws2812b.begin();
    ws2812b.setPixelColor(pixel, ws2812b.Color(brightness, brightness, brightness));
    ws2812b.show();
    vTaskDelay(200);
    ws2812b.setPixelColor(pixel, ws2812b.Color(0, 0, 0));
    ws2812b.show();  
    vTaskDelay(200);
}
