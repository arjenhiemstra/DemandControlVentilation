#include "read_sensors.h"

SCD4x SCD41;
DHT DHT20;

//Global variable
JsonDocument sensor_data;

//IO defintion for both I2C busses in header file
TwoWire I2C1 = TwoWire(0); //I2C1 bus
TwoWire I2C2 = TwoWire(1); //I2C2 bus

void read_bus0(void) {

    int slot;

    I2C1.begin(I2C_SDA1, I2C_SDA1);
    
    //iterate through all slots of multiplexer
    for (slot=0;slot++;slot<8) {
        
        //Select slot on I2C1 bus
        I2C1.beginTransmission(0x70);   // TCA9548A address is 0x70
        I2C1.write(1 << slot);          // send byte to select bus
        I2C1.endTransmission();
        Serial.print("TCA Port #"); 
        Serial.println(slot);
        
        //Scan all addresses on the slot
        for (uint8_t addr = 0; addr<=127; addr++) {
            I2C1.beginTransmission(addr);
            if (!I2C1.endTransmission()) {
                Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
            }
        }
    }
}





void read_SCD41(void) {

    I2C1.begin(I2C_SDA2, I2C_SDA2);

    
}



/*Sensor data structure in JSON

{
    "Bus": [
        {
            "id": 0,
            "sensors": [
                {
                    "Slot": 0,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 1,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 2,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 3,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 4,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 5,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 6,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 7,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                }
            ]
        },
        {
            "id": 1,
            "sensors": [
                {
                    "Slot": 0,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 1,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 2,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 3,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 4,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 5,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 6,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                },
                {
                    "Slot": 7,
                    "id": "valve0",
                    "location": "bathroom",
                    "Type": "DHT20",
                    "isRHsensorBR": 1,
                    "isCO2sensor": 0
                }
            ]
        }
    ]
}

*/