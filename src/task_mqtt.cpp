#include "task_mqtt.h"

TaskHandle_t task_mqtt;

void start_task_mqtt(void) {

    xTaskCreatePinnedToCore(task_mqtt_code, "taskMQTT", 10000, NULL, 1, &task_mqtt, 0);

}

void task_mqtt_code(void * pvParameters)
{
    for(;;) {
        Serial.println("\n\nUpdate MQTT....");
        publish_sensor_data();
        publish_valve_positions();
        publish_uptime();
        publish_state();
        Serial.println("MQTT update done");
        vTaskDelay(20000);
    }
  
}