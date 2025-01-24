#include "task_web_processors.h"
#include "config_files.h"

String valvecontrol_processor(const String& var) {

  const char* path = "/valvepositions.json";
  const char* status;
  bool status_file_present;
  
  String json;
  JsonDocument doc;
  
  status_file_present = check_file_exists(path);

  if (status_file_present == 1) {
    status = "<b><font color=\"green\">Valve status file found.</font></b>";
    if (var == "STATUS_VALVE_POSITION_FILE")
      return F(status);

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

    if(var == "VALVE0_POS")
      return (valve0_pos);
    if(var == "VALVE1_POS")
      return (valve1_pos);
    if(var == "VALVE2_POS")
      return (valve2_pos);
    if(var == "VALVE3_POS")
      return (valve3_pos);
    if(var == "VALVE4_POS")
      return (valve4_pos);
    if(var == "VALVE5_POS")
      return (valve5_pos);
    if(var == "VALVE6_POS")
      return (valve6_pos);
    if(var == "VALVE7_POS")
      return (valve7_pos);
    if(var == "VALVE8_POS")
      return (valve8_pos);
    if(var == "VALVE9_POS")
      return (valve9_pos);
    if(var == "VALVE10_POS")
      return (valve10_pos);
    if(var == "VALVE11_POS")
      return (valve11_pos);
  }

  else {
    status = "<b><font color=\"red\">Valve status file not found. Create a file with button below.</font></b>";
    if (var == "STATUS_VALVE_POSITION_FILE")
      return F(status);
  }

  return String();
}

