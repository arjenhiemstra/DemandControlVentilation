#include "task_mqtt.h"

TaskHandle_t task_mqtt;

void start_task_mqtt(void) {

    xTaskCreate(task_mqtt_code, "taskMQTT", 10000, NULL, 2, &task_mqtt);

}

void task_mqtt_code(void * pvParameters) {
    
    for(;;) {
        
        bool ap_active_temp=0;
        
        if (ap_active_mutex != NULL) {
            if(xSemaphoreTake(ap_active_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                ap_active_temp = ap_active;
                xSemaphoreGive(ap_active_mutex);
            }
        }
        
        if (WiFi.waitForConnectResult() == WL_CONNECTED && ap_active_temp == 0) {
            Serial.print("\nUpdate MQTT....");
            publish_sensor_data();
            publish_avg_sensor_data();
            publish_valve_positions();
            publish_uptime();
            publish_state();
            publish_fanspeed();
            Serial.print("\nMQTT update done");
            //vTaskDelay(20000);
        }
        vTaskDelay(20000);
    }
}