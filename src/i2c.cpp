#include "i2c.h"

LiquidCrystal_I2C lcd(LCDADDR, LCD_COLUMNS, LCD_ROWS);

void read_sensors(void) {
 
    bool sensor_config_file_present = 0;

    //const char* path;
    float temp_sensor_data[2][8][3]= {0};
    int bus = 0;

    String sensor_tmp = "";
    String sensor_type_temp = "";
    String sensor_address_temp = "";
        
    for(bus=0;bus<2;bus++) {
        
        if (bus==0) {
            Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
            const char* path1 = "/json/sensor_config1.json";
            sensor_config_file_present = check_file_exists(path1);
        }
        if (bus==1) {
            Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);
            const char* path2 = "/json/sensor_config2.json";
            sensor_config_file_present = check_file_exists(path2);
        }
        
        if(sensor_config_file_present == 1) {
            for (int slot=0;slot<8;slot++) {
                                
                if (bus==0) {
                    String sensor = "wire_sensor" + String(slot);
                    String sensor_type = wire_sensor_data[sensor]["type"];
                    String sensor_address = wire_sensor_data[sensor]["address"];
                    sensor_tmp = sensor;
                    sensor_type_temp= sensor_type;
                    sensor_address_temp = sensor_address;
                    Wire.beginTransmission(TCAADDR);
                    Wire.write(1 << slot);
                    Wire.endTransmission();
                }
                
                if (bus==1) {
                    String sensor = "wire1_sensor" + String(slot);
                    String sensor_type = wire1_sensor_data[sensor][String("type")];
                    String sensor_address = wire1_sensor_data[sensor][String("address")];
                    sensor_tmp = sensor;
                    sensor_type_temp= sensor_type;
                    sensor_address_temp = sensor_address;
                    Wire1.beginTransmission(TCAADDR);
                    Wire1.write(1 << slot);
                    Wire1.endTransmission();
                }
                if (sensor_type_temp == "DHT20" || sensor_type_temp == "AHT20") {
                    
                    if (bus==0) {
                        DHT20 DHT1(&Wire);
                        DHT1.begin();
                        //int status = DHT1.read(); 
                        DHT1.read();                  

                        temp_sensor_data[bus][slot][0] = DHT1.getTemperature();
                        temp_sensor_data[bus][slot][1] = DHT1.getHumidity();
                        Wire.endTransmission();
                    }
                    if (bus==1) {
                        DHT20 DHT2(&Wire1);
                        DHT2.begin();
                        //int status = DHT2.read();
                        DHT2.read();

                        temp_sensor_data[bus][slot][0] = DHT2.getTemperature();
                        temp_sensor_data[bus][slot][1] = DHT2.getHumidity();
                        Wire1.endTransmission();
                    }                   
                }
                
                /*
                else if (sensor_type_temp == "AHT20") {     
                    if (bus==0) {
                        
                        Adafruit_AHTX0 AHT20_1;
                        sensors_event_t humidity, temperature;

                        AHT20_1.begin();
                        AHT20_1.getEvent(&humidity, &temperature);
                        
                        temp_sensor_data[bus][slot][0] = temperature.temperature;
                        temp_sensor_data[bus][slot][1] = humidity.relative_humidity;
                        
                        Wire.endTransmission();

                        DFRobot_AHT20 AHT20_1;
                        AHT20_1.begin();
                        temp_sensor_data[bus][slot][0] = AHT20_1.getTemperature_C();
                        temp_sensor_data[bus][slot][1] = AHT20_1.getHumidity_RH();
                        Wire.endTransmission();

                    }
                    if (bus==1) {
                        Adafruit_AHTX0 AHT20_2;
                        sensors_event_t humidity, temperature;

                        AHT20_2.begin();
                        AHT20_2.getEvent(&humidity, &temperature);
                        
                        temp_sensor_data[bus][slot][0] = temperature.temperature;
                        temp_sensor_data[bus][slot][1] = humidity.relative_humidity;
                        
                        Wire1.endTransmission();

                        DFRobot_AHT20 AHT20_2;
                        AHT20_2.begin();
                        temp_sensor_data[bus][slot][0] = AHT20_2.getTemperature_C();
                        temp_sensor_data[bus][slot][1] = AHT20_2.getHumidity_RH();
                        Wire.endTransmission();
                    }                   
                }*/
                
                else if (sensor_type_temp == "SCD40" || sensor_type_temp == "SCD41") {
                        
                    if (bus==0) {
                        SensirionI2cScd4x SCD4X_1;
                        SCD4X_1.begin(Wire, SCD41_I2C_ADDR_62);
                        SCD4X_1.startPeriodicMeasurement();
                    
                        uint16_t error;
                        uint16_t co2 = 0;
                        float temperature = 0.0f;
                        float humidity = 0.0f;
                        //bool isDataReady = false;
        
                        error = SCD4X_1.readMeasurement(co2, temperature, humidity);
                        if (error) {
                            Serial.print("Error trying to execute readMeasurement(): ");
                        } 
                        else if (co2 == 0) {
                            Serial.println("Invalid sample detected, skipping.");
                        } 
                        else {
                            temp_sensor_data[bus][slot][0] = temperature;
                            temp_sensor_data[bus][slot][1] = humidity;
                            temp_sensor_data[bus][slot][2] = co2;
                        }
                        Wire.endTransmission();
                    }
                    if (bus==1) {
                        SensirionI2cScd4x SCD4X_2;
                        SCD4X_2.begin(Wire1, SCD41_I2C_ADDR_62);
                        SCD4X_2.startPeriodicMeasurement();
                    
                        uint16_t error;
                        uint16_t co2 = 0;
                        float temperature = 0.0f;
                        float humidity = 0.0f;
                        //bool isDataReady = false;
        
                        error = SCD4X_2.readMeasurement(co2, temperature, humidity);
                        if (error) {
                            Serial.print("Error trying to execute readMeasurement(): ");
                        } 
                        else if (co2 == 0) {
                            Serial.println("Invalid sample detected, skipping.");
                        } 
                        else {
                            temp_sensor_data[bus][slot][0] = temperature;
                            temp_sensor_data[bus][slot][1] = humidity;
                            temp_sensor_data[bus][slot][2] = co2;
                        }
                        Wire1.endTransmission();
                    }
                }
                else {
                    temp_sensor_data[bus][slot][0] = 0.00;
                    temp_sensor_data[bus][slot][1] = 0.00;
                    temp_sensor_data[bus][slot][2] = 0.00;
                }
            }
        }
    }

    vTaskDelay(200);
   
    //check if transmission is properly done, if not
    byte wire_status;
    byte wire1_status;
    
    wire_status = Wire.endTransmission();
    wire1_status = Wire1.endTransmission();
    
    if (wire_status == 0x00 && wire1_status == 0x00)
    {
        if(sensor_queue !=NULL) {
            //if (xQueueSendToFront(sensor_queue, &temp_sensor_data, (TickType_t) 100) != pdPASS){
            if (xQueueOverwrite(sensor_queue, &temp_sensor_data) != pdPASS){
                Serial.println("\nNo queue space for sending data to queue.\n");
            }
        }
        else {
            Serial.print("Send - Queue handle is NULL");
        }
    }
    else {
        Serial.print("I2C communication problem");
    }
}

