#include "mqtt.h"

EthernetClient ESP32Client;
PubSubClient client(ESP32Client);
    
void publish_sensor_data(void) {

    const char* topic;
    String measurement;
    const char* sensor_value;
    int bus;
    int slot;

    client.setServer(mqtt_server, 1883);

    xSemaphoreTake(sensor_variable_mutex, portMAX_DELAY);

    if (client.connect("ESP32Client")) {
        for (int bus=0;bus<2;bus++) {
            for (int slot=0;slot<8;slot++) {
                        
                if (sensor_data[bus][slot][0] != 0 )  {
                    measurement = "/temperature";
                    topic = ("OSVentilation/" + String(bus) + "/" + String(slot) + measurement).c_str();
                    sensor_value = (String(sensor_data[bus][slot][0],2)).c_str();
                    client.publish(topic, sensor_value);
                }

                if (sensor_data[bus][slot][1] != 0 )  {
                    measurement = "/humidity";
                    topic = ("OSVentilation/" + String(bus) + "/" + String(slot) + measurement).c_str();
                    sensor_value = (String(sensor_data[bus][slot][1],2)).c_str();
                    client.publish(topic, sensor_value);
                }

                if (sensor_data[bus][slot][2] != 0 )  {
                    measurement = "/CO2";
                    topic = ("OSVentilation/" + String(bus) + "/" + String(slot) + measurement).c_str();
                    sensor_value = (String(sensor_data[bus][slot][2],2)).c_str();
                    client.publish(topic, sensor_value);
                }
            }
        }
    }
    xSemaphoreGive(sensor_variable_mutex);
}

void publish_valve_data(void) {

    const char* path = "/valvepositions.json";
    bool status_file_present;

    String json;
    JsonDocument doc;

    client.setServer(mqtt_server, 1883);
    
    xSemaphoreTake(valve_position_mutex, portMAX_DELAY);
    
    status_file_present = check_file_exists(path);

    if (status_file_present == 1) {

        json = read_config_file(path);
        deserializeJson(doc, json);

        for (int i=0;i<12;i++){

            String valve = "valve" + String(i);                 //valve number compilation
            String valve_pos = doc[String(valve)];              //get valve position from doc as string
            String topic = "OSVentilation/position/" + valve;   //MQTT topic compilation
            client.publish(topic.c_str(), valve_pos.c_str());
        }
    }

    xSemaphoreGive(valve_position_mutex);
}

void subscribe(void) {

}