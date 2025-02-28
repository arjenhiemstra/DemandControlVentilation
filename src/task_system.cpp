#include "task_system.h"

TaskHandle_t task_sys;

void start_task_system(void) {

    xTaskCreate(task_system_code, "taskSystem", 10000, NULL, 1, &task_sys);

}

void task_system_code(void * pvParameters)
{
    for(;;) {
        task_list();
        vTaskDelay(30000);
    }
  
}