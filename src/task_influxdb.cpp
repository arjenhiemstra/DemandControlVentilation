#include "task_influxdb.h"

void start_task_influxdb(void) {

    xTaskCreate(task_influxdb_code, "task_influxdb", 10000, NULL, 3, &task_influxdb);
}

void task_influxdb_code(void * pvParameters)
{
    for(;;) {
        
        bool ap_active_temp=0;
        
        String enable_influxdb_tmp;
        
        vTaskDelay(10000);
        
        if (ap_active_mutex != NULL) {
            if(xSemaphoreTake(ap_active_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                ap_active_temp = ap_active;
                xSemaphoreGive(ap_active_mutex);
            }
        }

        if (settings_influxdb_mutex != NULL) {
            if(xSemaphoreTake(settings_influxdb_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                enable_influxdb_tmp = enable_influxdb;
                xSemaphoreGive(settings_influxdb_mutex);
            }
        }
        
        //Serial.print("\nEnable Influxdb: ");
        //Serial.print(enable_influxdb_tmp);

        if (WiFi.waitForConnectResult() == WL_CONNECTED && ap_active_temp == 0 && enable_influxdb_tmp == "On") {
            write_sensor_data();
            write_avg_sensor_data();
            write_valve_position_data();
            write_system_uptime();
            write_state_info();
            write_fanspeed();
            write_heap_info();
        }
    } 
}