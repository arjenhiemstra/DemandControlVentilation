#include "influxdb.h"

void write_sensor_data(void) {
    
    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
    Point sensor("Sensors");

    

    //Copy array to local array with active mutex an then run slow display function without mutex
    float temp_sensor_data[2][8][3];

    if (sensor_variable_mutex != NULL) {
        if(xSemaphoreTake(sensor_variable_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            vTaskDelay(100);
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 8; j++) {
                    for (int k = 0; k < 3; k++) {
                        temp_sensor_data[i][j][k] = sensor_data[i][j][k];
                    }
                }
            }
            vTaskDelay(100);
            xSemaphoreGive(sensor_variable_mutex);
        }
    }

    // Check server connection
    if (client.validateConnection()) {
        Serial.print("Connected to InfluxDB: ");
        Serial.println(client.getServerUrl());
    } 
    else {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(client.getLastErrorMessage());
    }

    sensor.clearFields();
    sensor.addTag("device","Bus0 - Sensor0");
    sensor.addField("temperature", temp_sensor_data[0][0][0]);


    Serial.print("Writing: ");
    Serial.println(client.pointToLineProtocol(sensor));

    if (!client.writePoint(sensor)) {
        Serial.print("InfluxDB write failed: ");
        Serial.println(client.getLastErrorMessage());
    }

}