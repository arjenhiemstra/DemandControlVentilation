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
//#include <SensirionI2cScd4x.h>

DHT20 DHT1(&Wire);
DHT20 DHT2(&Wire1);
Adafruit_AHTX0 AHT20_1;
Adafruit_AHTX0 AHT20_2;
SensirionI2cScd4x SCD4X_1;
SensirionI2cScd4x SCD4X_2;

#ifdef NO_ERROR
#undef NO_ERROR
#endif
#define NO_ERROR 0

//SCD4x SCD4X_1;
//SCD4x SCD4X_2;

void read_bus0(void) {
 
    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);

    bool sensor_config_file_present;
    const char* path1 = "/sensor_config1.json";

    sensor_config_file_present = check_file_exists(path1);
 
    if(sensor_config_file_present == 1) {
        for (int slot=0;slot<8;slot++) {

            String sensor = "wire_sensor" + String(slot);
            Serial.print("\nWire sensors, slot ");
            Serial.print(slot);
                    
            Wire.beginTransmission(TCAADDR);
            Wire.write(1 << slot);
            Wire.endTransmission();

            String sensor_type = wire_sensor_data[sensor]["type"];
            String sensor_address = wire_sensor_data[sensor]["address"];
            Serial.print("\nSensor type: ");
            Serial.print(sensor_type);
            Serial.print("\n");

            if (sensor_type == "DHT20") {
                
                DHT1.begin();
                vTaskDelay(2000);
                int status = DHT1.read();
                
                sensor1_data[slot][0] = DHT1.getTemperature();
                sensor1_data[slot][1] = DHT1.getHumidity();

                Serial.print("Temperature: "); Serial.print(sensor1_data[slot][0]); Serial.print("degrC");
                Serial.print(",\t");
                Serial.print("Humidity: "); Serial.print(sensor1_data[slot][1]); Serial.print("%");
            }
            
            else if (sensor_type == "AHT20") {
                               
                AHT20_1.begin();
                vTaskDelay(1000);
                sensors_event_t humidity, temp;
                AHT20_1.getEvent(&humidity, &temp);
                
                sensor1_data[slot][0] = temp.temperature;
                sensor1_data[slot][1] = humidity.relative_humidity;
                
                Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.print("degrC");
                Serial.print(",\t");
                Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.print("%");
            }
            
            else if (sensor_type == "SCD40" || sensor_type == "SCD41") {
             
                SCD4X_1.begin(Wire, SCD41_I2C_ADDR_62);

                static char errorMessage[64];
                static int16_t error;
                uint64_t serialNumber = 0;
                uint16_t co2 = 0;
                float temperature = 0.0f;
                float humidity = 0.0f;
                vTaskDelay(300);

                // Ensure sensor is in clean state
                error = SCD4X_1.wakeUp();
                if (error != NO_ERROR) {
                    Serial.print("Error trying to execute wakeUp(): ");
                    errorToString(error, errorMessage, sizeof errorMessage);
                    Serial.println(errorMessage);
                }
                error = SCD4X_1.stopPeriodicMeasurement();
                if (error != NO_ERROR) {
                    Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
                    errorToString(error, errorMessage, sizeof errorMessage);
                    Serial.println(errorMessage);
                }
                error = SCD4X_1.reinit();
                if (error != NO_ERROR) {
                    Serial.print("Error trying to execute reinit(): ");
                    errorToString(error, errorMessage, sizeof errorMessage);
                    Serial.println(errorMessage);
                }
                // Read out information about the sensor
                error = SCD4X_1.getSerialNumber(serialNumber);
                if (error != NO_ERROR) {
                    Serial.print("Error trying to execute getSerialNumber(): ");
                    errorToString(error, errorMessage, sizeof errorMessage);
                    Serial.println(errorMessage);
                    return;
                }
                Serial.print("serial number: 0x");
                Serial.print(serialNumber);
                Serial.println();
              
                error = SCD4X_1.wakeUp();
                if (error != NO_ERROR) {
                    Serial.print("Error trying to execute wakeUp(): ");
                    errorToString(error, errorMessage, sizeof errorMessage);
                    Serial.println(errorMessage);
                    return;
                }
                // Ignore first measurement after wake up.
                error = SCD4X_1.measureSingleShot();
                if (error != NO_ERROR) {
                    Serial.print("Error trying to execute measureSingleShot(): ");
                    errorToString(error, errorMessage, sizeof errorMessage);
                    Serial.println(errorMessage);
                    return;
                }
                // Perform single shot measurement and read data.
                error = SCD4X_1.measureAndReadSingleShot(co2, temperature,humidity);
                if (error != NO_ERROR) {
                    Serial.print("Error trying to execute measureAndReadSingleShot(): ");
                    errorToString(error, errorMessage, sizeof errorMessage);
                    Serial.println(errorMessage);
                    return;
                }
                
                sensor1_data[slot][0] = temperature;
                sensor1_data[slot][1] = humidity;
                sensor1_data[slot][2] = co2;
                                
                Serial.print("Temperature: "); Serial.print(temperature); Serial.print("degrees C");
                Serial.print(", \t");
                Serial.print("Humidity: "); Serial.println(humidity); Serial.print("%");
                Serial.print(", \t");
                Serial.print("CO2: "); Serial.print(co2); Serial.print("ppm");
            }
            
            else {
                Serial.println("No sensor configured.");
            }
        }

    }
}

