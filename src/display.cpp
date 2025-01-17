#include "display.h"

void display(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1);

    Serial.print("\nScanning Wire\n");

    //Scan all addresses on the slot
    for (uint8_t addr = 0; addr<=127; addr++) {
        Wire.beginTransmission(addr);
        if (!Wire.endTransmission()) {
            Serial.print("Found I2C 0x");  
            Serial.println(addr,HEX);
        }
    }


}