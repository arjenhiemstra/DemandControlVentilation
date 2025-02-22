#include "mqtt.h"

WiFiClient ESP32Client;
PubSubClient client(ESP32Client);
    
void publish_sensor_data(void) {

    String measurement;
    char topic[200];
    char sensor_value[8];
    float temp_sensor_data[2][8][3];
    int bus;
    int slot;

    //Copy array to local array with active mutex an then run slow display function without mutex
    if (sensor_variable_mutex != NULL) {
        if(xSemaphoreTake(sensor_variable_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 8; j++) {
                    for (int k = 0; k < 3; k++) {
                        temp_sensor_data[i][j][k] = sensor_data[i][j][k];
                    }
                }
            }
            xSemaphoreGive(sensor_variable_mutex);
        }
    }

    client.setServer(mqtt_server, mqtt_port);

    if (client.connect("ESP32Client")) {
        for (int bus=0;bus<2;bus++) {
            for (int slot=0;slot<8;slot++) {
                        
                if (temp_sensor_data[bus][slot][0] > 2 )  {
                    measurement = "/temperature";
                    ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + measurement).toCharArray(topic,200);
                    String(temp_sensor_data[bus][slot][0]).toCharArray(sensor_value,8);
                    client.publish(topic, sensor_value);
                }

                if (temp_sensor_data[bus][slot][1] > 2 )  {
                    measurement = "/humidity";
                    ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + measurement).toCharArray(topic,200);
                    String(temp_sensor_data[bus][slot][1]).toCharArray(sensor_value,8);
                    client.publish(topic, sensor_value);
                }

                if (temp_sensor_data[bus][slot][2] > 2 )  {
                    measurement = "/CO2";
                    ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + measurement).toCharArray(topic,200);
                    String(temp_sensor_data[bus][slot][2]).toCharArray(sensor_value,8);
                    client.publish(topic, sensor_value);
                }
            }
        }
    }
    else {
        Serial.print("Could not connect to MQTT server");
    }
}

void publish_valve_positions(void) {

    const char* path = "/json/valvepositions.json";
    char valve_pos[4];
    char valve_nr[10];
    char topic[100];
    bool status_file_present;

    String json;
    JsonDocument doc;

    client.setServer(mqtt_server, 1883); 

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

    if (client.connect("ESP32Client")) {
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

    client.setServer(mqtt_server, 1883);
    
    if (client.connect("ESP32Client")) {
        topic="OSVentilation/system/uptime";
        (uptime_formatter::getUptime()).toCharArray(uptime,200);
        client.publish(topic,uptime);
    }
    else {
        Serial.println("Could not connect to MQTT server");
    }
}

void publish_fanspeed(String fanspeed) {
    
    const char* topic;
    char fan[20];

    client.setServer(mqtt_server, 1883);

    if (client.connect("ESP32Client")) {
        fanspeed.toCharArray(fan,20);
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
    
    client.setServer(mqtt_server, 1883);

    if (client.connect("ESP32Client")) {
        topic="OSVentilation/status/state";
        client.publish(topic,temp_state);
    }
    else {
        Serial.println("Could not connect to MQTT server");
    }
}

void subscribe(void) {

}

