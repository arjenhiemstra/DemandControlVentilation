#include "task_read_sensors.h"

TaskHandle_t task_read_sensors;

void start_task_read_sensors(void) {

    xTaskCreate(task_read_sensors_code, "taskReadSensors", 30000, NULL, 6, &task_read_sensors);

}

void task_read_sensors_code(void * pvParameters)
{
    for(;;) {
        read_sensors();
        vTaskDelay(5000);
    }
  
}



