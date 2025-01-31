#include "task_read_sensor_config.h"

TaskHandle_t task_sensconf;

void start_task_read_sensor_config_code(void) {

    xTaskCreatePinnedToCore(task_read_sensor_config_code, "task_sensconf", 10000, NULL, 1, &task_sensconf, 0);

}

void task_read_sensor_config_code(void * pvParameters)
{
  for (;;) { 
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    Serial.print("\n\nReading config file");
    sensor_config_data_read();
  }
  
}

