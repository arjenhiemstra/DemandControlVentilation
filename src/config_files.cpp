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

void valve_status_file_delete() {
    
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
