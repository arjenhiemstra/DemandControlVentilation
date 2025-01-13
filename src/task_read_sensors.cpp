#include "task_read_sensors.h"

TaskHandle_t task_read_sensors;

void start_task_read_sensors(void) {

    xTaskCreatePinnedToCore(task_read_sensors_code, "taskReadSensors", 10000, NULL, 1, &task_read_sensors, 1);

}

void task_read_sensors_code(void * pvParameters)
{
    for(;;) {
        Serial.print("\n\nSensors running on core: ");
        Serial.print(xPortGetCoreID());
        
        vTaskDelay(5000);
    }
  
}



