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

DHT20 DHT(&Wire);
Adafruit_AHTX0 AHT20;
SensirionI2CScd4x SCD4X;

//Global variables with sensor data in an 8 by 3 array of floats (8 sensors and three readings per sensor)

extern float sensor2_data;

//Make these variables global so reading config files is not required
//JsonDocument sensor_config1_JsonDoc;
//JsonDocument sensor_config2_JsonDoc;

//JsonArray wire_sensors = sensor_config1_JsonDoc["wire_sensors"].to<JsonArray>();
//JsonArray wire1_sensors = sensor_config2_JsonDoc["wire1_sensors"].to<JsonArray>();


void read_sensor_config_data(void) {

}


void read_bus0(void) {
 
    extern float sensor1_data[8][3];
    extern JsonDocument wire_sensor_data;
    extern JsonArray wire_sensors;
    /*extern JsonObject wire_sensors0; 
    extern JsonObject wire_sensors1;
    extern JsonObject wire_sensors2; 
    extern JsonObject wire_sensors3;
    extern JsonObject wire_sensors4;
    extern JsonObject wire_sensors5;
    extern JsonObject wire_sensors6;
    extern JsonObject wire_sensors7;*/

    Wire.begin(I2C_SDA1, I2C_SCL1);

    bool sensor_config_file_present;
    const char* path1 = "/sensor_config1.json";

    sensor_config_file_present = check_file_exists(path1);

    if(sensor_config_file_present == 0) {
        for (int slot=0;slot<8;slot++) {
        
            Wire.beginTransmission(TCAADDR);
            Wire.write(1 << slot);
            Wire.endTransmission();

            String sensor_type = wire_sensors[slot]["type"];
            String sensor_address = wire_sensors[slot]["address"];
            Serial.print(sensor_type);

            if (sensor_type == "DHT20") {
                vTaskDelay(2000);
                DHT.begin();
                int status = DHT.read();

                switch (status) {
                    case DHT20_OK:
                        Serial.print("OK,\t");
                        break;
                    case DHT20_ERROR_CHECKSUM:
                        Serial.print("Checksum error,\t");
                        break;
                    case DHT20_ERROR_CONNECT:
                        Serial.print("Connect error,\t");
                        break;
                    case DHT20_MISSING_BYTES:
                        Serial.print("Missing bytes,\t");
                        break;
                    case DHT20_ERROR_BYTES_ALL_ZERO:
                        Serial.print("All bytes read zero");
                        break;
                    case DHT20_ERROR_READ_TIMEOUT:
                        Serial.print("Read time out");
                        break;
                    case DHT20_ERROR_LASTREAD:
                        Serial.print("Error read too fast");
                        break;
                    default:
                        Serial.print("Unknown error,\t");
                        break;
                }
                sensor1_data[slot][0] = DHT.getTemperature();
                Serial.print(sensor1_data[slot][0]);
                Serial.print(",\t");
                sensor1_data[slot][1] = DHT.getHumidity();
                Serial.print(sensor1_data[slot][1]);
            }
            
            else if (sensor_type == "AHT20") {
                
                vTaskDelay(1000);
                AHT20.begin();
                sensors_event_t humidity, temp;
                AHT20.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
                
                sensor1_data[slot][0] = temp.temperature;
                sensor1_data[slot][1] = humidity.relative_humidity;
                
                Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
                Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
            }
            
            else if (sensor_type == "SCD40" || "SCD41") {
                
                vTaskDelay(1000);
                SCD4X.begin(Wire);
                
                uint16_t error;
                uint16_t co2 = 0;
                float temperature = 0.0f;
                float humidity = 0.0f;
                bool isDataReady = false;

                error = SCD4X.readMeasurement(co2, temperature, humidity);
                if (error) {
                    Serial.print("Error trying to execute readMeasurement(): ");
                } else if (co2 == 0) {
                    Serial.println("Invalid sample detected, skipping.");
                } else {
                    sensor1_data[slot][0] = temperature;
                    sensor1_data[slot][1] = humidity;
                    sensor1_data[slot][2] = co2;
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

    //Serial.print("\nScanning bus0\n");

    //JsonDocument is a global variable but is only filled with data when the button pressed to create a config file
    //so somewhere at startup of the processor the config file should be read and put into the global variable  
    //extern JsonDocument valve_control_data;

    //iterate through all slots of multiplexer
    /*
    for (int slot =0;slot<8;slot++) {

        //Select slot on I2C1 bus
        Serial.print("\n");
        Wire.beginTransmission(0x70);   // TCA9548A address is 0x70
        Wire.write(1 << slot);          // send byte to select bus
        Wire.endTransmission();
        Serial.print("TCA Port #"); 
        Serial.println(slot);

        //Scan all addresses on the slot
        for (uint8_t addr = 0; addr<=127; addr++) {
            Wire.beginTransmission(addr);
            if (!Wire.endTransmission()) {
                Serial.print("Found I2C 0x");  
                Serial.println(addr,HEX);
            }
        }
    }*/

}

void read_bus1(void) {

    //Wire1.begin(I2C_SDA2, I2C_SCL2);

    //Serial.print("\nScanning bus1\n");

    //iterate through all slots of multiplexer
    /*
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
    }*/

}

