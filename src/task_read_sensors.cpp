#include "task_read_sensors.h"

TaskHandle_t task_read_sensors;

void start_task_read_sensors(void) {

    xTaskCreatePinnedToCore(task_read_sensors_code, "taskReadSensors", 20000, NULL, 5, &task_read_sensors, 0);

}

void task_read_sensors_code(void * pvParameters)
{
    for(;;) {
        //Serial.print("\n\nReading sensors: \n\n");
        //Serial.print(xPortGetCoreID());
        //read_bus0();
        //read_bus1();
        read_sensors();
        vTaskDelay(20000);
    }
  
}



