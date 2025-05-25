#include "mqtt.h"

WiFiClient OSventilation;
PubSubClient client(OSventilation);
   
void read_mqtt_config(void) {

    const char* path = "/json/settings_mqtt.json";
    String settings_mqtt_string = "";
    bool settings_mqtt_file_present = 0;
    JsonDocument settings_mqtt_doc;

    if (settings_mqtt_mutex != NULL) {
        if(xSemaphoreTake(settings_mqtt_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            settings_mqtt_file_present = check_file_exists(path);
            if (settings_mqtt_file_present == 1) {
                File file = LittleFS.open(path, "r");
                while(file.available()) {
                    settings_mqtt_string = file.readString();
                }
                file.close();
                deserializeJson(settings_mqtt_doc, settings_mqtt_string);
                
                //Assign to global variable
                enable_mqtt = settings_mqtt_doc[String("enable_mqtt")];
                mqtt_server = settings_mqtt_doc[String("mqtt_server")];
                mqtt_port = settings_mqtt_doc[String("mqtt_port")];
                mqtt_base_topic = settings_mqtt_doc[String("mqtt_base_topic")];
            }
            xSemaphoreGive(settings_mqtt_mutex);
        }
    }
}


void publish_sensor_data(void) {

    String measurement;
    char topic[200];
    char sensor_value[8];
    float queue_sensor_data[2][8][3];

    Serial.print("\nPublish sensor data.");
    if (xQueuePeek(sensor_queue, &queue_sensor_data, 0 ) == pdTRUE) {  
       
        client.setServer(mqtt_server, mqtt_port);

        if (client.connect("OSventilation")) {
            for (int bus=0;bus<2;bus++) {
                for (int slot=0;slot<8;slot++) {
                            
                    if (queue_sensor_data[bus][slot][0] > 2 )  {
                        measurement = "/temperature";
                        ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + measurement).toCharArray(topic,200);
                        String(queue_sensor_data[bus][slot][0]).toCharArray(sensor_value,8);
                        client.publish(topic, sensor_value);
                    }

                    if (queue_sensor_data[bus][slot][1] > 2 )  {
                        measurement = "/humidity";
                        ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + measurement).toCharArray(topic,200);
                        String(queue_sensor_data[bus][slot][1]).toCharArray(sensor_value,8);
                        client.publish(topic, sensor_value);
                    }

                    if (queue_sensor_data[bus][slot][2] > 2 )  {
                        measurement = "/CO2";
                        ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + measurement).toCharArray(topic,200);
                        String(queue_sensor_data[bus][slot][2]).toCharArray(sensor_value,8);
                        client.publish(topic, sensor_value);
                    }
                }
            }
        }
        else {
            Serial.print("Could not connect to MQTT server");
        }
    }
}

void publish_avg_sensor_data(void) {

    String measurement;
    char topic[200];
    char sensor_avg_value[8];
    float queue_sensor_avg_data[2][8][3];

    Serial.print("\nPublish sensor data.");
    if (xQueuePeek(sensor_avg_queue, &queue_sensor_avg_data, 0 ) == pdTRUE) {  
       
        client.setServer(mqtt_server, mqtt_port);

        if (client.connect("OSventilation")) {
            for (int bus=0;bus<2;bus++) {
                for (int slot=0;slot<8;slot++) {
                            
                    if (queue_sensor_avg_data[bus][slot][0] > 2 )  {
                        measurement = "/temperature";
                        ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + "_avg" + measurement).toCharArray(topic,200);
                        String(queue_sensor_avg_data[bus][slot][0]).toCharArray(sensor_avg_value,8);
                        client.publish(topic, sensor_avg_value);
                    }

                    if (queue_sensor_avg_data[bus][slot][1] > 2 )  {
                        measurement = "/humidity";
                        ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + "_avg" + measurement).toCharArray(topic,200);
                        String(queue_sensor_avg_data[bus][slot][1]).toCharArray(sensor_avg_value,8);
                        client.publish(topic, sensor_avg_value);
                    }

                    if (queue_sensor_avg_data[bus][slot][2] > 2 )  {
                        measurement = "/CO2";
                        ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + "_avg" + measurement).toCharArray(topic,200);
                        String(queue_sensor_avg_data[bus][slot][2]).toCharArray(sensor_avg_value,8);
                        client.publish(topic, sensor_avg_value);
                    }
                }
            }
        }
        else {
            Serial.print("Could not connect to MQTT server");
        }
    }
}

