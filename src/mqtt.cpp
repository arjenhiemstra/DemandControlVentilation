#include "mqtt.h"

WiFiClient ESP32Client;
PubSubClient client(ESP32Client);
    
void publish_sensor_data(void) {

    char topic[200];
    String measurement;
    char sensor_value[8];
    int bus;
    int slot;

    client.setServer(mqtt_server, mqtt_port);

    if (sensor_variable_mutex != NULL) {
        if(xSemaphoreTake(sensor_variable_mutex, ( TickType_t ) 10 ) == pdTRUE) {

            Serial.println("Update MQTT....");
            if (client.connect("ESP32Client")) {
                for (int bus=0;bus<2;bus++) {
                    for (int slot=0;slot<8;slot++) {
                                
                        if (sensor_data[bus][slot][0] != 0.00 )  {
                            measurement = "/temperature";
                            ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + measurement).toCharArray(topic,200);
                            String(sensor_data[bus][slot][0]).toCharArray(sensor_value,8);
                            client.publish(topic, sensor_value);
                            vTaskDelay(50);
                        }

                        if (sensor_data[bus][slot][1] != 0.00 )  {
                            measurement = "/humidity";
                            ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + measurement).toCharArray(topic,200);
                            String(sensor_data[bus][slot][1]).toCharArray(sensor_value,8);
                            client.publish(topic, sensor_value);
                            vTaskDelay(50);
                        }

                        if (sensor_data[bus][slot][2] != 0.00 )  {
                            measurement = "/CO2";
                            ("OSVentilation/bus/" + String(bus) + "/sensor" + String(slot) + measurement).toCharArray(topic,200);
                            String(sensor_data[bus][slot][2]).toCharArray(sensor_value,8);
                            client.publish(topic, sensor_value);
                            vTaskDelay(50);
                        }
                    }
                }
            }
            else {
                Serial.print("No connection to MQTT server");
            }
            xSemaphoreGive(sensor_variable_mutex);
        }
    }
}

void publish_valve_data(void) {

    const char* path = "/valvepositions.json";
    char valve_pos[4];
    char valve_nr[10];
    char topic[100];
    bool status_file_present;

    String json;
    JsonDocument doc;

    client.setServer(mqtt_server, 1883); 

    if (valve_position_mutex != NULL) {
        if(xSemaphoreTake(valve_position_mutex, ( TickType_t ) 10 ) == pdTRUE) {
    
            status_file_present = check_file_exists(path);

            if (status_file_present == 1) {

                json = read_config_file(path);
                deserializeJson(doc, json);

                for (int i=0;i<12;i++){

                    String valve_nr_str = "valve" + String(i);
                    String valve_pos_str = doc[String(valve_nr_str)];
                    valve_nr_str.toCharArray(valve_nr,10);
                    valve_pos_str.toCharArray(valve_pos,4);
                    ("OSVentilation/position/" + valve_nr_str).toCharArray(topic,100);
                    client.publish(topic,valve_pos);
                }
            }
            xSemaphoreGive(valve_position_mutex);
        }
    }
}

void publish_state(void) {
    
}

void subscribe(void) {

}