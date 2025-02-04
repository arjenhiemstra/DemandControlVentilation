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

DHT20 DHT1(&Wire);
DHT20 DHT2(&Wire1);
Adafruit_AHTX0 AHT20_1;
Adafruit_AHTX0 AHT20_2;
SensirionI2cScd4x SCD4X_1;
SensirionI2cScd4x SCD4X_2;

void read_bus0(void) {
 
    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);

    bool sensor_config_file_present;
    const char* path1 = "/sensor_config1.json";

    sensor_config_file_present = check_file_exists(path1);
 
    if(sensor_config_file_present == 1) {
        for (int slot=0;slot<8;slot++) {

            String sensor = "wire_sensor" + String(slot);
            String sensor_type = wire_sensor_data[sensor]["type"];
            String sensor_address = wire_sensor_data[sensor]["address"];
                             
            Wire.beginTransmission(TCAADDR);
            Wire.write(1 << slot);
            Wire.endTransmission();
            
            Serial.print("\n\nWire sensors, slot "); Serial.print(slot);
            Serial.print(", Sensor type: "); Serial.print(sensor_type);
            Serial.println();

            if (sensor_type == "DHT20") {
                
                DHT1.begin();
                int status = DHT1.read();
                
                sensor1_data[slot][0] = DHT1.getTemperature();
                sensor1_data[slot][1] = DHT1.getHumidity();

                Serial.print("Temperature: "); Serial.print(sensor1_data[slot][0]); Serial.print(" °C");
                Serial.print(",\t\t");
                Serial.print("Humidity: "); Serial.print(sensor1_data[slot][1]); Serial.print(" %");
            }
            
            else if (sensor_type == "AHT20") {
                               
                AHT20_1.begin();
                sensors_event_t humidity, temp;
                AHT20_1.getEvent(&humidity, &temp);
                
                sensor1_data[slot][0] = temp.temperature;
                sensor1_data[slot][1] = humidity.relative_humidity;
                
                Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.print(" °C");
                Serial.print(",\t\t");
                Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.print(" %");
            }
            
            else if (sensor_type == "SCD40" || sensor_type == "SCD41") {
                    
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
                    sensor1_data[slot][0] = temperature;
                    sensor1_data[slot][1] = humidity;
                    sensor1_data[slot][2] = co2;
                    Serial.print("Temperature: "); Serial.print(temperature); Serial.print(" °C");
                    Serial.print("\t\t");
                    Serial.print("Humidity: "); Serial.print(humidity); Serial.print(" %");
                    Serial.print("\t\t");
                    Serial.print("Co2: "); Serial.print(co2); Serial.print(" ppm");
                }
            }
            else {
                Serial.println("No sensor configured.");
            }
        }

    }
}

void read_bus1(void) {
 
    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);
    
    bool sensor_config_file_present;
    const char* path = "/sensor_config2.json";

    sensor_config_file_present = check_file_exists(path);
 
    if(sensor_config_file_present == 1) {
        for (int slot=0;slot<8;slot++) {

            String sensor = "wire1_sensor" + String(slot);
            String sensor_type = wire1_sensor_data[sensor]["type"];
            String sensor_address = wire1_sensor_data[sensor]["address"];
                             
            Wire1.beginTransmission(TCAADDR);
            Wire1.write(1 << slot);
            Wire1.endTransmission();
            
            Serial.print("\n\nWire1 sensors, slot "); Serial.print(slot);
            Serial.print(", Sensor type: "); Serial.print(sensor_type);
            Serial.println();

            if (sensor_type == "DHT20") {
                
                DHT2.begin();
                int status = DHT2.read();
                
                sensor2_data[slot][0] = DHT2.getTemperature();
                sensor2_data[slot][1] = DHT2.getHumidity();
                Serial.print("Temperature: "); Serial.print(sensor2_data[slot][0]); Serial.print(" °C");
                Serial.print(",\t\t");
                Serial.print("Humidity: "); Serial.print(sensor2_data[slot][1]); Serial.print(" %");
                Serial.println();
            }
            
            else if (sensor_type == "AHT20") {
                               
                AHT20_2.begin(&Wire1);
                sensors_event_t humidity, temp;
                AHT20_2.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
                
                sensor2_data[slot][0] = temp.temperature;
                sensor2_data[slot][1] = humidity.relative_humidity;
                
                Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.print(" °C");
                Serial.print(",\t\t");
                Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.print(" %");
            }
            
            else if (sensor_type == "SCD40" || sensor_type ==  "SCD41") {
                
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
                    sensor2_data[slot][0] = temperature;
                    sensor2_data[slot][1] = humidity;
                    sensor2_data[slot][2] = co2;
                    Serial.print("Temperature: "); Serial.print(temperature); Serial.print(" °C");
                    Serial.print("\t\t");
                    Serial.print("Humidity:"); Serial.print(humidity); Serial.print(" %");
                    Serial.print("\t\t");
                    Serial.print("Co2:"); Serial.print(co2); Serial.print(" ppm");
                }
            }
            
            else {
                Serial.print("No sensor configured.");
            }
        }

    }
}
