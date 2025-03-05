#include "task_display.h"

TaskHandle_t task_display;

void start_task_display(void) {

    xTaskCreate(task_display_code, "taskDisplay", 10000, NULL, 1, &task_display);

}

void task_display_code(void * pvParameters)
{
    for(;;) {
        //display_time_and_date();
        //display_sensors();
        //display_valve_positions();
        vTaskDelay(15000);
    }
  
}