#include "task_sensors.h"

TaskHandle_t task_sensors;

void start_task_sensors(void) {

    xTaskCreatePinnedToCore(task_sensors_code, "task_sensors", 10000, NULL, 1, &task_sensors, 1);

}

void task_sensors_code(void * pvParameters)
{
    for(;;) {
        Serial.print("\n\nSensors running on core: ");
        Serial.print(xPortGetCoreID());
        vTaskDelay(5000);
    }
  
}



