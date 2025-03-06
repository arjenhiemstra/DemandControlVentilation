#include "influxdb.h"

void write_sensor_data(void) {
    
    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("Sensors");   

    //Copy array to local array with active mutex an then run slow display function without mutex
    float queque_sensor_data[2][8][3];
    
    //Serial.println("\nTemp sensor data in queue for influxdb:");
    //if (xQueueReceive(sensor_queue, &queque_sensor_data, 0) == pdTRUE) {
    if (xQueuePeek(sensor_queue, &queque_sensor_data, 0) == pdTRUE) {     
    
        // Check server connection. Only write data when connected.
        if (client.validateConnection()) {
            Serial.print("\nConnected to InfluxDB: ");
            Serial.print(client.getServerUrl());
    
            Serial.print("\nWriting sensor data to influxDB.");
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 8; j++) {           
                    if (queque_sensor_data[i][j][0] > 0) {
                        sensor.clearFields();
                        sensor.clearTags();
                        String tag = "sensor" + String(j);
                        String bus = "bus" + String(i);
                        sensor.addTag("device",tag);
                        sensor.addTag("bus",bus);
                        if (queque_sensor_data[i][j][0] > 3) {
                            sensor.addField("temperature", queque_sensor_data[i][j][0]);
                        }
                        if (queque_sensor_data[i][j][1] > 5) {
                            sensor.addField("humidity", queque_sensor_data[i][j][1]);
                        }
                        if (queque_sensor_data[i][j][2] > 5) {
                            sensor.addField("CO2", queque_sensor_data[i][j][2]); 
                        }
                        
                        //Serial.println("Writing sensor data to influxDB: ");
                        //Serial.println(client.pointToLineProtocol(sensor));
                        client.pointToLineProtocol(sensor);
                
                        if (!client.writePoint(sensor)) {
                            Serial.print("InfluxDB write failed: ");
                            Serial.println(client.getLastErrorMessage());
                        }
                        vTaskDelay(50);
                    }
                } 
            }
        }
        else {
            Serial.print("\nInfluxDB connection failed: ");
            Serial.print(client.getLastErrorMessage());
        }
    }
}

void write_valve_position_data(void) {
    
    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("Valves");
    String json;
    JsonDocument doc;

    const char* path = "/json/valvepositions.json";
    bool status_file_present;
    int valve_pos_temp;

    status_file_present = check_file_exists(path);

    if (status_file_present == 1) {
        if (valve_position_file_mutex != NULL) {
            if(xSemaphoreTake(valve_position_file_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
                json = read_config_file(path);
                xSemaphoreGive(valve_position_file_mutex);
            }
        }

        deserializeJson(doc, json);

        Serial.print("\nWriting valve position data to influxDB.");
        for(int i=0;i<12;i++) {
            
            valve_pos_temp = doc["valve"+String(i)];
                        
            sensor.clearFields();
            sensor.clearTags();
            String tag = "valve" + String(i);
            sensor.addTag("device",tag);
            sensor.addField("position", valve_pos_temp);
                        
            client.pointToLineProtocol(sensor);
    
            if (!client.writePoint(sensor)) {
                Serial.print("InfluxDB write failed: ");
                Serial.println(client.getLastErrorMessage());
            }
        }
    }
}

void write_system_uptime(void) {

    uint64_t uptime;

    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("System");

    uptime = (esp_timer_get_time())/1000000;        //in sec
    sensor.clearFields();
    sensor.clearTags();
    //sensor.addTag("system","system");
    sensor.addField("uptime", uptime);
    Serial.print("\nWriting uptime to influxDB.");
    if (!client.writePoint(sensor)) {
        Serial.print("\nInfluxDB write failed: ");
        Serial.print(client.getLastErrorMessage());
    }
}

