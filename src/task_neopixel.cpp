#include "task_neopixel.h"

TaskHandle_t task_np;

void start_task_neopixel(void) {

    xTaskCreate(task_neopixel_code, "tasknp", 30000, NULL, 6, &task_np);

}

void task_neopixel_code(void * pvParameters) {

    for(;;) {
        ws2812b_test();
    }

}  