String sensor_config_processor(const String& var) {

    extern JsonDocument wire_sensor_data;
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
    const char* status;
    bool sensor_config_file_present;

    String wire_sensor0_type = wire_sensors0["type"];
    String wire_sensor0_address = wire_sensors0["address"];
    String wire_sensor0_valve = wire_sensors0["valve"];
    String wire_sensor0_location = wire_sensors0["location"];
    String wire_sensor0_rh = wire_sensors0["rh"];
    String wire_sensor0_co2 = wire_sensors0["co2"];

    sensor_config_file_present = check_file_exists(path1);

    if(sensor_config_file_present == 1) {
        status = "<b><font color=\"green\">Sensor config file found.</font></b>";
        if (var == "STATUS_SENSOR_CONFIG1_FILE")
            return F(status);
        if (var == "WIRE_SENSOR0_TYPE")
            return (wire_sensors0["type"]);
        if (var == "WIRE_SENSOR0_ADDRESS")
            return (wire_sensors0["address"]);
        if (var == "WIRE_SENSOR0_VALVE")
            return (wire_sensors0["valve"]);
        if (var == "WIRE_SENSOR0_LOCATION")
            return (wire_sensors0["location"]);
        if (var == "WIRE_SENSOR0_RH")
            return (wire_sensors0["rh"]);
        if (var == "WIRE_SENSOR0_CO2")
            return (wire_sensors0["rh"]);
        if (var == "WIRE_SENSOR1_TYPE")
            return (wire_sensors1["type"]);
        if (var == "WIRE_SENSOR1_ADDRESS")
            return (wire_sensors1["address"]);
        if (var == "WIRE_SENSOR1_VALVE")
            return (wire_sensors1["valve"]);
        if (var == "WIRE_SENSOR0_LOCATION")
            return (wire_sensors1["location"]);
        if (var == "WIRE_SENSOR1_RH")
            return (wire_sensors1["rh"]);
        if (var == "WIRE_SENSOR0_CO2")
            return (wire_sensors1["rh"]);
        if (var == "WIRE_SENSOR2_TYPE")
            return (wire_sensors2["type"]);
        if (var == "WIRE_SENSOR2_ADDRESS")
            return (wire_sensors2["address"]);
        if (var == "WIRE_SENSOR2_VALVE")
            return (wire_sensors2["valve"]);
        if (var == "WIRE_SENSOR2_LOCATION")
            return (wire_sensors2["location"]);
        if (var == "WIRE_SENSOR2_RH")
            return (wire_sensors2["rh"]);
        if (var == "WIRE_SENSOR2_CO2")
            return (wire_sensors2["rh"]);
        if (var == "WIRE_SENSOR3_TYPE")
            return (wire_sensors3["type"]);
        if (var == "WIRE_SENSOR3_ADDRESS")
            return (wire_sensors3["address"]);
        if (var == "WIRE_SENSOR3_VALVE")
            return (wire_sensors3["valve"]);
        if (var == "WIRE_SENSOR3_LOCATION")
            return (wire_sensors3["location"]);
        if (var == "WIRE_SENSOR3_RH")
            return (wire_sensors3["rh"]);
        if (var == "WIRE_SENSOR3_CO2")
            return (wire_sensors3["rh"]);
        if (var == "WIRE_SENSOR4_TYPE")
            return (wire_sensors4["type"]);
        if (var == "WIRE_SENSOR4_ADDRESS")
            return (wire_sensors4["address"]);
        if (var == "WIRE_SENSOR4_VALVE")
            return (wire_sensors4["valve"]);
        if (var == "WIRE_SENSOR4_LOCATION")
            return (wire_sensors4["location"]);
        if (var == "WIRE_SENSOR4_RH")
            return (wire_sensors4["rh"]);
        if (var == "WIRE_SENSOR4_CO2")
            return (wire_sensors4["rh"]);
        if (var == "WIRE_SENSOR5_TYPE")
            return (wire_sensors5["type"]);
        if (var == "WIRE_SENSOR5_ADDRESS")
            return (wire_sensors5["address"]);
        if (var == "WIRE_SENSOR5_VALVE")
            return (wire_sensors5["valve"]);
        if (var == "WIRE_SENSOR5_LOCATION")
            return (wire_sensors5["location"]);
        if (var == "WIRE_SENSOR5_RH")
            return (wire_sensors5["rh"]);
        if (var == "WIRE_SENSOR5_CO2")
            return (wire_sensors5["rh"]);
        if (var == "WIRE_SENSOR6_TYPE")
            return (wire_sensors6["type"]);
        if (var == "WIRE_SENSOR6_ADDRESS")
            return (wire_sensors6["address"]);
        if (var == "WIRE_SENSOR6_VALVE")
            return (wire_sensors6["valve"]);
        if (var == "WIRE_SENSOR6_LOCATION")
            return (wire_sensors6["location"]);
        if (var == "WIRE_SENSOR6_RH")
            return (wire_sensors6["rh"]);
        if (var == "WIRE_SENSOR6_CO2")
            return (wire_sensors6["rh"]);
        if (var == "WIRE_SENSOR7_TYPE")
            return (wire_sensors7["type"]);
        if (var == "WIRE_SENSOR7_ADDRESS")
            return (wire_sensors7["address"]);
        if (var == "WIRE_SENSOR7_VALVE")
            return (wire_sensors7["valve"]);
        if (var == "WIRE_SENSOR7_LOCATION")
            return (wire_sensors7["location"]);
        if (var == "WIRE_SENSOR7_RH")
            return (wire_sensors7["rh"]);
        if (var == "WIRE_SENSOR7_CO2")
            return (wire_sensors7["rh"]);
    }

    else {
        status = "<b><font color=\"red\">Sensor config file not found. Create a file with button below.</font></b>";
        if (var == "STATUS_SENSOR_CONFIG1_FILE")
            return F(status);
    }

    sensor_config_file_present = check_file_exists(path2);

    if(sensor_config_file_present == 1) {
        status = "<b><font color=\"green\">Sensor config file found.</font></b>";
        if (var == "STATUS_SENSOR_CONFIG2_FILE")
            return F(status);
    }

    else {
        status = "<b><font color=\"red\">Sensor config file not found. Create a file with button below.</font></b>";
        if (var == "STATUS_SENSOR_CONFIG2_FILE")
            return F(status);
    }

    return String();
}

