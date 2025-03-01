#include "influxdb.h"

void write_sensor_data(void) {
    
    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("Sensors");   

    //Copy array to local array with active mutex an then run slow display function without mutex
    float temp_sensor_data[2][8][3];
    
    //Serial.println("\nTemp sensor data in queue for influxdb:");
    if( sensor_queue != NULL ) {
        if (xQueueReceive(sensor_queue, &temp_sensor_data, ( TickType_t ) 0 ) == pdPASS) {  
        }
    }
    else {
        Serial.print("\n\nReceive - Queue handle is NULL");
    }

    vTaskDelay(100);
    
    Serial.print("\nAvailable places in sensor queue: ");
    Serial.print(uxQueueSpacesAvailable( sensor_queue ));
    Serial.print("\nMessages waiting in sensor queue: ");
    Serial.print(uxQueueMessagesWaiting( sensor_queue ));

    Serial.println("\n\nBus\tSensor\tTemperature (°C)\tHumidity (%)\tCO2 (ppm)");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 8; j++) {
            Serial.print("\n");
            Serial.print(i);
            Serial.print("\t");
            Serial.print(j);
            Serial.print("\t");
            for (int k = 0; k < 3; k++) {
                Serial.print(temp_sensor_data[i][j][k]);
                Serial.print("\t\t");
            }
        }
    }
    
    // Check server connection. Only write data when connected.
    if (client.validateConnection()) {
        Serial.print("\nConnected to InfluxDB: ");
        Serial.print(client.getServerUrl());
  
        Serial.println("\nWriting sensor data to influxDB.");
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {           
                if (temp_sensor_data[i][j][0] > 0) {
                    sensor.clearFields();
                    sensor.clearTags();
                    String tag = "sensor" + String(j);
                    String bus = "bus" + String(i);
                    sensor.addTag("device",tag);
                    sensor.addTag("bus",bus);
                    if (temp_sensor_data[i][j][0] > 3) {
                        sensor.addField("temperature", temp_sensor_data[i][j][0]);
                    }
                    if (temp_sensor_data[i][j][1] > 5) {
                        sensor.addField("humidity", temp_sensor_data[i][j][1]);
                    }
                    if (temp_sensor_data[i][j][2] > 5) {
                        sensor.addField("CO2", temp_sensor_data[i][j][2]); 
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

        Serial.println("Writing valve position data to influxDB.");
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
    Serial.println("Writing uptime to influxDB.");
    if (!client.writePoint(sensor)) {
        Serial.print("InfluxDB write failed: ");
        Serial.println(client.getLastErrorMessage());
    }
}