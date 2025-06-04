#include "config_files.h"

//Read mqtt config file and update global variables
void read_influxdb_config(void) {

    const char* path = "/json/settings_influxdb.json";
    String settings_influxdb_string = "";
    bool settings_influxdb_file_present = 0;
    JsonDocument settings_influxdb_doc;

    if (settings_influxdb_mutex != NULL) {
        if(xSemaphoreTake(settings_influxdb_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            settings_influxdb_file_present = check_file_exists(path);
            if (settings_influxdb_file_present == 1) {
                File file = LittleFS.open(path, "r");
                while(file.available()) {
                    settings_influxdb_string = file.readString();
                }
                file.close();
                deserializeJson(settings_influxdb_doc, settings_influxdb_string);
            }
            xSemaphoreGive(settings_influxdb_mutex);
        }
    }

    String enable_influxdb_tmp = settings_influxdb_doc[String("enable_influxdb")];
    String influxdb_url_tmp = settings_influxdb_doc[String("influxdb_url")];
    String influxdb_org_tmp = settings_influxdb_doc[String("influxdb_org")];
    String influxdb_bucket_tmp = settings_influxdb_doc[String("influxdb_bucket")];
    String influxdb_token_tmp = settings_influxdb_doc[String("influxdb_token")];

    if (settings_influxdb_mutex != NULL) {
        if(xSemaphoreTake(settings_influxdb_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                          
            //Assign to global variable
            enable_influxdb = enable_influxdb_tmp;
            influxdb_url = influxdb_url_tmp;
            influxdb_org = influxdb_org_tmp;
            influxdb_bucket = influxdb_bucket_tmp;
            influxdb_token = influxdb_token_tmp;
            xSemaphoreGive(settings_influxdb_mutex);
        }
    }
}

//Read I2C hardware settings
void read_i2c_config(void) {

    const char* path = "/json/settings_i2c.json";
    String settings_i2c_string = "";
    bool settings_i2c_file_present = 0;
    JsonDocument settings_i2c_doc;

    if (settings_i2c_mutex != NULL) {
        if(xSemaphoreTake(settings_i2c_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            settings_i2c_file_present = check_file_exists(path);
            if (settings_i2c_file_present == 1) {
                File file = LittleFS.open(path, "r");
                while(file.available()) {
                    settings_i2c_string = file.readString();
                }
                file.close();
                deserializeJson(settings_i2c_doc, settings_i2c_string);
            }
            xSemaphoreGive(settings_i2c_mutex);
        }
    }

    String bus0_multiplexer_addr_str = settings_i2c_doc[String("bus0_multiplexer_address")];
    String bus1_multiplexer_addr_str = settings_i2c_doc[String("bus0_multiplexer_address")];
    String enable_lcd_str = settings_i2c_doc[String("enable_lcd")];
    String display_i2c_addr_str = settings_i2c_doc[String("display_i2c_address")];
}


//Read mqtt config file and update global variables
void read_mqtt_config(void) {

    const char* path = "/json/settings_mqtt.json";
    String settings_mqtt_string = "";
    bool settings_mqtt_file_present = 0;
    JsonDocument settings_mqtt_doc;

    if (settings_mqtt_mutex != NULL) {
        if(xSemaphoreTake(settings_mqtt_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            settings_mqtt_file_present = check_file_exists(path);
            if (settings_mqtt_file_present == 1) {
                File file = LittleFS.open(path, "r");
                while(file.available()) {
                    settings_mqtt_string = file.readString();
                }
                file.close();
                deserializeJson(settings_mqtt_doc, settings_mqtt_string);
            }
            xSemaphoreGive(settings_mqtt_mutex);
        }
    }

    String enable_mqtt_tmp = settings_mqtt_doc[String("enable_mqtt")];
    String mqtt_server_tmp = settings_mqtt_doc[String("mqtt_server")];
    String mqtt_port_tmp = settings_mqtt_doc[String("mqtt_port")];
    String mqtt_base_topic_tmp = settings_mqtt_doc[String("mqtt_base_topic")];

    if (settings_mqtt_mutex != NULL) {
        if(xSemaphoreTake(settings_mqtt_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                          
            //Assign to global variable
            enable_mqtt = enable_mqtt_tmp;
            mqtt_server = mqtt_server_tmp;
            mqtt_port = mqtt_port_tmp.toInt();
            mqtt_base_topic = mqtt_base_topic_tmp;
            xSemaphoreGive(settings_mqtt_mutex);
        }
    }
}

//Read both sensor config files an place contents in global variable
void sensor_config_data_read() {
 
    const char* path1 = "/json/sensor_config1.json";
    const char* path2 = "/json/sensor_config2.json";
    
    String sensor_config1_string = "";
    String sensor_config2_string = "";

    bool sensor_config1_file_present = 0;
    bool sensor_config2_file_present = 0;
    
    if (sensor_config_file_mutex != NULL) {
        if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            sensor_config1_file_present = check_file_exists(path1);
            if (sensor_config1_file_present == 1) {
                File file = LittleFS.open(path1, "r");
                while(file.available()) {
                    sensor_config1_string = file.readString();
                }
                file.close();
                deserializeJson(wire_sensor_data, sensor_config1_string);
            }
            xSemaphoreGive(sensor_config_file_mutex);
        }
    }
	
    if (sensor_config_file_mutex != NULL) {
        if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            sensor_config2_file_present = check_file_exists(path2);
            if (sensor_config2_file_present == 1) {
                File file = LittleFS.open(path2, "r");
                while(file.available()) {
                    sensor_config2_string = file.readString();
                }
                file.close();
                deserializeJson(wire1_sensor_data, sensor_config2_string);
            }
            xSemaphoreGive(sensor_config_file_mutex);
        }
    }
}

//Function to read settings (e.g. valve positions) for each state and put these in the global variable
void valve_settings_config_read() {
    
    const char* settings_state_day_path = "/json/settings_state_day.json";
    const char* settings_state_night_path = "/json/settings_state_night.json";
    const char* settings_state_highco2day_path = "/json/settings_state_highco2day.json";
    const char* settings_state_highco2night_path = "/json/settings_state_highco2night.json";
    const char* settings_state_highrhday_path = "/json/settings_state_highrhday.json";
    const char* settings_state_highrhnight_path = "/json/settings_state_highrhnight.json";
    const char* settings_state_cooking_path = "/json/settings_state_cooking.json";
    const char* settings_state_cyclingday_path = "/json/settings_state_cyclingday.json";
    const char* settings_state_cyclingnight_path = "/json/settings_state_cyclingnight.json";

    String settings_state_day_str;
    String settings_state_night_str;
    String settings_state_highco2day_str;
    String settings_state_highco2night_str;
    String settings_state_highrhday_str;
    String settings_state_highrhnight_str;
    String settings_state_cooking_str;
    String settings_state_cyclingday_str;
    String settings_state_cyclingnight_str;

    bool settings_state_day_present = 0;
    bool settings_state_night_present = 0;
    bool settings_state_highco2day_present = 0;
    bool settings_state_highco2night_present = 0;
    bool settings_state_highrhday_present = 0;
    bool settings_state_highrhnight_present = 0;
    bool settings_state_cooking_present = 0;
    bool settings_state_cyclingday_present = 0;
    bool settings_state_cyclingnight_present = 0;
    
    if (settings_state_day_mutex != NULL) {
        if(xSemaphoreTake(settings_state_day_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            settings_state_day_present = check_file_exists(settings_state_day_path);
            if (settings_state_day_present == 1) {
                File file = LittleFS.open(settings_state_day_path, "r");
                while(file.available()) {
                    settings_state_day_str = file.readString();
                }
                file.close();
                deserializeJson(settings_state_day, settings_state_day_str);
            }
            xSemaphoreGive(settings_state_day_mutex);
        }
    }

    if (settings_state_night_mutex != NULL) {
        if(xSemaphoreTake(settings_state_night_mutex, ( TickType_t ) 100 ) == pdTRUE) { 
            settings_state_night_present = check_file_exists(settings_state_night_path);
            if (settings_state_night_present == 1) {
                File file = LittleFS.open(settings_state_night_path, "r");
                while(file.available()) {
                    settings_state_night_str = file.readString();
                }
                file.close();
                deserializeJson(settings_state_night, settings_state_night_str);
            }
            xSemaphoreGive(settings_state_night_mutex);
        }
    }

    if (settings_state_highco2day_mutex != NULL) {
        if(xSemaphoreTake(settings_state_highco2day_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            settings_state_highco2day_present = check_file_exists(settings_state_highco2day_path);
            if (settings_state_highco2day_present == 1) {
                File file = LittleFS.open(settings_state_highco2day_path, "r");
                while(file.available()) {
                    settings_state_highco2day_str = file.readString();
                }
                file.close();
                deserializeJson(settings_state_highco2day, settings_state_highco2day_str);
            }
            xSemaphoreGive(settings_state_highco2day_mutex);
        }
    }

    if (settings_state_highco2night_mutex != NULL) {
        if(xSemaphoreTake(settings_state_highco2night_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            settings_state_highco2night_present = check_file_exists(settings_state_highco2night_path);
            if (settings_state_highco2night_present == 1) {
                File file = LittleFS.open(settings_state_highco2night_path, "r");
                while(file.available()) {
                    settings_state_highco2night_str = file.readString();
                }
                file.close();
                
                deserializeJson(settings_state_highco2night, settings_state_highco2night_str);
            }
            xSemaphoreGive(settings_state_highco2night_mutex);
        }
    }

    if (settings_state_highrhday_mutex != NULL) {
        if(xSemaphoreTake(settings_state_highrhday_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            settings_state_highrhday_present = check_file_exists(settings_state_highrhday_path);
            if (settings_state_highrhday_present == 1) {
                File file = LittleFS.open(settings_state_highrhday_path, "r");
                while(file.available()) {
                    settings_state_highrhday_str = file.readString();
                }
                file.close();
                deserializeJson(settings_state_highrhday, settings_state_highrhday_str);
            }
            xSemaphoreGive(settings_state_highrhday_mutex);
        }
    }

    if (settings_state_highrhnight_mutex != NULL) {
        if(xSemaphoreTake(settings_state_highrhnight_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            
            settings_state_highrhnight_present = check_file_exists(settings_state_highrhnight_path);

            if (settings_state_highrhnight_present == 1) {
                File file = LittleFS.open(settings_state_highrhnight_path, "r");

                while(file.available()) {
                    settings_state_highrhnight_str = file.readString();
                }
                file.close();
                
                deserializeJson(settings_state_highrhnight, settings_state_highrhnight_str);
            }
            xSemaphoreGive(settings_state_highrhnight_mutex);
        }
    }

    if (settings_state_cooking_mutex != NULL) {
        if(xSemaphoreTake(settings_state_cooking_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            
            settings_state_cooking_present = check_file_exists(settings_state_cooking_path);

            if (settings_state_cooking_present == 1) {
                File file = LittleFS.open(settings_state_cooking_path, "r");

                while(file.available()) {
                    settings_state_cooking_str = file.readString();
                }
                file.close();
                
                deserializeJson(settings_state_cooking, settings_state_cooking_str);
            }
            xSemaphoreGive(settings_state_cooking_mutex);
        }
    }

    if (settings_state_cyclingday_mutex != NULL) {
        if(xSemaphoreTake(settings_state_cyclingday_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            
            settings_state_cyclingday_present = check_file_exists(settings_state_cyclingday_path);

            if (settings_state_cyclingday_present == 1) {
                File file = LittleFS.open(settings_state_cyclingday_path, "r");

                while(file.available()) {
                    settings_state_cyclingday_str = file.readString();
                }
                file.close();
                
                deserializeJson(settings_state_cyclingday, settings_state_cyclingday_str);
            }
            xSemaphoreGive(settings_state_cyclingday_mutex);
        }
    }

    if (settings_state_night_mutex != NULL) {
        if(xSemaphoreTake(settings_state_cyclingnight_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            
            settings_state_cyclingnight_present = check_file_exists(settings_state_cyclingnight_path);

            if (settings_state_cyclingnight_present == 1) {
                File file = LittleFS.open(settings_state_cyclingnight_path, "r");

                while(file.available()) {
                    settings_state_cyclingnight_str = file.readString();
                }
                file.close();
                
                deserializeJson(settings_state_cyclingnight, settings_state_cyclingnight_str);
            }
            xSemaphoreGive(settings_state_cyclingnight_mutex);
        }
    }
}

//Write valve status file with all valve positions 0
void valve_status_file_create() {
    
    File file;
    const char* default_valve_position_file;
    default_valve_position_file = "{\"valve0\":0, \"valve1\":0, \"valve2\":0, \"valve3\":0, \"valve4\":0, \"valve5\":0, \"valve6\":0, \"valve7\":0, \"valve8\":0, \"valve9\":0, \"valve10\":0, \"valve11\":0}";  

    if (valve_position_file_mutex != NULL) {
        if(xSemaphoreTake(valve_position_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            file = LittleFS.open("/json/valvepositions.json", "w");
            if(!file) {
                Serial.println("\nFailed to open file for writing");
                return;
            }
            // Write to the file
            if (file.println(default_valve_position_file)) {
                Serial.println("\nValve status file written");
            } 
            else {
                Serial.println("\nWrite failed");
            }
            file.close();
            xSemaphoreGive(valve_position_file_mutex);
        }
    }
}

//Delete file with path as input variable
void delete_file(const char* path) {
    
    if (LittleFS.remove(path)) {
        Serial.println("\nFile deleted");
    }
    else {
        Serial.println("\nDelete failed");
    }
}

bool check_file_exists(const char* path) {

    if (LittleFS.exists(path)) {
        return true;
    } 
    else {
        return false;
    }
}

// Functions read config file from file with file path as input and returns the contents of the file as a string. 
// Assumes presents of file was checked before calling this function.
String read_config_file(const char* path) {

    File file = LittleFS.open(path, "r");
    String valve_positions;
    //int i;

    while(file.available()) {
        valve_positions = file.readString();
    }
    file.close();
    return valve_positions;

}

//Write string to file, path and contents as string as parameters
void write_config_file(const char* path, String file_contents) { 

    File file;
    file = LittleFS.open(path, "w");
    if(!file) {
        Serial.println("\nFailed to open file for writing");
        return;
    }
    if (file.println(file_contents)) {
        Serial.println("\nConfig file written");
    } 
    else {
        Serial.println("\nWrite failed");
    }
    file.close();
}

//Read settings files and save contents in global varaibles