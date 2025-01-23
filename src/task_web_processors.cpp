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

    const char* path1 = "/sensor_config1.json";
    const char* path2 = "/sensor_config2.json";
    const char* status;
    bool sensor_config_file_present;

    sensor_config_file_present = check_file_exists(path1);

    if(sensor_config_file_present == 1) {
        status = "<b><font color=\"green\">Sensor config file found.</font></b>";
        if (var == "STATUS_SENSOR_CONFIG1_FILE")
            return F(status);
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

