/*
This sensor interacts with the sensors and writes the values to a global variable. The input for 
this function is the sensors config file which is stored in LittleFS. The measured values must be
stored in a global variable so other tasks, e.g. statemachine, web inteface, MQTT communication can use this data. 
Permanent storage of measured data is not required so a two dimensional array would be most suitable
which is in memery only.

Two arrays of sensors data, one for each I2C multiplexer:
sensordata_I2C1[8][3]
sensordata_I2C2[8][3]

The array structure:
sensordata_I2C1[0][21,50,700] //Sensor0 with three readings: temp, RH, CO2
sensordata_I2C1[1][22,52,705] //Sensor1 with three readings: temp, RH, CO2
.....
sensordata_I2C1[7][21,50,700] //Sensor7 with three readings: temp, RH,CO2

Note that not all sensors have CO2 measurement so the mesasured value stays 0 (as array is initialised with zeros)

Sequence:

1. Read sensor config file
2. Get measurement data from sensors
3. Write measured values to varaible
*/

#include "read_sensors.h"

void read_bus0(void) {
 
    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);

    bool sensor_config_file_present;
    const char* path1 = "/json/sensor_config1.json";
    int bus = 0;

    if (sensor_variable_mutex != NULL) {
        if(xSemaphoreTake(sensor_variable_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            
            sensor_config_file_present = check_file_exists(path1);
            Serial.println("\nBus\tSensor\tType\tTemperature (°C)\tHumidity (%)\tCO2 (ppm)");
            if(sensor_config_file_present == 1) {
                
                for (int slot=0;slot<8;slot++) {

                    String sensor = "wire_sensor" + String(slot);
                    String sensor_type = wire_sensor_data[sensor]["type"];
                    String sensor_address = wire_sensor_data[sensor]["address"];
                                    
                    Wire.beginTransmission(TCAADDR);
                    Wire.write(1 << slot);
                    Wire.endTransmission();

                    if (sensor_type == "DHT20") {
                        
                        DHT20 DHT1(&Wire);
                        DHT1.begin();
                        int status = DHT1.read();
                        
                        if(status == DHT20_OK) {
                            sensor_data[bus][slot][0] = DHT1.getTemperature();
                            sensor_data[bus][slot][1] = DHT1.getHumidity();
                        }

                        //Wire.endTransmission();

                        Serial.print(bus);Serial.print("\t");Serial.print(slot);Serial.print("\t");Serial.print(sensor_type);Serial.print("\t");
                        Serial.print(sensor_data[bus][slot][0]);Serial.print("\t\t\t");
                        Serial.print(sensor_data[bus][slot][1]);Serial.print("\t\t");
                        Serial.print(sensor_data[bus][slot][2]);Serial.print("\n");
                    }
                    
                    else if (sensor_type == "AHT20") {
                                    
                        Adafruit_AHTX0 AHT20_1;
                        AHT20_1.begin();
                        sensors_event_t humidity, temp;
                        AHT20_1.getEvent(&humidity, &temp);
                        
                        sensor_data[bus][slot][0] = temp.temperature;
                        sensor_data[bus][slot][1] = humidity.relative_humidity;

                        //Wire.endTransmission();
                        
                        Serial.print(bus);Serial.print("\t");Serial.print(slot);Serial.print("\t");Serial.print(sensor_type);Serial.print("\t");
                        Serial.print(sensor_data[bus][slot][0]);Serial.print("\t\t\t");
                        Serial.print(sensor_data[bus][slot][1]);Serial.print("\t\t");
                        Serial.print(sensor_data[bus][slot][2]);Serial.print("\n");
                    }
                    
                    else if (sensor_type == "SCD40" || sensor_type == "SCD41") {
                            
                        SensirionI2cScd4x SCD4X_1;
                        SCD4X_1.begin(Wire1, SCD41_I2C_ADDR_62);
                        SCD4X_1.startPeriodicMeasurement();
                    
                        uint16_t error;
                        uint16_t co2 = 0;
                        float temperature = 0.0f;
                        float humidity = 0.0f;
                        bool isDataReady = false;
            
                        error = SCD4X_1.readMeasurement(co2, temperature, humidity);
                        if (error) {
                            Serial.print("Error trying to execute readMeasurement(): ");
                        } 
                        else if (co2 == 0) {
                            Serial.println("Invalid sample detected, skipping.");
                        } 
                        else {
                            sensor_data[bus][slot][0] = temperature;
                            sensor_data[bus][slot][1] = humidity;
                            sensor_data[bus][slot][2] = co2;

                            Serial.print(bus);Serial.print("\t");Serial.print(slot);Serial.print("\t");Serial.print(sensor_type);Serial.print("\t");
                            Serial.print(sensor_data[bus][slot][0]);Serial.print("\t\t\t");
                            Serial.print(sensor_data[bus][slot][1]);Serial.print("\t\t");
                            Serial.print(sensor_data[bus][slot][2]);Serial.print("\n");
                        }
                        //Wire.endTransmission();
                    }
                    else {
                        //Serial.print(bus);Serial.print("\t");Serial.print(slot);Serial.print("\t");Serial.print("No sensor.\n");
                        
                        sensor_data[bus][slot][0] = 0;
                        sensor_data[bus][slot][1] = 0;
                        sensor_data[bus][slot][2] = 0;
                        
                        Serial.print(bus);Serial.print("\t");Serial.print(slot);Serial.print("\t");Serial.print(sensor_type);Serial.print("\t");
                        Serial.print(sensor_data[bus][slot][0]);Serial.print("\t\t\t");
                        Serial.print(sensor_data[bus][slot][1]);Serial.print("\t\t");
                        Serial.print(sensor_data[bus][slot][2]);Serial.print("\n");
                    }
                }
            }
            xSemaphoreGive(sensor_variable_mutex);
        }
    }
}

