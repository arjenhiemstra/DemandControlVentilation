#include "task_influxdb.h"

TaskHandle_t task_influxdb;

void start_task_influxdb(void) {

    xTaskCreate(task_influxdb_code, "task_influxdb", 10000, NULL, 3, &task_influxdb);
}

void task_influxdb_code(void * pvParameters)
{
    for(;;) {
        vTaskDelay(30000);
        write_sensor_data();
        //write_avg_sensor_data();
        write_valve_position_data();
        write_system_uptime();
        write_state_info();
        write_fanspeed();
    } 
}