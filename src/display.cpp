#include "display.h"

LiquidCrystal_I2C lcd(LCDADDR, LCD_COLUMNS, LCD_ROWS);

void display_sensors(void) {

    /*
        0 	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15  16  17  18  19
       -------------------------------------------------------------------------------
    0 |	B	u	s	:	0		S	e	n	s	o	r	:	1	1	
    1 |	T	e	m	p	:	2	2	,	8	7	°	C				
    2 |	H	u	m	i	d	i	t	y	:	4	7	%				
    3 |	C	O	2	:	1	2	0	0	p	p	m					
    */

    int slot = 0;
    int bus = 0;

    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);     //Display is on Wire1 bus

    lcd.init();
    lcd.backlight();
    lcd.noAutoscroll();
    lcd.noCursor();

    //Copy array to local array with active mutex an then run slow display function without mutex
    float temp_sensor_data[2][8][3];

    if (sensor_variable_mutex != NULL) {
        if(xSemaphoreTake(sensor_variable_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            vTaskDelay(100);
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 8; j++) {
                    for (int k = 0; k < 3; k++) {
                        temp_sensor_data[i][j][k] = sensor_data[i][j][k];
                    }
                }
            }
            vTaskDelay(100);
            xSemaphoreGive(sensor_variable_mutex);
        }
    }
        
    for (int bus=0;bus<2;bus++)
    {
        for (int slot=0;slot<8;slot++) {
                    
            lcd.setCursor(0, 0);
            lcd.print("Bus:");
            lcd.print(bus);
            lcd.print(" Sensor:");
            lcd.print(slot);
            
            //Only display measurments if sensor is present, i.e. if temperature measurement is not zero
            if (temp_sensor_data[bus][slot][0] != 0) {
                lcd.setCursor(0, 1);
                lcd.print("Temperature: ");
                lcd.print(temp_sensor_data[bus][slot][0]);
                lcd.print((char)223);
                lcd.print("C");

                lcd.setCursor(0, 2);
                lcd.print("Humidity: ");
                lcd.print(temp_sensor_data[bus][slot][1]);
                lcd.print("%");

                //Only displat CO2 is sensor has this measurement
                if (temp_sensor_data[bus][slot][2] != 0) {
                    lcd.setCursor(0, 3);
                    lcd.print("CO2: ");
                    lcd.print(temp_sensor_data[bus][slot][2]);
                    lcd.print("ppm");
                }

                //Refresh sensor data every 5 seconds and clear display
                vTaskDelay(5000);
                lcd.clear();
            }
            //No sensor connected to port
            else {
                lcd.setCursor(0, 2);
                lcd.print("No sensor");
                vTaskDelay(5000);
                lcd.clear();
            }
        }
    }
    lcd.clear();
}

void display_valve_positions(void) {

    /* Display layout

            0 	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15  16  17  18  19  20
            -----------------------------------------------------------------------------------
    0   |	v   0	:	i	i		    v	1	:	i	i			v   2	:	i	i
    1   |	v   3	:	i	i		    v	4	:	i	i			v   5	:	i	i
    2   |	v   6	:	i   i		    v	7	:	i	i			v   8	:	i	i
    3   |	v   9	:	i   i		v   1	0	:	i	i		v   1   1	:	i	i
    
    */
      
    const char* path = "/json/valvepositions.json";
    bool status_file_present;
    String json;
    JsonDocument doc;

    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);     //Display is on Wire1 bus
    lcd.init();

    lcd.clear();
    lcd.backlight();
    
    status_file_present = check_file_exists(path);

    if (valve_position_file_mutex != NULL) {
        if(xSemaphoreTake(valve_position_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
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

                lcd.setCursor(0,0);
                lcd.print("v0:");
                lcd.print(valve0_pos);
                lcd.setCursor(7,0);
                lcd.print("v1:");
                lcd.print(valve1_pos);
                lcd.setCursor(14,0);
                lcd.print("v2:");
                lcd.print(valve2_pos);
                
                lcd.setCursor(0,1);
                lcd.print("v3:");
                lcd.print(valve3_pos);
                lcd.setCursor(7,1);
                lcd.print("v4:");
                lcd.print(valve4_pos);
                lcd.setCursor(14,1);
                lcd.print("v5:");
                lcd.print(valve5_pos);
                
                lcd.setCursor(0,2);
                lcd.print("v6:");
                lcd.print(valve6_pos);
                lcd.setCursor(7,2);
                lcd.print("v7:");
                lcd.print(valve7_pos);
                lcd.setCursor(14,2);
                lcd.print("v8:");
                lcd.print(valve8_pos);

                lcd.setCursor(0,3);
                lcd.print("v9:");
                lcd.print(valve9_pos);
                lcd.setCursor(6,3);
                lcd.print("v10:");
                lcd.print(valve10_pos);
                lcd.setCursor(13,3);
                lcd.print("v11:");
                lcd.print(valve11_pos);

            }
            xSemaphoreGive(valve_position_file_mutex);
            vTaskDelay(5000);
            lcd.clear();
            lcd.noBacklight(); 
        }
    }
}

void display_time_and_date(void) {

    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);     //Display is on Wire1 bus
    lcd.init();

    lcd.clear();
    lcd.backlight();
    
    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            lcd.setCursor(0,0);
            lcd.print(dayOfWeek);

            lcd.setCursor(0,1);
            lcd.print(dayStr);
            lcd.print("-");
            lcd.print(monthStr);
            lcd.print("-");
            lcd.print(yearStr);
            
            lcd.setCursor(0,2);
            lcd.print(hourStr);
            lcd.print(":");
            lcd.print(minuteStr);
            lcd.print(":");
            lcd.print(secondStr);  

            xSemaphoreGive(date_time_mutex);       
        }
        vTaskDelay(5000);
        lcd.clear();
    }
}