void read_bus1(void) {
 
    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);
    
    bool sensor_config_file_present;
    const char* path = "/json/sensor_config2.json";
    int bus = 1;

    if (sensor_variable_mutex != NULL) {
        if(xSemaphoreTake(sensor_variable_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            
            sensor_config_file_present = check_file_exists(path);
            Serial.println("\nBus\tSensor\tType\tTemperature (°C)\tHumidity (%)\tCO2 (ppm)");
            if(sensor_config_file_present == 1) {
                for (int slot=0;slot<8;slot++) {

                    String sensor = "wire1_sensor" + String(slot);
                    String sensor_type = wire1_sensor_data[sensor]["type"];
                    String sensor_address = wire1_sensor_data[sensor]["address"];
                                    
                    Wire1.beginTransmission(TCAADDR);
                    Wire1.write(1 << slot);
                    Wire1.endTransmission();

                    if (sensor_type == "DHT20") {
                        
                        DHT20 DHT2(&Wire1);
                        DHT2.begin();
                        int status = DHT2.read();
                        
                        if(status == DHT20_OK) {
                            sensor_data[bus][slot][0] = DHT2.getTemperature();
                            sensor_data[bus][slot][1] = DHT2.getHumidity();
                        }

                        //Wire1.endTransmission();
                        
                        Serial.print(bus);Serial.print("\t");Serial.print(slot);Serial.print("\t");Serial.print(sensor_type);Serial.print("\t");
                        Serial.print(sensor_data[bus][slot][0]);Serial.print("\t\t\t");
                        Serial.print(sensor_data[bus][slot][1]);Serial.print("\t\t");
                        Serial.print(sensor_data[bus][slot][2]);Serial.print("\n");
                    }
                    
                    else if (sensor_type == "AHT20") {
                                    
                        Adafruit_AHTX0 AHT20_2;
                        AHT20_2.begin(&Wire1);
                        sensors_event_t humidity, temp;
                        AHT20_2.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
                        
                        sensor_data[bus][slot][0] = temp.temperature;
                        sensor_data[bus][slot][1] = humidity.relative_humidity;

                        //Wire1.endTransmission();
                        
                        Serial.print(bus);Serial.print("\t");Serial.print(slot);Serial.print("\t");Serial.print(sensor_type);Serial.print("\t");
                        Serial.print(sensor_data[bus][slot][0]);Serial.print("\t\t\t");
                        Serial.print(sensor_data[bus][slot][1]);Serial.print("\t\t");
                        Serial.print(sensor_data[bus][slot][2]);Serial.print("\n");
                    }
                    
                    else if (sensor_type == "SCD40" || sensor_type ==  "SCD41") {
                        
                        SensirionI2cScd4x SCD4X_2;
                        SCD4X_2.begin(Wire1, SCD41_I2C_ADDR_62);
                        SCD4X_2.startPeriodicMeasurement();
                    
                        uint16_t error;
                        uint16_t co2 = 0;
                        float temperature = 0.0f;
                        float humidity = 0.0f;
                        bool isDataReady = false;
            
                        error = SCD4X_2.readMeasurement(co2, temperature, humidity);
                        if (error) {
                            Serial.print("Error trying to execute readMeasurement(): ");
                        } 
                        else if (co2 == 0) {
                            Serial.println("Invalid sample detected, skipping.");
                        } 
                        else {
                            sensor_data[bus][slot][0] = temperature;
                            sensor_data[bus][slot][1] = humidity;
                            sensor_data[bus][slot][2] = co2;
                            
                            Serial.print(bus);Serial.print("\t");Serial.print(slot);Serial.print("\t");Serial.print(sensor_type);Serial.print("\t");
                            Serial.print(sensor_data[bus][slot][0]);Serial.print("\t\t\t");
                            Serial.print(sensor_data[bus][slot][1]);Serial.print("\t\t");
                            Serial.print(sensor_data[bus][slot][2]);Serial.print("\n");
                        }
                        //Wire1.endTransmission();
                    }
                    else {
                        //Serial.print(bus);Serial.print("\t");Serial.print(slot);Serial.print("\t");Serial.print("No sensor.\n");

                        sensor_data[bus][slot][0] = 0;
                        sensor_data[bus][slot][1] = 0;
                        sensor_data[bus][slot][2] = 0;
                        
                        Serial.print(bus);Serial.print("\t");Serial.print(slot);Serial.print("\t");Serial.print(sensor_type);Serial.print("\t");
                        Serial.print(sensor_data[bus][slot][0]);Serial.print("\t\t\t");
                        Serial.print(sensor_data[bus][slot][1]);Serial.print("\t\t");
                        Serial.print(sensor_data[bus][slot][2]);Serial.print("\n");
                    }
                }
            }
            xSemaphoreGive(sensor_variable_mutex);
        }
    }
}
