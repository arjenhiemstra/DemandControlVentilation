#include "influxdb.h"

void write_sensor_data(void) {
    
    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("Sensors");   

    //Copy array to local array with active mutex an then run slow display function without mutex
    float queue_sensor_data[2][8][3];

    if (xQueuePeek(sensor_queue, &queue_sensor_data, 0) == pdTRUE) {     
    
        // Check server connection. Only write data when connected.
        if (client.validateConnection()) {
            //Serial.print("\nConnected to InfluxDB: ");
            //Serial.print(client.getServerUrl());
    
            Serial.print("\nWriting sensor data to influxDB.");
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 8; j++) {           
                    if (queue_sensor_data[i][j][0] > 0) {
                        sensor.clearFields();
                        sensor.clearTags();
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
    
    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("Sensors_avg");   

    //Copy array to local array with active mutex an then run slow display function without mutex
    float queue_avg_sensor_data[2][8][3];

    if (xQueuePeek(sensor_avg_queue, &queue_avg_sensor_data, 0) == pdTRUE) {     
        // Check server connection. Only write data when connected.
        if (client.validateConnection()) {
            //Serial.print("\nConnected to InfluxDB: ");
            //Serial.print(client.getServerUrl());
    
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
                        //if (queue_avg_sensor_data[i][j][0] > 3) {
                            sensor.addField("temperature", queue_avg_sensor_data[i][j][0]);
                        //}
                        //if (queue_avg_sensor_data[i][j][1] > 5) {
                            sensor.addField("humidity", queue_avg_sensor_data[i][j][1]);
                        //}
                        //if (queue_avg_sensor_data[i][j][2] > 5) {
                            sensor.addField("CO2", queue_avg_sensor_data[i][j][2]); 
                        //}
                        
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
    int valve_pos_sum=0;

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

    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
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
    
    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("Status");

    String temp_state;
    int temp_state_nr;

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
    else {
        temp_state_nr = 12;
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
    
    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
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
    if (temp_fanspeed == "low") {
        temp_fanspeed_nr = 1;
    }
    else if (temp_fanspeed == "medium") {
        temp_fanspeed_nr = 2;
    }
    else if (temp_fanspeed == "high") {
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

    int influxdb_hwm;
    int i2c_hwm;
    int mqtt_hwm;
    int np_hwm;
    int statemach_hwm;
    int sys_hwm;
    int valvectrl_hwm;
    int web_hwm;
    int wifi_hwm;

    int free_heap_size;
    int minimum_ever_free_heap_size;
    int available_heap_space_bytes;
    
    if (task_influxdb != NULL) {
        influxdb_hwm = uxTaskGetStackHighWaterMark(task_influxdb);
    }
    if (task_i2c != NULL) {
        i2c_hwm = uxTaskGetStackHighWaterMark(task_i2c);
    }
    if (task_mqtt != NULL) {
        mqtt_hwm = uxTaskGetStackHighWaterMark(task_mqtt);
    }
    if (task_np != NULL) {
        np_hwm = uxTaskGetStackHighWaterMark(task_np);
    }
    if (task_statemach != NULL) {
        statemach_hwm = uxTaskGetStackHighWaterMark(task_statemach);
    }
    if (task_sys != NULL) {
        sys_hwm = uxTaskGetStackHighWaterMark(task_sys);
    }
    if (task_valvectrl != NULL) {
        valvectrl_hwm = uxTaskGetStackHighWaterMark(task_valvectrl);
    }
    if (h_Task_web != NULL) {
        web_hwm = uxTaskGetStackHighWaterMark(h_Task_web);
    }
    if (task_wifi != NULL) {
        wifi_hwm = uxTaskGetStackHighWaterMark(task_wifi);
    }

    Serial.print("\nTask\t\t\tHigh water mark");
    Serial.print("\ntask_influxdb\t\t"); Serial.print(influxdb_hwm);    
    Serial.print("\ntask_i2c\t\t"); Serial.print(i2c_hwm);
    Serial.print("\ntask_mqtt\t\t"); Serial.print(mqtt_hwm);
    Serial.print("\ntask_np\t\t\t"); Serial.print(np_hwm); 
    Serial.print("\ntask_statemach\t\t"); Serial.print(statemach_hwm);
    Serial.print("\ntask_sys\t\t"); Serial.print(sys_hwm);
    Serial.print("\ntask_valvectrl\t\t"); Serial.print(valvectrl_hwm);
    Serial.print("\ntask_web\t\t"); Serial.print(web_hwm);
    Serial.print("\ntask_wifi\t\t"); Serial.print(wifi_hwm);

    free_heap_size = xPortGetFreeHeapSize();
    Serial.print("\nFree heap size: ");
    Serial.print(free_heap_size);

    minimum_ever_free_heap_size = xPortGetMinimumEverFreeHeapSize();
    Serial.print("\nMinimum ever free heap size: ");
    Serial.print(minimum_ever_free_heap_size);

    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("System_stats");
    sensor.clearFields();
    sensor.clearTags();
    sensor.addField("task_influxdb_hwm", influxdb_hwm);
    sensor.addField("task_i2c_hwm", i2c_hwm);
    sensor.addField("task_mqtt_hwm", mqtt_hwm);
    sensor.addField("task_np_hwm", np_hwm);
    sensor.addField("task_statemach_hwm", statemach_hwm);
    sensor.addField("task_sys_hwm", sys_hwm);
    sensor.addField("task_valvectrl_hwm", valvectrl_hwm);
    sensor.addField("task_web_hwm", web_hwm);
    sensor.addField("task_wifi_hwm", wifi_hwm);
    sensor.addField("min_free_heap_size_ever", minimum_ever_free_heap_size);
    sensor.addField("free_heap_size", free_heap_size);
    
    Serial.print("\nWriting heap info to influxDB.");
    if (!client.writePoint(sensor)) {
        Serial.print("\nInfluxDB write failed: ");
        Serial.print(client.getLastErrorMessage());
    }
}