void display_sensors(void) {

    /*
        0 	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15  16  17  18  19
       -------------------------------------------------------------------------------
    0 |	B	u	s	:	0		S	e	n	s	o	r	:	1	1	
    1 |	T	e	m	p	:	2	2	,	8	7	°	C				
    2 |	H	u	m	i	d	i	t	y	:	4	7	%				
    3 |	C	O	2	:	1	2	0	0	p	p	m					
    */

    float queue_sensor_data[2][8][3];        //local variable to store sensor data from queue
    //int slot = 0;
    //int bus = 0;

    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);     //Display is on Wire1 bus

    lcd.init();
    lcd.noAutoscroll();
    lcd.noCursor();   

    if (xQueuePeek(sensor_queue, &queue_sensor_data, 0 ) == pdTRUE) {
        for (int bus=0;bus<2;bus++) {
            for (int slot=0;slot<8;slot++) {
                        
                lcd.setCursor(0, 0);
                lcd.print("Bus:");
                lcd.print(bus);
                lcd.print(" Sensor:");
                lcd.print(slot);
                
                //Only display measurements if sensor is present, i.e. if temperature measurement is not zero
                if (queue_sensor_data[bus][slot][0] != 0) {
                    lcd.setCursor(0, 1);
                    lcd.print("Temperature: ");
                    lcd.print(queue_sensor_data[bus][slot][0]);
                    lcd.print((char)223);
                    lcd.print("C");

                    lcd.setCursor(0, 2);
                    lcd.print("Humidity: ");
                    lcd.print(queue_sensor_data[bus][slot][1]);
                    lcd.print("%");

                    //Only displat CO2 is sensor has this measurement
                    if (queue_sensor_data[bus][slot][2] != 0) {
                        lcd.setCursor(0, 3);
                        lcd.print("CO2: ");
                        lcd.print(queue_sensor_data[bus][slot][2]);
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
    }
    Wire1.endTransmission();
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
   
    status_file_present = check_file_exists(path);

    if (valve_position_file_mutex != NULL) {
        if(xSemaphoreTake(valve_position_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            if (status_file_present == 1) {

                json = read_config_file(path);
                deserializeJson(doc, json);
            }
            xSemaphoreGive(valve_position_file_mutex);
        }
    }
            
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
    vTaskDelay(5000);
    lcd.clear();
    Wire1.endTransmission();
}

void display_time_and_date(void) {

 /*
        0 	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15  16  17  18  19
       -------------------------------------------------------------------------------
    0 |	W   e   d   n   e   s   d   a   y       3   1   -   1   2   -   2   0   2   5
    1 |	2   3   :   5   9   :   0   0				
    2 |	U   p   t   i   m   e   :       9   9   9   9   9   9       m   i   n			
    3 |	S   t   a   t   e   :       f   a   n   h   i   g   h   s   p   e   e   d
*/

    int64_t uptime;
    
    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);     //Display is on Wire1 bus
    lcd.init();
    
    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            lcd.setCursor(0,0);
            lcd.print(dayOfWeek);
            lcd.print(" ");

            //lcd.setCursor(9,0);
            lcd.print(dayStr);
            lcd.print("-");
            lcd.print(monthStr);
            lcd.print("-");
            lcd.print(yearStr);
            
            lcd.setCursor(0,1);
            lcd.print(hourStr);
            lcd.print(":");
            lcd.print(minuteStr);
            lcd.print(":");
            lcd.print(secondStr);  

            xSemaphoreGive(date_time_mutex);       
        }
        
        uptime = esp_timer_get_time();
        lcd.setCursor(0,2);
        lcd.print("Uptime: ");
        lcd.print(uptime/1000000/60);         // in minutes
        lcd.print(" min");
        
        

        vTaskDelay(5000);
        lcd.clear();
        Wire1.endTransmission();
    }
}

void display_state_fan(void) {

    /*
           0 	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15  16  17  18  19
          -------------------------------------------------------------------------------
       0 |	S   t   a   t   e   :       f   a   n   h   i   g   h   s   p   e   e   d
       1 |	F   a   n   s   p   e   e   d   :   M   e   d   i   u   m				
       2 |			
       3 |	
   */
        
    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);     //Display is on Wire1 bus
    lcd.init();

    lcd.setCursor(0,0);
    lcd.print("State: ");
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            lcd.print(state);
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    lcd.setCursor(0,1);
    lcd.print("Fan speed: ");
    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            lcd.print(fanspeed);
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    vTaskDelay(5000);
    lcd.clear();
    Wire1.endTransmission();  
}

