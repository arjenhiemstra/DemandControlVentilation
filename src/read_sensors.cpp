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

//SCD4x SCD41;
//DHT DHT20;

//Global variables with sensor data in an 8 by 3 array of floats (8 sensors and three readings per sensor)
float sensor1_data[8][3] = { 0 };
float sensor2_data[8][3] = { 0 };

//Make these variables global so reading config files is not required
//JsonDocument sensor_config1_JsonDoc;
//JsonDocument sensor_config2_JsonDoc;

//JsonArray wire_sensors = sensor_config1_JsonDoc["wire_sensors"].to<JsonArray>();
//JsonArray wire1_sensors = sensor_config2_JsonDoc["wire1_sensors"].to<JsonArray>();


void read_sensor_config_data(void) {

}


void read_bus0(void) {
 
    Wire.begin(I2C_SDA1, I2C_SCL1);

    Serial.print("\nScanning bus0\n");

    //JsonDocument is a global variable but is only filled with data when the button pressed to create a config file
    //so somewhere at startup of the processor the config file should be read and put into the global variable  
    extern JsonDocument valve_control_data;

    //iterate through all slots of multiplexer
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
    }

}

void read_bus1(void) {

    Wire1.begin(I2C_SDA2, I2C_SCL2);

    Serial.print("\nScanning bus1\n");

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

}

