/*
R	    G	    B					                R	    G	    B	
128	    128	    0	    High CO2			        128	    128	    0	
128	    128	    128	    Valve cycling		        128	    128	    128	
128	    0	    0	    Night				        128	    0	    0	    No WIFI
128	    0	    128	    Manual				        128	    0	    128	    Fan high
0	    128	    0	    Cooking				        0	    128	    0	    Valves moving
0	    128	    128	    High RH				        0	    128	    128	    Fan medium
0	    0	    0	    -				            0	    0	    0	
0	    0	    128	    Day				            0	    0	    128	    Fan low
*/






#include "neopixel.h"

Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

void ws2812b_test(void) {

    Serial.print("\nRunning Neopixel function");

    for (int pixel=0; pixel < NUM_PIXELS; pixel++) {
        ws2812b.begin();
        ws2812b.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called

        // turn pixels to green one-by-one with delay between each pixel
        ws2812b.setPixelColor(pixel, ws2812b.Color(128, 0, 0));
        ws2812b.show();
        vTaskDelay(1000);

        // turn off all pixels for two seconds
        ws2812b.clear();
        ws2812b.show();  
        vTaskDelay(1000);

        // turn on all pixels to red at the same time for two seconds
        ws2812b.setPixelColor(pixel, ws2812b.Color(0, 128, 0));  // it only takes effect if pixels.show() is called
        ws2812b.show();  
        vTaskDelay(1000);

        // turn off all pixels for two seconds
        ws2812b.clear();
        ws2812b.show();  
        vTaskDelay(1000);

        // turn on all pixels to blue at the same time for two seconds
        ws2812b.setPixelColor(pixel, ws2812b.Color(0, 0, 128));  // it only takes effect if pixels.show() is called
        ws2812b.show();  
        vTaskDelay(1000);

        // turn off all pixels for one seconds
        ws2812b.clear();
        ws2812b.show();  // update to the WS2812B Led Strip
        
        vTaskDelay(3000);

    }

}
