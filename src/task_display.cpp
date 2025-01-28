#include "task_display.h"

TaskHandle_t task_display;

void start_task_display(void) {

    xTaskCreatePinnedToCore(task_display_code, "taskDisplay", 10000, NULL, 1, &task_display, 1);

}

void task_display_code(void * pvParameters)
{
    for(;;) {
        //Serial.print("\n\nDisplay running on core: ");
        //Serial.print(xPortGetCoreID());
        //display();
        vTaskDelay(5000);
    }
  
}