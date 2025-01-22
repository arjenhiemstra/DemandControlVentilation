#include "config_files.h"

//Define globals for sensor configuration
JsonDocument wire_sensor_data;
JsonDocument wire1_sensor_data;

//Make array of sensors inside JsonDocument for each sensor
JsonArray wire_sensors = wire_sensor_data["wire_sensors"].to<JsonArray>();
JsonObject wire_sensors0 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors1 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors2 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors3 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors4 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors5 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors6 = wire_sensors.add<JsonObject>();
JsonObject wire_sensors7 = wire_sensors.add<JsonObject>();

JsonArray wire1_sensors = wire1_sensor_data["wire1_sensors"].to<JsonArray>();
JsonObject wire1_sensors0 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors1 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors2 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors3 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors4 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors5 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors6 = wire1_sensors.add<JsonObject>();
JsonObject wire1_sensors7 = wire1_sensors.add<JsonObject>();

/*JsonObject wire_sensors0["slot"];
JsonObject wire_sensors1["slot"];
JsonObject wire_sensors2["slot"];
JsonObject wire_sensors3["slot"];
JsonObject wire_sensors4["slot"];
JsonObject wire_sensors5["slot"];
JsonObject wire_sensors6["slot"];
JsonObject wire_sensors7["slot"];*/

/*JsonObject wire_sensors0["slot"] = 0;
JsonObject wire_sensors1["slot"] = 1;
JsonObject wire_sensors2["slot"] = 2;
JsonObject wire_sensors3["slot"] = 3;
JsonObject wire_sensors4["slot"] = 4;
JsonObject wire_sensors5["slot"] = 5;
JsonObject wire_sensors6["slot"] = 6;
JsonObject wire_sensors7["slot"] = 7;*/

JsonObject wire_sensors7["slot"];
JsonObject wire_sensors0["type"];
JsonObject wire_sensors0["address"];
JsonObject wire_sensors0["valve"];
JsonObject wire_sensors0["location"];
JsonObject wire_sensors0["rh"];
JsonObject wire_sensors0["co2"];




void sensor_config_data_read() {

    /*const char* path1 = "/sensor_config1.json";
    const char* path2 = "/sensor_config2.json";
    
    String sensor_config1_string;
    String sensor_config2_string;

    bool sensor_config1_file_present;
    bool sensor_config2_file_present;

    sensor_config1_file_present = check_file_exists(path1);
    sensor_config2_file_present = check_file_exists(path2);*/



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

