#include "task_mqtt.h"

void start_task_mqtt(void) {

    xTaskCreate(task_mqtt_code, "taskMQTT", 10000, NULL, 2, &task_mqtt);

}

void task_mqtt_code(void * pvParameters) {
    
    for(;;) {
        
        bool ap_active_temp=0;
        int mqtt_port_tmp = 0;
        
        char txBuffer[200];
        int test = 1;

        String mqtt_enable_str;
        String mqtt_server_str;
        String mqtt_base_topic_str; 
        

        //Read basic connection settings for MQTT to check if MQTT connection can be made
        if (settings_mqtt_mutex != NULL) {
            if(xSemaphoreTake(settings_mqtt_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                mqtt_enable_str = enable_mqtt;
                mqtt_server_str = mqtt_server;
                mqtt_port_tmp = mqtt_port;
                mqtt_base_topic_str = mqtt_base_topic; 
                xSemaphoreGive(settings_mqtt_mutex);
            }
        }
        
        if (ap_active_mutex != NULL) {
            if(xSemaphoreTake(ap_active_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                ap_active_temp = ap_active;
                xSemaphoreGive(ap_active_mutex);
            }
        }

        //If MQTT connection settings are changed then re-read config file
        if(mqtt_server_str == "" || mqtt_port_tmp == 0) {
            //Serial.print("\nRead MQTT config file");
            read_mqtt_config();
        }
       
        /*
        Serial.print("\nMQTT connection settings:\t");
        Serial.print(mqtt_enable_str);
        Serial.print("\t");
        Serial.print(mqtt_server_str);
        Serial.print("\t");
        Serial.print(mqtt_port_tmp);
        Serial.print("\t");
        Serial.print(mqtt_base_topic_str);
        */

        //Check if MQTT functions can run
        if (WiFi.waitForConnectResult() == WL_CONNECTED && ap_active_temp == 0 && mqtt_enable_str == "On" && mqtt_server_str != "" && mqtt_port_tmp != 0) {
            Serial.print("\nUpdate MQTT....");
            
            //sprintf(txBuffer, "Update MQTT....");
            strcpy(txBuffer, "Update MQTT....");
            //if(webserial_queue != 0) {
                xQueueSend(webserial_queue, txBuffer, 10);
            //}
            Serial.print("\nNumber of messages in queue waiting: " + String(uxQueueMessagesWaiting(webserial_queue)));
            
            read_mqtt_config();
            publish_sensor_data();
            publish_avg_sensor_data();
            publish_valve_positions();
            publish_uptime();
            publish_state();
            publish_fanspeed();
            //Serial.print("\nMQTT update done");
        }
        else {
            Serial.print("\nNo WIFI connection, MQTT disabled or MQTT settings incomplete");
        }
        vTaskDelay(10000);
    }
}