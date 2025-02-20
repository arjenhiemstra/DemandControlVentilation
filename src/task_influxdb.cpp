#include "task_influxdb.h"

TaskHandle_t task_influxdb;

void start_task_influxdb(void) {

    xTaskCreatePinnedToCore(task_influxdb_code, "task_influxdb", 10000, NULL, 1, &task_influxdb, 1);
}

void task_influxdb_code(void * pvParameters)
{
    for(;;) {
        write_sensor_data();
        write_valve_position_data();
        vTaskDelay(30000);
    }
  
}