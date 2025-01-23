#include "config_files.h"

void sensor_config_data_read() {

    const char* path1 = "/sensor_config1.json";
    const char* path2 = "/sensor_config2.json";
    
    String sensor_config1_string;
    String sensor_config2_string;

    bool sensor_config1_file_present;
    bool sensor_config2_file_present;

    sensor_config1_file_present = check_file_exists(path1);
    sensor_config2_file_present = check_file_exists(path2);

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

void write_config_file(const char* path, String new_valve_positions) { 

    File file;
    file = LittleFS.open(path, "w");
    if(!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    // Write to the file
    if (file.println(new_valve_positions)) {
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