void read_bus1(void) {
 
    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);
    SCD4X_2.begin(Wire1, SCD41_I2C_ADDR_62);
    vTaskDelay(1000);
    
    bool sensor_config_file_present;
    const char* path = "/sensor_config2.json";

    sensor_config_file_present = check_file_exists(path);
 
    if(sensor_config_file_present == 1) {
        for (int slot=0;slot<8;slot++) {

            String sensor = "wire1_sensor" + String(slot);
            Serial.print("\nWire1 sensors, slot ");
            Serial.print(slot);
                    
            Wire1.beginTransmission(TCAADDR);
            Wire1.write(1 << slot);
            Wire1.endTransmission();

            String sensor_type = wire1_sensor_data[sensor]["type"];
            String sensor_address = wire1_sensor_data[sensor]["address"];
            Serial.print("\nSensor type: ");
            Serial.print(sensor_type);
            Serial.print("\n");

            if (sensor_type == "DHT20") {
                
                DHT2.begin();
                vTaskDelay(2000);
                int status = DHT2.read();
                
                sensor2_data[slot][0] = DHT2.getTemperature();
                sensor2_data[slot][1] = DHT2.getHumidity();
                Serial.print(sensor2_data[slot][0]);
                Serial.print(",\t");
                Serial.print(sensor2_data[slot][1]);
            }
            
            else if (sensor_type == "AHT20") {
                               
                AHT20_2.begin(&Wire1);
                vTaskDelay(1000);
                sensors_event_t humidity, temp;
                AHT20_2.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
                
                sensor2_data[slot][0] = temp.temperature;
                sensor2_data[slot][1] = humidity.relative_humidity;
                
                Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.print(" degrees C");
                Serial.print(",\t");
                Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.print("% rH");
            }
            
            else if (sensor_type == "SCD40" || sensor_type ==  "SCD41") {
                
                SCD4X_2.startPeriodicMeasurement();
                vTaskDelay(5200);
                
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
                    Serial.print("Co2:");
                    Serial.print(co2);
                    Serial.print("\t");
                    Serial.print("Temperature:");
                    Serial.print(temperature);
                    Serial.print("\t");
                    Serial.print("Humidity:");
                    Serial.println(humidity);
                }
            }
            
            else {
                Serial.print("\n\nSensor not found");
            }
        }

    }
}


