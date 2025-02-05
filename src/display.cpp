#include "display.h"

#include "read_sensors.h"

void display(void) {

    int lcd_columns = 16;
    int lcd_rows = 4;
    int slot = 0;
    int bus = 0;

    LiquidCrystal_I2C lcd(LCDADDR, lcd_columns, lcd_rows);

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);     //Display is on Wire bus

    lcd.init();
    lcd.backlight();                            //LCD starts with backlight on so toggle off until needed

    xSemaphoreTake(sensor_variable_mutex, portMAX_DELAY);

    //Sensor bus0
    for (int slot=0;slot<8;slot++) {
        
        bus = 0;

        //Clear display and turn on backlight 
        lcd.backlight();
        lcd.clear();

        vTaskDelay(2000);

        lcd.setCursor(0, 0);
        lcd.print("Bus: "); Serial.print(bus); Serial.print("Sensor: "); Serial.print(slot);
        
        lcd.setCursor(0, 1);
        lcd.print("Temperature: ");
        lcd.print(sensor1_data[slot][0]);
        lcd.print(" °C");

        lcd.setCursor(0, 2);
        lcd.print("Humidity: ");
        lcd.print(sensor1_data[slot][1]);
        lcd.print(" °C");

        lcd.setCursor(0, 3);
        lcd.print("CO2: ");
        lcd.print(sensor1_data[slot][2]);
        lcd.print(" ppm");

        lcd.backlight();
        lcd.clear();
    }
    
    //Sensor bus1
    for (int slot=0;slot<8;slot++) {
        
        bus = 1;

        //Clear display and turn on backlight 
        lcd.backlight();
        lcd.clear();

        vTaskDelay(2000);

        lcd.setCursor(0, 0);
        lcd.print("Bus:"); Serial.print(bus); Serial.print("Sensor:"); Serial.print(slot);
        
        lcd.setCursor(0, 1);
        lcd.print("Temperature: ");
        lcd.print(sensor2_data[slot][0]);
        lcd.print(" °C");

        lcd.setCursor(0, 2);
        lcd.print("Humidity: ");
        lcd.print(sensor2_data[slot][1]);
        lcd.print(" °C");

        lcd.setCursor(0, 3);
        lcd.print("CO2: ");
        lcd.print(sensor2_data[slot][2]);
        lcd.print(" ppm");

        lcd.backlight();
        lcd.clear();
    }
    
    xSemaphoreGive(sensor_variable_mutex);
}