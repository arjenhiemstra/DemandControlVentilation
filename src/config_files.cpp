#include "config_files.h"

void sensor_config_data_read() {
 
    extern JsonDocument wire_sensor_data;
    extern JsonDocument wire1_sensor_data;

    extern JsonArray wire_sensors;
    extern JsonObject wire_sensors0; 
    extern JsonObject wire_sensors1;
    extern JsonObject wire_sensors2; 
    extern JsonObject wire_sensors3;
    extern JsonObject wire_sensors4;
    extern JsonObject wire_sensors5;
    extern JsonObject wire_sensors6;
    extern JsonObject wire_sensors7;

    extern JsonArray wire1_sensors;
    extern JsonObject wire1_sensors0; 
    extern JsonObject wire1_sensors1;
    extern JsonObject wire1_sensors2; 
    extern JsonObject wire1_sensors3;
    extern JsonObject wire1_sensors4;
    extern JsonObject wire1_sensors5;
    extern JsonObject wire1_sensors6;
    extern JsonObject wire1_sensors7;

    const char* path1 = "/sensor_config1.json";
    const char* path2 = "/sensor_config2.json";
    
    String sensor_config1_string;
    String sensor_config2_string;

    bool sensor_config1_file_present;
    bool sensor_config2_file_present;

    //xSemaphoreTake(mutex, portMAX_DELAY);
    sensor_config1_file_present = check_file_exists(path1);
    sensor_config2_file_present = check_file_exists(path2);
    //xSemaphoreGive(mutex);

    Serial.print("\n\nSensor config file 1 present: ");
    Serial.print(sensor_config1_file_present);

    if (sensor_config1_file_present = 1) {
        File file = LittleFS.open(path1, "r");

        while(file.available()) {
            sensor_config1_string = file.readString();
        }
        file.close();
        deserializeJson(wire_sensor_data, sensor_config1_string);

        wire_sensors = wire_sensor_data["wire_sensors"];
        wire_sensors0 = wire_sensors[0];
        wire_sensors1 = wire_sensors[1];
        wire_sensors2 = wire_sensors[2];
        wire_sensors3 = wire_sensors[3];
        wire_sensors4 = wire_sensors[4];
        wire_sensors5 = wire_sensors[5];
        wire_sensors6 = wire_sensors[6];
        wire_sensors7 = wire_sensors[7];

        wire1_sensors = wire1_sensor_data["wire_sensors"];
        wire1_sensors0 = wire1_sensors[0];
        wire1_sensors1 = wire1_sensors[1];
        wire1_sensors2 = wire1_sensors[2];
        wire1_sensors3 = wire1_sensors[3];
        wire1_sensors4 = wire1_sensors[4];
        wire1_sensors5 = wire1_sensors[5];
        wire1_sensors6 = wire1_sensors[6];
        wire1_sensors7 = wire1_sensors[7];

        Serial.print("\n\nContents config file: \n\n");
        serializeJson(wire_sensor_data, Serial);

        Serial.print("\n\nContents sensor file sensor0: \n\n");
        String test = wire_sensors0["type"];
        Serial.print(test);
    }
}

void valve_status_file_create() {
    
    File file;
    const char* default_valve_position_file;
    default_valve_position_file = "{\"valve0\":1, \"valve1\":2, \"valve2\":3, \"valve3\":4, \"valve4\":5, \"valve5\":6, \"valve6\":7, \"valve7\":8, \"valve8\":9, \"valve9\":10, \"valve10\":11, \"valve11\":12}";
    
    file = LittleFS.open("/valvepositions.json", "w");
    if(!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    // Write to the file
    if (file.println(default_valve_position_file)) {
        Serial.println("File written");
    } 
    else {
        Serial.println("Write failed");
    }
    file.close();
}

void delete_file(const char* path) {
    
    if (LittleFS.remove(path)) {
        Serial.println("File deleted");
    }
    else {
        Serial.println("Delete failed");
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

String read_config_file(const char* path) {

    // Functions read config file from file with file path as input and return the contents of the file as a string. 
    // Assumes presents of fule was checked.

    File file = LittleFS.open(path, "r");
    String valve_positions;
    int i;

    while(file.available()) {
        valve_positions = file.readString();
    }
    file.close();

    return valve_positions;

}

void write_config_file(const char* path, String file_contents) { 

    File file;
    file = LittleFS.open(path, "w");
    if(!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    // Write to the file
    if (file.println(file_contents)) {
        Serial.println("File written");
    } 
    else {
        Serial.println("Write failed");
    }
    file.close();
}

bool verify_valve_position_file_contents(void) {

    int i;
    File file;

    //Assumes file exists
    file = LittleFS.open("/valvepositions.json", "r");
    if(!file) {
        Serial.println("Failed to open file");
        return false;
    }
    
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);

    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return false;
    }

    // Access the JSON data
    //const char* valve0_pos = doc["valve0"];
    int valve0_pos;
    for(i=0;i<12;i++) {
         "valve" + String(i) + "_pos" = 0;
        Serial.print(valve0_pos);
        
        //= doc[("valve" + String(i))];
        //int valve0_pos = doc[("valve" + i)];
        //if (("valve" + String(i) + "_pos") >= 0 || ("valve" + String(i) + "_pos") <25) {
        // if (valve0_pos >= 0 || valve0_pos <25) {
        //     return true;
        // }
        // else {
        //     return false;
        //     break;
        // }
    }
    
    file.close();
    return 0;
}