/*void read_bus1(void) {
    
    //DHT20 on slot 0
    Wire1.begin(I2C_SDA2, I2C_SCL2);
    Wire1.beginTransmission(TCAADDR);
    Wire1.write(1 << 0);
    Wire1.endTransmission();
    vTaskDelay(2000);
    DHT20 DHT2(&Wire1);
    DHT2.begin();
    int status = DHT2.read();
    
    Serial.print("\n");
    sensor2_data[0][0] = DHT2.getTemperature();
    Serial.print(sensor2_data[0][0]);
    Serial.print(",\t");
    sensor2_data[0][1] = DHT2.getHumidity();
    Serial.print(sensor2_data[0][1]);

    //AHT20 on slot1
    Wire1.begin(I2C_SDA2, I2C_SCL2);
    Wire1.beginTransmission(TCAADDR);
    Wire1.write(1 << 1);
    Wire1.endTransmission();
    vTaskDelay(1000);
    Adafruit_AHTX0 AHT20;
    AHT20.begin(&Wire1);
    vTaskDelay(1000);
    sensors_event_t humidity, temp;
    AHT20.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
    
    sensor2_data[1][0] = temp.temperature;
    sensor2_data[1][1] = humidity.relative_humidity;
    
    Serial.print("\nTemperature: "); 
    Serial.print(temp.temperature); 
    Serial.print(" C");
    Serial.print(",\t");
    Serial.print("Humidity: "); 
    Serial.print(humidity.relative_humidity); 
    Serial.print(" %");
    

    
    bool sensor_config_file_present;
    const char* path2 = "/sensor_config2.json";

    sensor_config_file_present = check_file_exists(path2);
 
    if(sensor_config_file_present == 1) {
        for (int slot=0;slot<8;slot++) {

            String sensor = "wire1_sensor" + String(slot);
            Wire1.beginTransmission(TCAADDR);
            Wire1.write(1 << slot);
            Wire1.endTransmission();

            String sensor_type = wire1_sensor_data[sensor]["type"];
            String sensor_address = wire1_sensor_data[sensor]["address"];
            Serial.print("\n\n");
            Serial.print(sensor_type);
            Serial.print("\n\n");

            if (sensor_type == "DHT20") {
                vTaskDelay(2000);
                DHT20 DHT2(&Wire1);
                DHT2.begin();
                int status = DHT2.read();
    
                Serial.print("\n");
                sensor2_data[0][0] = DHT2.getTemperature();
                Serial.print(sensor2_data[0][0]);
                Serial.print(",\t");
                sensor2_data[0][1] = DHT2.getHumidity();
                Serial.print(sensor2_data[0][1]);
            }
            
            else if (sensor_type == "AHT20") {
                
                vTaskDelay(1000);
                Adafruit_AHTX0 AHT20;
                AHT20.begin(&Wire1);
                vTaskDelay(1000);
                sensors_event_t humidity, temp;
                AHT20.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
                    
                sensor2_data[1][0] = temp.temperature;
                sensor2_data[1][1] = humidity.relative_humidity;
                    
                Serial.print("\nTemperature: "); 
                Serial.print(temp.temperature); 
                Serial.print(" C");
                Serial.print(",\t");
                Serial.print("Humidity: "); 
                Serial.print(humidity.relative_humidity); 
                Serial.print(" %");
            }
            
            else if (sensor_type == "SCD40" || "SCD41") {
                
                SCD4X_2.begin(Wire1);
                
                uint16_t error;
                uint16_t co2 = 0;
                float temperature = 0.0f;
                float humidity = 0.0f;
                bool isDataReady = false;

                vTaskDelay(2000);

                error = SCD4X_2.readMeasurement(co2, temperature, humidity);
                if (error) {
                    Serial.print("Error trying to execute readMeasurement(): ");
                } else if (co2 == 0) {
                    Serial.println("Invalid sample detected, skipping.");
                } else {
                    sensor2_data[slot][0] = temperature;
                    sensor2_data[slot][1] = humidity;
                    sensor2_data[slot][2] = co2;
                    Serial.print("Co2:");
                    Serial.print(co2);
                    Serial.print("\t");
                    Serial.print("Temperature:");
                    Serial.print(temperature);
                    Serial.print("\t");
                    Serial.print("Humidity:");
                    Serial.println(humidity);
                }
            }
            
            else {
                Serial.print("\n\nSensor not found");
            }
        }

    }
}*/



/*void read_bus1(void) {

    //Wire1.begin(I2C_SDA2, I2C_SCL2);

    //Serial.print("\nScanning bus1\n");

    //iterate through all slots of multiplexer
    
    for (int slot =0;slot<8;slot++) {

        //Select slot on I2C1 bus
        Serial.print("\n");
        Wire1.beginTransmission(0x70);   // TCA9548A address is 0x70
        Wire1.write(1 << slot);          // send byte to select bus
        Wire1.endTransmission();
        Serial.print("TCA Port #"); 
        Serial.println(slot);

        //Scan all addresses on the slot
        for (uint8_t addr = 0; addr<=127; addr++) {
            Wire1.beginTransmission(addr);
            if (!Wire1.endTransmission()) {
                Serial.print("Found I2C 0x");  
                Serial.println(addr,HEX);
            }
        }
    }

}*/