String current_time(void) {

    char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    String formattedTime;

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {

            yearStr = String(now.year(), DEC);
            monthStr = (now.month() < 10 ? "0" : "") + String(now.month(), DEC);
            dayStr = (now.day() < 10 ? "0" : "") + String(now.day(), DEC);
            hourStr = (now.hour() < 10 ? "0" : "") + String(now.hour(), DEC);
            minuteStr = (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
            secondStr = (now.second() < 10 ? "0" : "") + String(now.second(), DEC);
            dayOfWeek = daysOfTheWeek[now.dayOfTheWeek()];
            formattedTime = dayOfWeek + ", " + yearStr + "-" + monthStr + "-" + dayStr + " " + hourStr + ":" + minuteStr + ":" + secondStr;
            xSemaphoreGive(date_time_mutex);
        }
    }
    Wire.endTransmission();
    return formattedTime;
}

void sync_rtc_ntp(void) {

    struct tm timeinfo;
        
    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);
    
    //DateTime now = rtc.now();

    //configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);  // Configure time with NTP server
    configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", "pool.ntp.org");
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.print("\nESP32 Time synchronized with NTP server.");
    Serial.print("\nCurrent time: ");
    Serial.print(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    // Sync the RTC with the NTP time
    rtc.adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));
    Wire.endTransmission();
}

void IRAM_ATTR lcd_baclight_pb_isr() {
    pb_toggle = true;
}

void pb_start_display(void) {

    pb_toggle = false;      
    
    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);
    lcd.init();
    lcd.backlight();
    Wire1.endTransmission();
    
    display_time_and_date();
    display_state_fan();
    display_sensors();
    display_valve_positions();
    
    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);
    lcd.noBacklight();
    Wire1.endTransmission();
}

void init_display_off(void) {
    Wire1.begin(I2C_SDA2, I2C_SCL2, 100000);
    lcd.init();
    lcd.clear();
    lcd.noBacklight();
    Wire1.endTransmission();
}