void publish_valve_positions(void) {

    const char* path = "/json/valvepositions.json";
    char valve_pos[4];
    char valve_nr[10];
    char topic[100];
    const char* mqtt_server_local;
    int mqtt_port_local = 0;
    
    bool status_file_present;

    String mqtt_enable_local;
    String mqtt_base_topic_local;
    String json;
    JsonDocument doc;

    if (settings_mqtt_mutex != NULL) {
        if(xSemaphoreTake(settings_mqtt_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            mqtt_enable_local = String(enable_mqtt);
            mqtt_server_local = mqtt_server;
            mqtt_port_local = mqtt_port;
            mqtt_base_topic_local = String(mqtt_base_topic); 
            xSemaphoreGive(settings_mqtt_mutex);
        }
    }

    Serial.print(mqtt_enable_local);
    Serial.print(mqtt_server_local);
    Serial.print(mqtt_port_local);
    Serial.print(mqtt_base_topic_local);

    Serial.print("\nPublish valve positions.");
    client.setServer(mqtt_server, mqtt_port); 

    if (valve_position_file_mutex != NULL) {
        if(xSemaphoreTake(valve_position_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
    
            status_file_present = check_file_exists(path);

            if (status_file_present == 1) {

                json = read_config_file(path);
                deserializeJson(doc, json);
            }
            xSemaphoreGive(valve_position_file_mutex);
            vTaskDelay(50);
        }
    }

    if (client.connect("OSventilation")) {
        for (int i=0;i<12;i++){
            String valve_nr_str = "valve" + String(i);
            String valve_pos_str = doc[String(valve_nr_str)];
            valve_nr_str.toCharArray(valve_nr,10);
            valve_pos_str.toCharArray(valve_pos,4);
            ("OSVentilation/position/" + valve_nr_str).toCharArray(topic,100);
            client.publish(topic,valve_pos);
        }
    }
    else {
        Serial.println("Could not connect to MQTT server");
    }
}

void publish_uptime(void) {

    const char* topic;
    char uptime[200];

    Serial.print("\nPublish uptime.");
    client.setServer(mqtt_server, 1883);
    
    if (client.connect("OSventilation")) {
        topic="OSVentilation/system/uptime";
        (uptime_formatter::getUptime()).toCharArray(uptime,200);
        client.publish(topic,uptime);
    }
    else {
        Serial.print("\nCould not connect to MQTT server");
    }
}

void publish_fanspeed(void) {
    
    String temp_fanspeed;
    const char* topic;
    char fan[20];

    Serial.print("\nPublish fan speed.");
    client.setServer(mqtt_server, 1883);

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    if (client.connect("OSventilation")) {
        temp_fanspeed.toCharArray(fan,20);
        topic="OSVentilation/status/fanspeed";
        client.publish(topic,fan);
    }
    else {
        Serial.println("Could not connect to MQTT server");
    }
}

void publish_state(void) {

    const char* topic;
    char temp_state[20];

    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state.toCharArray(temp_state,20);
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    
    Serial.print("\nPublish statemachine state.");
    client.setServer(mqtt_server, 1883);

    if (client.connect("OSventilation")) {
        topic="OSVentilation/status/state";
        client.publish(topic,temp_state);
    }
    else {
        Serial.println("Could not connect to MQTT server");
    }
}

/*void publish_queues(void) {
    
    const char* topic;
    char sensor_queue_waiting[5];
    char sensor_queue_space_avail[5];
    String sensor_queue_waiting_str;
    String sensor_queue_space_avail_str;

    Serial.print("\nPublish queue.");
    client.setServer(mqtt_server, 1883);

    sensor_queue_waiting_str = String(uxQueueMessagesWaiting(sensor_queue));
    sensor_queue_space_avail_str = String(uxQueueSpacesAvailable( sensor_queue ));

    if (client.connect("ESP32Client")) {
        sensor_queue_waiting_str.toCharArray(sensor_queue_waiting,5);
        topic="OSVentilation/system/queue_sensor_data_waiting";
        client.publish(topic,sensor_queue_waiting);

        vTaskDelay(50);

        sensor_queue_space_avail_str.toCharArray(sensor_queue_space_avail,5);
        topic="OSVentilation/system/queue_sensor_data_space_avail";
        client.publish(topic,sensor_queue_space_avail);

    }
    else {
        Serial.print("\nCould not connect to MQTT server");
    }
    
}*/

/*void subscribe(void) {

}*/

