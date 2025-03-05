#include "task_mqtt.h"

TaskHandle_t task_mqtt;

void start_task_mqtt(void) {

    xTaskCreate(task_mqtt_code, "taskMQTT", 10000, NULL, 2, &task_mqtt);

}

void task_mqtt_code(void * pvParameters)
{
    for(;;) {
        Serial.println("\nUpdate MQTT....");
        publish_sensor_data();
        //publish_valve_positions();
        publish_uptime();
        //publish_queues();
        //publish_state();
        Serial.println("MQTT update done");
        vTaskDelay(20000);
    }
  
}