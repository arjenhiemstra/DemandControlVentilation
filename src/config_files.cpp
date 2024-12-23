#include "config_files.h"

File file;

void valve_status_file_create() {
    
    const char* default_valve_position_file;
    default_valve_position_file = "{\"valve0\":0, \"valve1\":0, \"valve2\":0, \"valve3\":0, \"valve4\":0, \"valve5\":0, \"valve6\":0, \"valve7\":0, \"valve8\":0, \"valve9\":0, \"valve10\":0, \"valve11\":0}";
    
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

void valve_status_file_delete(const char* path) {
    
    if (LittleFS.remove("/valvepositions.json")) {
        Serial.println("File deleted");
    }
    else {
        Serial.println("Delete failed");
    }
}

bool check_valve_position_file_exists(void) {

    if (LittleFS.exists("/valvepositions.json")) {
        Serial.println("File exists");
        return true;
    } 
    else {
        Serial.println("File does not exist");
        return false;
    }
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

void write_new_valve_positions_to_file(void) {




}