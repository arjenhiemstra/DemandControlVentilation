#include "sensors.h"

SCD4x SCD41;
DHT DHT20;

void TCA9548A(uint8_t bus){
    Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
    Wire.write(1 << bus);          // send byte to select bus
    Wire.endTransmission();
    Serial.print(bus);
}




void read_DHT20(void) {

    Wire.begin(I2C_SDA2, I2C_SCL2);

}





void read_SCD41(void) {

    Wire.begin(I2C_SDA2, I2C_SCL2);
    
}


