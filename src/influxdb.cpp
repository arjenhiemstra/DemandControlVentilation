#include "influxdb.h"

void write_sensor_data(void) {
    
    String enable_influxdb_tmp;
    String influxdb_url_tmp;
    String influxdb_org_tmp;
    String influxdb_bucket_tmp;
    String influxdb_token_tmp;
    String settings_state_day_path_str;
    String state_tmp;

    float queue_sensor_data[2][8][3];

    JsonDocument wire_sensor_data_temp;
    JsonDocument wire1_sensor_data_temp;
    
    if (settings_influxdb_mutex != NULL) {
        if(xSemaphoreTake(settings_influxdb_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            enable_influxdb_tmp = enable_influxdb;
            influxdb_url_tmp = influxdb_url;
            influxdb_org_tmp = influxdb_org;
            influxdb_bucket_tmp = influxdb_bucket;
            influxdb_token_tmp = influxdb_token;
            xSemaphoreGive(settings_influxdb_mutex);
        }
    }

    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state_tmp = state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    
    //Read setting for valve and valve name
    if (sensor_config_file_mutex != NULL) {
        if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            wire_sensor_data_temp = wire1_sensor_data;
            wire1_sensor_data_temp = wire1_sensor_data;
        }
        xSemaphoreGive(sensor_config_file_mutex);
    }

    //serializeJsonPretty(wire_sensor_data_temp, Serial);

    InfluxDBClient client(influxdb_url_tmp, influxdb_org_tmp, influxdb_bucket_tmp, influxdb_token_tmp);
    Point sensor("Sensors");

    if (xQueuePeek(sensor_queue, &queue_sensor_data, 0) == pdTRUE) {     
    
        // Check server connection. Only write data when connected.
        if (client.validateConnection()) {   
            Serial.print("\nWriting sensor data to influxDB.");
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 8; j++) {    
                    if (queue_sensor_data[i][j][0] > 0) {
                        sensor.clearFields();
                        sensor.clearTags();      
                        if (i == 0) {

                            String sensor_valve = wire_sensor_data_temp["wire_sensor" + String(j)]["valve"];
                            String sensor_location = wire_sensor_data_temp["wire_sensor" + String(j)]["location"];
                            Serial.print("Sensor data: " + sensor_location + "\t\t" + sensor_valve);
                            sensor.addTag("valve", sensor_valve);
                            sensor.addTag("location", sensor_location);
                        }
                        else {
                            String sensor_valve = wire1_sensor_data_temp["wire1_sensor" + String(j)]["valve"];
                            String sensor_location = wire1_sensor_data_temp["wire1_sensor" + String(j)]["location"];
                            Serial.print("Sensor data: " + sensor_location + "\t\t" + sensor_valve);
                            sensor.addTag("valve", sensor_valve);
                            sensor.addTag("location", sensor_location);
                        }    
                        String tag = "sensor" + String(j);
                        String bus = "bus" + String(i);
                        sensor.addTag("device",tag);
                        sensor.addTag("bus",bus);
                        
                        if (queue_sensor_data[i][j][0] > 3) {
                            sensor.addField("temperature", queue_sensor_data[i][j][0]);
                        }
                        if (queue_sensor_data[i][j][1] > 5) {
                            sensor.addField("humidity", queue_sensor_data[i][j][1]);
                        }
                        if (queue_sensor_data[i][j][2] > 5) {
                            sensor.addField("CO2", queue_sensor_data[i][j][2]); 
                        }
                        
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

void write_avg_sensor_data(void) {
    
    String enable_influxdb_tmp;
    String influxdb_url_tmp;
    String influxdb_org_tmp;
    String influxdb_bucket_tmp;
    String influxdb_token_tmp;
    
    if (settings_influxdb_mutex != NULL) {
        if(xSemaphoreTake(settings_influxdb_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            enable_influxdb_tmp = enable_influxdb;
            influxdb_url_tmp = influxdb_url;
            influxdb_org_tmp = influxdb_org;
            influxdb_bucket_tmp = influxdb_bucket;
            influxdb_token_tmp = influxdb_token;
            xSemaphoreGive(settings_influxdb_mutex);
        }
    }
    
    InfluxDBClient client(influxdb_url_tmp, influxdb_org_tmp, influxdb_bucket_tmp, influxdb_token_tmp);
    Point sensor("Sensors_avg");   

    float queue_avg_sensor_data[2][8][3];

    if (xQueuePeek(sensor_avg_queue, &queue_avg_sensor_data, 0) == pdTRUE) {     
        if (client.validateConnection()) {    
            Serial.print("\nWriting average sensor data to influxDB.");
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 8; j++) {           
                    if (queue_avg_sensor_data[i][j][0] > 0) {
                        sensor.clearFields();
                        sensor.clearTags();
                        String tag = "sensor" + String(j);
                        String bus = "bus" + String(i);
                        sensor.addTag("device",tag);
                        sensor.addTag("bus",bus);
                        sensor.addField("temperature", queue_avg_sensor_data[i][j][0]);
                        sensor.addField("humidity", queue_avg_sensor_data[i][j][1]);
                        sensor.addField("CO2", queue_avg_sensor_data[i][j][2]); 
                        
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
    
    const char* path = "/json/valvepositions.json";
    bool status_file_present;
    int valve_pos_temp;
    int valve_pos_sum=0;

    String enable_influxdb_tmp;
    String influxdb_url_tmp;
    String influxdb_org_tmp;
    String influxdb_bucket_tmp;
    String influxdb_token_tmp;

    String json;
    JsonDocument doc;
    
    if (settings_influxdb_mutex != NULL) {
        if(xSemaphoreTake(settings_influxdb_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                          
            //Assign to global variable
            enable_influxdb_tmp = enable_influxdb;
            influxdb_url_tmp = influxdb_url;
            influxdb_org_tmp = influxdb_org;
            influxdb_bucket_tmp = influxdb_bucket;
            influxdb_token_tmp = influxdb_token;
            xSemaphoreGive(settings_influxdb_mutex);
        }
    }

    InfluxDBClient client(influxdb_url_tmp, influxdb_org_tmp, influxdb_bucket_tmp, influxdb_token_tmp);
    Point sensor("Valves");
    
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
            valve_pos_sum = valve_pos_sum + valve_pos_temp;
            
            if (valve_pos_sum != 0) {
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
}

void write_system_uptime(void) {

    uint64_t uptime;

    String enable_influxdb_tmp;
    String influxdb_url_tmp;
    String influxdb_org_tmp;
    String influxdb_bucket_tmp;
    String influxdb_token_tmp;
    
    if (settings_influxdb_mutex != NULL) {
        if(xSemaphoreTake(settings_influxdb_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            enable_influxdb_tmp = enable_influxdb;
            influxdb_url_tmp = influxdb_url;
            influxdb_org_tmp = influxdb_org;
            influxdb_bucket_tmp = influxdb_bucket;
            influxdb_token_tmp = influxdb_token;
            xSemaphoreGive(settings_influxdb_mutex);
        }
    }

    InfluxDBClient client(influxdb_url_tmp, influxdb_org_tmp, influxdb_bucket_tmp, influxdb_token_tmp);
    //InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("System");

    uptime = (esp_timer_get_time())/1000000;        //in sec
    sensor.clearFields();
    sensor.clearTags();
    sensor.addField("uptime", uptime);
    Serial.print("\nWriting uptime to influxDB.");
    if (!client.writePoint(sensor)) {
        Serial.print("\nInfluxDB write failed: ");
        Serial.print(client.getLastErrorMessage());
    }
}

void write_state_info(void) {
    
    int temp_state_nr;
    String enable_influxdb_tmp;
    String influxdb_url_tmp;
    String influxdb_org_tmp;
    String influxdb_bucket_tmp;
    String influxdb_token_tmp;
    String temp_state;
    
    if (settings_influxdb_mutex != NULL) {
        if(xSemaphoreTake(settings_influxdb_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            enable_influxdb_tmp = enable_influxdb;
            influxdb_url_tmp = influxdb_url;
            influxdb_org_tmp = influxdb_org;
            influxdb_bucket_tmp = influxdb_bucket;
            influxdb_token_tmp = influxdb_token;
            xSemaphoreGive(settings_influxdb_mutex);
        }
    }

    InfluxDBClient client(influxdb_url_tmp, influxdb_org_tmp, influxdb_bucket_tmp, influxdb_token_tmp);
    Point sensor("Status");

    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            temp_state = state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    //Need to translate state to number for easy processing in Grafana
    if (temp_state == "init") {
        temp_state_nr = 1;
    }
    else if (temp_state == "night") {
        temp_state_nr = 2;
    }
    else if (temp_state == "day") {
        temp_state_nr = 3;
    }
    else if (temp_state == "highco2night") {
        temp_state_nr = 4;
    }
    else if (temp_state == "highco2day") {
        temp_state_nr = 5;
    }
    else if (temp_state == "manualhighspeed") {
        temp_state_nr = 6;
    }
    else if (temp_state == "cyclingnight") {
        temp_state_nr = 7;
    }
    else if (temp_state == "cyclingday") {
        temp_state_nr = 8;
    }
    else if (temp_state == "cooking") {
        temp_state_nr = 9;
    }
    else if (temp_state == "highrhnight") {
        temp_state_nr = 10;
    }
    else if (temp_state == "highrhday") {
        temp_state_nr = 11;
    }
    else if (temp_state == "stopped") {
        temp_state_nr = 12;
    }
    else {
        temp_state_nr = 13;
    }

    sensor.clearFields();
    sensor.clearTags();
    sensor.addField("state", temp_state_nr);
    Serial.print("\nWriting statemachine state to influxDB.");
    if (!client.writePoint(sensor)) {
        Serial.print("\nInfluxDB write failed: ");
        Serial.print(client.getLastErrorMessage());
    }
}

void write_fanspeed(void) {
    
    String enable_influxdb_tmp;
    String influxdb_url_tmp;
    String influxdb_org_tmp;
    String influxdb_bucket_tmp;
    String influxdb_token_tmp;
    
    if (settings_influxdb_mutex != NULL) {
        if(xSemaphoreTake(settings_influxdb_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            enable_influxdb_tmp = enable_influxdb;
            influxdb_url_tmp = influxdb_url;
            influxdb_org_tmp = influxdb_org;
            influxdb_bucket_tmp = influxdb_bucket;
            influxdb_token_tmp = influxdb_token;
            xSemaphoreGive(settings_influxdb_mutex);
        }
    }

    InfluxDBClient client(influxdb_url_tmp, influxdb_org_tmp, influxdb_bucket_tmp, influxdb_token_tmp);
    Point sensor("Status");

    String temp_fanspeed;
    int temp_fanspeed_nr;

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    //Need to translate fanspeed to number for easy processing in Grafana
    if (temp_fanspeed == "Low") {
        temp_fanspeed_nr = 1;
    }
    else if (temp_fanspeed == "Medium") {
        temp_fanspeed_nr = 2;
    }
    else if (temp_fanspeed == "High") {
        temp_fanspeed_nr = 3;
    }
    else {
        temp_fanspeed_nr = 4;
    }

    sensor.clearFields();
    sensor.clearTags();
    sensor.addField("fanspeed", temp_fanspeed_nr);
    Serial.print("\nWriting fanspeed state to influxDB.");
    if (!client.writePoint(sensor)) {
        Serial.print("\nInfluxDB write failed: ");
        Serial.print(client.getLastErrorMessage());
    }
}

void write_heap_info(void) {

    int free_heap_size;
    int minimum_ever_free_heap_size;

    String enable_influxdb_tmp;
    String influxdb_url_tmp;
    String influxdb_org_tmp;
    String influxdb_bucket_tmp;
    String influxdb_token_tmp;
    
    if (settings_influxdb_mutex != NULL) {
        if(xSemaphoreTake(settings_influxdb_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            enable_influxdb_tmp = enable_influxdb;
            influxdb_url_tmp = influxdb_url;
            influxdb_org_tmp = influxdb_org;
            influxdb_bucket_tmp = influxdb_bucket;
            influxdb_token_tmp = influxdb_token;
            xSemaphoreGive(settings_influxdb_mutex);
        }
    }

    free_heap_size = xPortGetFreeHeapSize();
    Serial.print("\nFree heap size: ");
    Serial.print(free_heap_size);

    minimum_ever_free_heap_size = xPortGetMinimumEverFreeHeapSize();
    Serial.print("\nMinimum ever free heap size: ");
    Serial.print(minimum_ever_free_heap_size);

    InfluxDBClient client(influxdb_url_tmp, influxdb_org_tmp, influxdb_bucket_tmp, influxdb_token_tmp);
    Point sensor("System_stats");
    sensor.clearFields();
    sensor.clearTags();

    sensor.addField("min_free_heap_size_ever", minimum_ever_free_heap_size);
    sensor.addField("free_heap_size", free_heap_size);
    
    Serial.print("\nWriting heap info to influxDB.");
    if (!client.writePoint(sensor)) {
        Serial.print("\nInfluxDB write failed: ");
        Serial.print(client.getLastErrorMessage());
    }
}
