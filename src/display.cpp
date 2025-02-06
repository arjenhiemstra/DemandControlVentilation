#include "display.h"

int lcd_columns = 16;
int lcd_rows = 4;

LiquidCrystal_I2C lcd(LCDADDR, lcd_columns, lcd_rows);

void display_sensors(void) {

    /*
        0 	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15
       ---------------------------------------------------------------
    0 |	B	u	s	:	0		S	e	n	s	o	r	:	1	1	
    1 |	T	e	m	p	:	2	2	,	8	7	°	C				
    2 |	H	u	m	i	d	i	t	y	:	4	7	%				
    3 |	C	O	2	:	1	2	0	0	p	p	m					
    */

    int slot = 0;
    int bus = 0;

    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);     //Display is on Wire1 bus

    lcd.init();
    lcd.backlight();                            //LCD starts with backlight on so toggle off until needed
    lcd.print("Hello World");

    /*
    xSemaphoreTake(sensor_variable_mutex, portMAX_DELAY);  
   
    for (int bus=0;bus<2;bus++)
    {
        for (int slot=0;slot<8;slot++) {
            
            Serial.print(sensor_data[bus][slot][0]);
            Serial.println();
            Serial.print(sensor_data[bus][slot][1]);
            Serial.println();
            
            //Clear display and turn on backlight 
            lcd.backlight();
            lcd.clear();

            //Refresh sensor data every 2 seconds
            vTaskDelay(2000);

            lcd.setCursor(0, 0);
            lcd.print("Bus:"); Serial.print(bus); Serial.print(" Sensor:"); Serial.print(slot);
            
            lcd.setCursor(0, 1);
            lcd.print("Temperature:");
            lcd.print(sensor_data[bus][slot][0]);
            lcd.print("°C");

            lcd.setCursor(0, 2);
            lcd.print("Humidity:");
            lcd.print(sensor_data[bus][slot][1]);
            lcd.print("%");

            lcd.setCursor(0, 3);
            lcd.print("CO2:");
            lcd.print(sensor_data[bus][slot][2]);
            lcd.print("ppm");
        }
    }

    lcd.backlight(); //backlight off
    lcd.clear();
   
    xSemaphoreGive(sensor_variable_mutex);*/
}

void display_valve_positions(void) {

    /*
        0 	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15
       ---------------------------------------------------------------
    0 |	0	:	2	4			1	:	i	i			2	:	i	i
    1 |	3	:	1	2			4	:	i	i			5	:	i	i
    2 |	6	:	9				7	:	i	i			8	:	i	i
    3 |	9	:	7			1	0	:	i	i		1	1	:	i	i
    */
      
   /*
    const char* path = "/valvepositions.json";
    bool status_file_present;
    String json;
    JsonDocument doc;

    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);     //Display is on Wire bus
    lcd.init();

    lcd.clear();
    lcd.backlight();
    
    vTaskDelay(2000);                           //Wait for two seconds

    xSemaphoreTake(valve_position_mutex, portMAX_DELAY);
    status_file_present = check_file_exists(path);

    if (status_file_present == 1) {

        json = read_config_file(path);
        deserializeJson(doc, json);
  
        String valve0_pos = doc[String("valve0")];
        String valve1_pos = doc[String("valve1")];
        String valve2_pos = doc[String("valve2")];
        String valve3_pos = doc[String("valve3")];
        String valve4_pos = doc[String("valve4")];
        String valve5_pos = doc[String("valve5")];
        String valve6_pos = doc[String("valve6")];
        String valve7_pos = doc[String("valve7")];
        String valve8_pos = doc[String("valve8")];
        String valve9_pos = doc[String("valve9")];
        String valve10_pos = doc[String("valve10")];
        String valve11_pos = doc[String("valve11")];

        lcd.setCursor(0, 0);
        lcd.print("v0:");
        lcd.print(valve0_pos);
        lcd.setCursor(0, 6);
        lcd.print("v1:");
        lcd.print(valve1_pos);
        lcd.setCursor(0, 12);
        lcd.print("v2:");
        lcd.print(valve2_pos);
        
        lcd.setCursor(1, 0);
        lcd.print("v3:");
        lcd.print(valve3_pos);
        lcd.setCursor(0, 6);
        lcd.print("v4:");
        lcd.print(valve4_pos);
        lcd.setCursor(0, 12);
        lcd.print("v5:");
        lcd.print(valve5_pos);
        
        lcd.setCursor(2, 0);
        lcd.print("v6:");
        lcd.print(valve6_pos);
        lcd.setCursor(0, 6);
        lcd.print("v7:");
        lcd.print(valve7_pos);
        lcd.setCursor(0, 12);
        lcd.print("v8:");
        lcd.print(valve8_pos);

        lcd.setCursor(3, 0);
        lcd.print("v9:");
        lcd.print(valve9_pos);
        lcd.setCursor(0, 5);
        lcd.print("v10:");
        lcd.print(valve10_pos);
        lcd.setCursor(0, 11);
        lcd.print("v11:");
        lcd.print(valve11_pos);

    }

    vTaskDelay(2000);                           //Show data for two seconds
    lcd.clear();
    lcd.backlight();                            //Backlight off

    xSemaphoreGive(valve_position_mutex);
    */
}

