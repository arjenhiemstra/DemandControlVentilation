#include "task_web_processors.h"

String sensor_config_processor(const String& var) {
    
    const char* path1 = "/json/sensor_config1.json";
    const char* path2 = "/json/sensor_config2.json";
    const char* status;
    bool sensor_config_file1_present;
    bool sensor_config_file2_present;

    /*if (var == "WIRE_SENSOR_CONFIG")
        return (wire_sensor_config_string);
    if (var == "WIRE1_SENSOR_CONFIG")
        return (wire1_sensor_config_string);*/
    
    sensor_config_file1_present = check_file_exists(path1);

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

String status_processor(const String& var) {

    /*Valve positions part of processor*/
    const char* path = "/json/valvepositions.json";
    const char* status;
    bool status_file_present;
    
    String json;
    JsonDocument doc;
    
    if (valve_position_mutex != NULL) {
        if(xSemaphoreTake(valve_position_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            //Serial.print("mutex taken");
            status_file_present = check_file_exists(path);

            if (status_file_present == 1) {

                json = read_config_file(path);
                deserializeJson(doc, json);
            }
            xSemaphoreGive(valve_position_mutex);
        }
    }

    if(var == "VALVE0_POS")
    return (doc[String("valve0")]);
    if(var == "VALVE1_POS")
    return (doc[String("valve1")]);
    if(var == "VALVE2_POS")
    return (doc[String("valve2")]);
    if(var == "VALVE3_POS")
    return (doc[String("valve3")]);
    if(var == "VALVE4_POS")
    return (doc[String("valve4")]);
    if(var == "VALVE5_POS")
    return (doc[String("valve5")]);
    if(var == "VALVE6_POS")
    return (doc[String("valve6")]);
    if(var == "VALVE7_POS")
    return (doc[String("valve7")]);
    if(var == "VALVE8_POS")
    return (doc[String("valve8")]);
    if(var == "VALVE9_POS")
    return (doc[String("valve9")]);
    if(var == "VALVE10_POS")
    return (doc[String("valve10")]);
    if(var == "VALVE11_POS")
    return (doc[String("valve11")]);

    /*Sensor readings part of processor*/
    float temp_sensor_data[2][8][3];
    if (sensor_variable_mutex != NULL) {
        if(xSemaphoreTake(sensor_variable_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 8; j++) {
                    for (int k = 0; k < 3; k++) {
                        temp_sensor_data[i][j][k] = sensor_data[i][j][k];
                    }
                }
            }
            xSemaphoreGive(sensor_variable_mutex);
        }
    }

    if(var == "BUS0_SENSOR0_TEMP")
        return (String(temp_sensor_data[0][0][0]));
    if(var == "BUS0_SENSOR0_HUM")
        return (String(temp_sensor_data[0][0][1]));
    if(var == "BUS0_SENSOR0_CO2")
        return (String(temp_sensor_data[0][0][2]));
    if(var == "BUS0_SENSOR1_TEMP")
        return (String(temp_sensor_data[0][1][0]));
    if(var == "BUS0_SENSOR1_HUM")
        return (String(temp_sensor_data[0][1][1]));
    if(var == "BUS0_SENSOR1_CO2")
        return (String(temp_sensor_data[0][1][2]));
    if(var == "BUS0_SENSOR2_TEMP")
        return (String(temp_sensor_data[0][2][0]));
    if(var == "BUS0_SENSOR2_HUM")
        return (String(temp_sensor_data[0][2][1]));
    if(var == "BUS0_SENSOR2_CO2")
        return (String(temp_sensor_data[0][2][2]));
    if(var == "BUS0_SENSOR3_TEMP")
        return (String(sensor_data[0][3][0]));
    if(var == "BUS0_SENSOR3_HUM")
        return (String(temp_sensor_data[0][3][1]));
    if(var == "BUS0_SENSOR3_CO2")
        return (String(temp_sensor_data[0][3][2]));
    if(var == "BUS0_SENSOR4_TEMP")
        return (String(temp_sensor_data[0][4][0]));
    if(var == "BUS0_SENSOR4_HUM")
        return (String(temp_sensor_data[0][4][1]));
    if(var == "BUS0_SENSOR4_CO2")
        return (String(temp_sensor_data[0][4][2]));
    if(var == "BUS0_SENSOR5_TEMP")
        return (String(temp_sensor_data[0][5][0]));
    if(var == "BUS0_SENSOR5_HUM")
        return (String(temp_sensor_data[0][5][1]));
    if(var == "BUS0_SENSOR5_CO2")
        return (String(temp_sensor_data[0][5][2]));
    if(var == "BUS0_SENSOR6_TEMP")
        return (String(temp_sensor_data[0][6][0]));
    if(var == "BUS0_SENSOR6_HUM")
        return (String(temp_sensor_data[0][6][1]));
    if(var == "BUS0_SENSOR6_CO2")
        return (String(temp_sensor_data[0][6][2]));
    if(var == "BUS0_SENSOR7_TEMP")
        return (String(temp_sensor_data[0][7][0]));
    if(var == "BUS0_SENSOR7_HUM")
        return (String(temp_sensor_data[0][7][1]));
    if(var == "BUS0_SENSOR7_CO2")
        return (String(temp_sensor_data[0][7][2]));

    if(var == "BUS1_SENSOR0_TEMP")
        return (String(temp_sensor_data[1][0][0]));
    if(var == "BUS1_SENSOR0_HUM")
        return (String(temp_sensor_data[1][0][1]));
    if(var == "BUS1_SENSOR0_CO2")
        return (String(temp_sensor_data[1][0][2]));
    if(var == "BUS1_SENSOR1_TEMP")
        return (String(temp_sensor_data[1][1][0]));
    if(var == "BUS1_SENSOR1_HUM")
        return (String(temp_sensor_data[1][1][1]));
    if(var == "BUS1_SENSOR1_CO2")
        return (String(temp_sensor_data[1][1][2]));
    if(var == "BUS1_SENSOR2_TEMP")
        return (String(temp_sensor_data[1][2][0]));
    if(var == "BUS1_SENSOR2_HUM")
        return (String(temp_sensor_data[1][2][1]));
    if(var == "BUS1_SENSOR2_CO2")
        return (String(temp_sensor_data[1][2][2]));
    if(var == "BUS1_SENSOR3_TEMP")
        return (String(temp_sensor_data[1][3][0]));
    if(var == "BUS1_SENSOR3_HUM")
        return (String(temp_sensor_data[1][3][1]));
    if(var == "BUS1_SENSOR3_CO2")
        return (String(temp_sensor_data[1][3][2]));
    if(var == "BUS1_SENSOR4_TEMP")
        return (String(temp_sensor_data[1][4][0]));
    if(var == "BUS1_SENSOR4_HUM")
        return (String(temp_sensor_data[1][4][1]));
    if(var == "BUS1_SENSOR4_CO2")
        return (String(temp_sensor_data[1][4][2]));
    if(var == "BUS1_SENSOR5_TEMP")
        return (String(temp_sensor_data[1][5][0]));
    if(var == "BUS1_SENSOR5_HUM")
        return (String(temp_sensor_data[1][5][1]));
    if(var == "BUS1_SENSOR5_CO2")
        return (String(temp_sensor_data[1][5][2]));
    if(var == "BUS1_SENSOR6_TEMP")
        return (String(temp_sensor_data[1][6][0]));
    if(var == "BUS1_SENSOR6_HUM")
        return (String(temp_sensor_data[1][6][1]));
    if(var == "BUS1_SENSOR6_CO2")
        return (String(temp_sensor_data[1][6][2]));
    if(var == "BUS1_SENSOR7_TEMP")
        return (String(temp_sensor_data[1][7][0]));
    if(var == "BUS1_SENSOR7_HUM")
        return (String(temp_sensor_data[1][7][1]));
    if(var == "BUS1_SENSOR7_CO2")
        return (String(temp_sensor_data[1][7][2]));

    return String();
}

String settings_processor(const String& var) {

    return String();

}

String valvecontrol_processor(const String& var) {

  const char* path = "/json/valvepositions.json";
  const char* status;
  bool status_file_present;
  
  String json;
  JsonDocument doc;
  
  status_file_present = check_file_exists(path);

  if (status_file_present == 1) {
    status = "<b><font color=\"green\">Valve status file found.</font></b>";
    if (var == "STATUS_VALVE_POSITION_FILE") {
      return F(status);
    }
  }
  else {
    status = "<b><font color=\"red\">Valve status file not found. Create a file with button below.</font></b>";
    if (var == "STATUS_VALVE_POSITION_FILE") {
      return F(status);
    }
  }

  return String();
}
