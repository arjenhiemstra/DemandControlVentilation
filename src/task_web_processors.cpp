#include "task_web_processors.h"

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
    bool sensor_config_file1_present;
    bool sensor_config_file2_present;

    if (var == "WIRE_SENSOR_CONFIG")
        return (wire_sensor_config_string);
    if (var == "WIRE1_SENSOR_CONFIG")
        return (wire1_sensor_config_string);
    
    sensor_config_file1_present = check_file_exists(path1);

    //if (sensor_config_file_mutex != NULL) {
        //if(xSemaphoreTake(sensor_config_file_mutex, (TickType_t)0)) {
            
            //String wire_sensors0_type = wire_sensor_data["wire_sensor0"]["type"];
            //Serial.print("\n\nwire_sensors0_type: ");
            //Serial.print(wire_sensors0_type);
            //Serial.print("\n\n");
            
            if(sensor_config_file1_present == 1) {
                status = "<b><font color=\"green\">Sensor config file found.</font></b>";
                if (var == "STATUS_SENSOR_CONFIG1_FILE")
                    return (status);
                if (var == "WIRE_SENSOR0_TYPE")
                    return (wire_sensor_data["wire_sensor0"]["type"]);
                if (var == "WIRE_SENSOR0_ADDRESS")
                    return (wire_sensor_data["wire_sensor0"]["address"]);
                if (var == "WIRE_SENSOR0_VALVE")
                    return (wire_sensor_data["wire_sensor0"]["valve"]);
                if (var == "WIRE_SENSOR0_LOCATION")
                    return (wire_sensor_data["wire_sensor0"]["location"]);
                if (var == "WIRE_SENSOR0_RH")
                    return (wire_sensor_data["wire_sensor0"]["rh"]);
                if (var == "WIRE_SENSOR0_CO2")
                    return (wire_sensor_data["wire_sensor0"]["co2"]);
                if (var == "WIRE_SENSOR1_TYPE")
                    return (wire_sensor_data["wire_sensor1"]["type"]);
                if (var == "WIRE_SENSOR1_ADDRESS")
                    return (wire_sensor_data["wire_sensor1"]["address"]);
                if (var == "WIRE_SENSOR1_VALVE")
                    return (wire_sensor_data["wire_sensor1"]["valve"]);
                if (var == "WIRE_SENSOR0_LOCATION")
                    return (wire_sensor_data["wire_sensor1"]["location"]);
                if (var == "WIRE_SENSOR1_RH")
                    return (wire_sensor_data["wire_sensor1"]["rh"]);
                if (var == "WIRE_SENSOR0_CO2")
                    return (wire_sensor_data["wire_sensor1"]["co2"]);
                if (var == "WIRE_SENSOR2_TYPE")
                    return (wire_sensor_data["wire_sensor2"]["type"]);
                if (var == "WIRE_SENSOR2_ADDRESS")
                    return (wire_sensor_data["wire_sensor2"]["address"]);
                if (var == "WIRE_SENSOR2_VALVE")
                    return (wire_sensor_data["wire_sensor2"]["valve"]);
                if (var == "WIRE_SENSOR2_LOCATION")
                    return (wire_sensor_data["wire_sensor2"]["location"]);
                if (var == "WIRE_SENSOR2_RH")
                    return (wire_sensor_data["wire_sensor2"]["rh"]);
                if (var == "WIRE_SENSOR2_CO2")
                    return (wire_sensor_data["wire_sensor2"]["co2"]);
                if (var == "WIRE_SENSOR3_TYPE")
                    return (wire_sensor_data["wire_sensor3"]["type"]);
                if (var == "WIRE_SENSOR3_ADDRESS")
                    return (wire_sensor_data["wire_sensor3"]["address"]);
                if (var == "WIRE_SENSOR3_VALVE")
                    return (wire_sensor_data["wire_sensor3"]["valve"]);
                if (var == "WIRE_SENSOR3_LOCATION")
                    return (wire_sensor_data["wire_sensor3"]["location"]);
                if (var == "WIRE_SENSOR3_RH")
                    return (wire_sensor_data["wire_sensor3"]["rh"]);
                if (var == "WIRE_SENSOR3_CO2")
                    return (wire_sensor_data["wire_sensor3"]["co2"]);
                if (var == "WIRE_SENSOR4_TYPE")
                    return (wire_sensor_data["wire_sensor4"]["type"]);
                if (var == "WIRE_SENSOR4_ADDRESS")
                    return (wire_sensor_data["wire_sensor4"]["address"]);
                if (var == "WIRE_SENSOR4_VALVE")
                    return (wire_sensor_data["wire_sensor4"]["valve"]);
                if (var == "WIRE_SENSOR4_LOCATION")
                    return (wire_sensor_data["wire_sensor4"]["location"]);
                if (var == "WIRE_SENSOR4_RH")
                    return (wire_sensor_data["wire_sensor4"]["rh"]);
                if (var == "WIRE_SENSOR4_CO2")
                    return (wire_sensor_data["wire_sensor4"]["co2"]);
                if (var == "WIRE_SENSOR5_TYPE")
                    return (wire_sensor_data["wire_sensor5"]["type"]);
                if (var == "WIRE_SENSOR5_ADDRESS")
                    return (wire_sensor_data["wire_sensor5"]["address"]);
                if (var == "WIRE_SENSOR5_VALVE")
                    return (wire_sensor_data["wire_sensor5"]["valve"]);
                if (var == "WIRE_SENSOR5_LOCATION")
                    return (wire_sensor_data["wire_sensor5"]["location"]);
                if (var == "WIRE_SENSOR5_RH")
                    return (wire_sensor_data["wire_sensor5"]["rh"]);
                if (var == "WIRE_SENSOR5_CO2")
                    return (wire_sensor_data["wire_sensor5"]["co2"]);
                if (var == "WIRE_SENSOR6_TYPE")
                    return (wire_sensor_data["wire_sensor6"]["type"]);
                if (var == "WIRE_SENSOR6_ADDRESS")
                    return (wire_sensor_data["wire_sensor6"]["address"]);
                if (var == "WIRE_SENSOR6_VALVE")
                    return (wire_sensor_data["wire_sensor6"]["valve"]);
                if (var == "WIRE_SENSOR6_LOCATION")
                    return (wire_sensor_data["wire_sensor6"]["location"]);
                if (var == "WIRE_SENSOR6_RH")
                    return (wire_sensor_data["wire_sensor6"]["rh"]);
                if (var == "WIRE_SENSOR6_CO2")
                    return (wire_sensor_data["wire_sensor6"]["co2"]);
                if (var == "WIRE_SENSOR7_TYPE")
                    return (wire_sensor_data["wire_sensor7"]["type"]);
                if (var == "WIRE_SENSOR7_ADDRESS")
                    return (wire_sensor_data["wire_sensor7"]["address"]);
                if (var == "WIRE_SENSOR7_VALVE")
                    return (wire_sensor_data["wire_sensor7"]["valve"]);
                if (var == "WIRE_SENSOR7_LOCATION")
                    return (wire_sensor_data["wire_sensor7"]["location"]);
                if (var == "WIRE_SENSOR7_RH")
                    return (wire_sensor_data["wire_sensor7"]["rh"]);
                if (var == "WIRE_SENSOR7_CO2")
                    return (wire_sensor_data["wire_sensor0"]["co2"]);
            }
            else {
                status = "<b><font color=\"red\">Sensor config file not found. Create a file with button below.</font></b>";
                if (var == "STATUS_SENSOR_CONFIG1_FILE")
                    return F(status);
            }
            //if(xSemaphoreGive(sensor_config_file_mutex) != pdTRUE) {
			//	configASSERT(pdFALSE);
			//}
        //}
    //}

    sensor_config_file2_present = check_file_exists(path2);

    if(sensor_config_file2_present == 1) {
        status = "<b><font color=\"green\">Sensor config file found.</font></b>";
        if (var == "STATUS_SENSOR_CONFIG2_FILE")
            return F(status);
        if (var == "WIRE1_SENSOR0_TYPE")
            return (wire1_sensor_data["wire1_sensor0"]["type"]);
        if (var == "WIRE1_SENSOR0_ADDRESS")
            return (wire1_sensor_data["wire1_sensor0"]["address"]);
        if (var == "WIRE1_SENSOR0_VALVE")
            return (wire1_sensor_data["wire1_sensor0"]["valve"]);
        if (var == "WIRE1_SENSOR0_LOCATION")
            return (wire1_sensor_data["wire1_sensor0"]["location"]);
        if (var == "WIRE1_SENSOR0_RH")
            return (wire1_sensor_data["wire1_sensor0"]["rh"]);
        if (var == "WIRE1_SENSOR0_CO2")
            return (wire1_sensor_data["wire1_sensor0"]["co2"]);
        if (var == "WIRE1_SENSOR1_TYPE")
            return (wire1_sensor_data["wire1_sensor1"]["type"]);
        if (var == "WIRE1_SENSOR1_ADDRESS")
            return (wire1_sensor_data["wire1_sensor1"]["address"]);
        if (var == "WIRE1_SENSOR1_VALVE")
            return (wire1_sensor_data["wire1_sensor1"]["valve"]);
        if (var == "WIRE1_SENSOR0_LOCATION")
            return (wire1_sensor_data["wire1_sensor1"]["location"]);
        if (var == "WIRE1_SENSOR1_RH")
            return (wire1_sensor_data["wire1_sensor1"]["rh"]);
        if (var == "WIRE1_SENSOR0_CO2")
            return (wire1_sensor_data["wire1_sensor1"]["co2"]);
        if (var == "WIRE1_SENSOR2_TYPE")
            return (wire1_sensor_data["wire1_sensor2"]["type"]);
        if (var == "WIRE1_SENSOR2_ADDRESS")
            return (wire1_sensor_data["wire1_sensor2"]["address"]);
        if (var == "WIRE1_SENSOR2_VALVE")
            return (wire1_sensor_data["wire1_sensor2"]["valve"]);
        if (var == "WIRE1_SENSOR2_LOCATION")
            return (wire1_sensor_data["wire1_sensor2"]["location"]);
        if (var == "WIRE1_SENSOR2_RH")
            return (wire1_sensor_data["wire1_sensor2"]["rh"]);
        if (var == "WIRE1_SENSOR2_CO2")
            return (wire1_sensor_data["wire1_sensor2"]["co2"]);
        if (var == "WIRE1_SENSOR3_TYPE")
            return (wire1_sensor_data["wire1_sensor3"]["type"]);
        if (var == "WIRE1_SENSOR3_ADDRESS")
            return (wire1_sensor_data["wire1_sensor3"]["address"]);
        if (var == "WIRE1_SENSOR3_VALVE")
            return (wire1_sensor_data["wire1_sensor3"]["valve"]);
        if (var == "WIRE1_SENSOR3_LOCATION")
            return (wire1_sensor_data["wire1_sensor3"]["location"]);
        if (var == "WIRE1_SENSOR3_RH")
            return (wire1_sensor_data["wire1_sensor3"]["rh"]);
        if (var == "WIRE1_SENSOR3_CO2")
            return (wire1_sensor_data["wire1_sensor3"]["co2"]);
        if (var == "WIRE1_SENSOR4_TYPE")
            return (wire1_sensor_data["wire1_sensor4"]["type"]);
        if (var == "WIRE1_SENSOR4_ADDRESS")
            return (wire1_sensor_data["wire1_sensor4"]["address"]);
        if (var == "WIRE1_SENSOR4_VALVE")
            return (wire1_sensor_data["wire1_sensor4"]["valve"]);
        if (var == "WIRE1_SENSOR4_LOCATION")
            return (wire1_sensor_data["wire1_sensor4"]["location"]);
        if (var == "WIRE1_SENSOR4_RH")
            return (wire1_sensor_data["wire1_sensor4"]["rh"]);
        if (var == "WIRE1_SENSOR4_CO2")
            return (wire1_sensor_data["wire1_sensor4"]["co2"]);
        if (var == "WIRE1_SENSOR5_TYPE")
            return (wire1_sensor_data["wire1_sensor5"]["type"]);
        if (var == "WIRE1_SENSOR5_ADDRESS")
            return (wire1_sensor_data["wire1_sensor5"]["address"]);
        if (var == "WIRE1_SENSOR5_VALVE")
            return (wire1_sensor_data["wire1_sensor5"]["valve"]);
        if (var == "WIRE1_SENSOR5_LOCATION")
            return (wire1_sensor_data["wire1_sensor5"]["location"]);
        if (var == "WIRE1_SENSOR5_RH")
            return (wire1_sensor_data["wire1_sensor5"]["rh"]);
        if (var == "WIRE1_SENSOR5_CO2")
            return (wire1_sensor_data["wire1_sensor5"]["co2"]);
        if (var == "WIRE1_SENSOR6_TYPE")
            return (wire1_sensor_data["wire1_sensor6"]["type"]);
        if (var == "WIRE1_SENSOR6_ADDRESS")
            return (wire1_sensor_data["wire1_sensor6"]["address"]);
        if (var == "WIRE1_SENSOR6_VALVE")
            return (wire1_sensor_data["wire1_sensor6"]["valve"]);
        if (var == "WIRE1_SENSOR6_LOCATION")
            return (wire1_sensor_data["wire1_sensor6"]["location"]);
        if (var == "WIRE1_SENSOR6_RH")
            return (wire1_sensor_data["wire1_sensor6"]["rh"]);
        if (var == "WIRE1_SENSOR6_CO2")
            return (wire1_sensor_data["wire1_sensor6"]["co2"]);
        if (var == "WIRE1_SENSOR7_TYPE")
            return (wire1_sensor_data["wire1_sensor7"]["type"]);
        if (var == "WIRE1_SENSOR7_ADDRESS")
            return (wire1_sensor_data["wire1_sensor7"]["address"]);
        if (var == "WIRE1_SENSOR7_VALVE")
            return (wire1_sensor_data["wire1_sensor7"]["valve"]);
        if (var == "WIRE1_SENSOR7_LOCATION")
            return (wire1_sensor_data["wire1_sensor7"]["location"]);
        if (var == "WIRE1_SENSOR7_RH")
            return (wire1_sensor_data["wire1_sensor7"]["rh"]);
        if (var == "WIRE1_SENSOR7_CO2")
            return (wire1_sensor_data["wire1_sensor7"]["co2"]);
    }
        
    else {
        status = "<b><font color=\"red\">Sensor config file not found. Create a file with button below.</font></b>";
        if (var == "STATUS_SENSOR_CONFIG2_FILE")
            return F(status);
    }

    return String();

}

