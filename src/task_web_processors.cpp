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
        status = "<font color=\"green\">Sensor config file found.</font>";
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
        status = "<font color=\"red\">Sensor config file not found. Create a file with button below.</font>";
        if (var == "STATUS_SENSOR_CONFIG1_FILE")
            return F(status);
    }

    sensor_config_file2_present = check_file_exists(path2);

    if(sensor_config_file2_present == 1) {
        status = "<font color=\"green\">Sensor config file found.</font>";
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
        status = "<font color=\"red\">Sensor config file not found. Create a file with button below.</font>";
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
    
    if (valve_position_file_mutex != NULL) {
        if(xSemaphoreTake(valve_position_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            //Serial.print("mutex taken");
            status_file_present = check_file_exists(path);

            if (status_file_present == 1) {

                json = read_config_file(path);
                deserializeJson(doc, json);
            }
            xSemaphoreGive(valve_position_file_mutex);
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

    //Copy data from queue in local variable
    float temp_sensor_data[2][8][3];
    if( sensor_queue != 0 ) {
        if (xQueuePeek(sensor_queue, &temp_sensor_data, ( TickType_t ) 10 )) { 
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
        return (String(temp_sensor_data[0][3][0]));
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

String valvecontrol_processor(const String& var) {

  const char* path = "/json/valvepositions.json";
  const char* status;
  bool status_file_present;
  
  String json;
  JsonDocument doc;
  
  status_file_present = check_file_exists(path);

  if (status_file_present == 1) {
    status = "<font color=\"green\">Valve status file found.</font>";
    if (var == "STATUS_VALVE_POSITION_FILE") {
      return F(status);
    }
  }
  else {
    status = "<font color=\"red\">Valve status file not found. Create a file with button below.</font>";
    if (var == "STATUS_VALVE_POSITION_FILE") {
      return F(status);
    }
  }

  return String();
}

String settings_processor(const String& var) {

    const char* settings_network_path = "/json/settings_network.json";
    const char* settings_mqtt_path = "/json/settings_mqtt.json";
    const char* settings_i2c_path = "/json/settings_i2c.json";
    const char* settings_fan_path = "/json/settings_fan.json";
    const char* settings_statemachine_path = "/json/settings_statemachine.json";
    const char* status;
    bool settings_network_file_present;
    bool settings_mqtt_file_present;
    bool settings_i2c_file_present;
    bool settings_fan_file_present;
    bool settings_statemachine_file_present;

    String settings_network_json;
    String settings_mqtt_json;
    String settings_i2c_json;
    String settings_fan_json;
    String settings_statemachine_json;
    JsonDocument settings_network_doc;
    JsonDocument settings_mqtt_doc;
    JsonDocument settings_i2c_doc;
    JsonDocument settings_fan_doc;
    JsonDocument settings_statemachine_doc;
  
    /*Network settings processor*/
    if (settings_network_mutex != NULL) {
        if(xSemaphoreTake(settings_network_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            settings_network_file_present = check_file_exists(settings_network_path);
            if (settings_network_file_present == 1) {
                settings_network_json = read_config_file(settings_network_path);
                deserializeJson(settings_network_doc, settings_network_json);
            }
            xSemaphoreGive(settings_network_mutex);
        }
    }

    if (settings_network_file_present == 1) {
        status = "<font color=\"green\">Network settings file found.</font>";
        if (var == "STATUS_NETWORK_CONFIG")
            return F(status);
        if(var == "ENABLE_DHCP")
            return (settings_network_doc[String("enable_dhcp")]);
        if(var == "SSID")
            return (settings_network_doc[String("ssid")]);
        if(var == "WIFI_PASSWORD")
            return (settings_network_doc[String("wifi_password")]);
        if(var == "IP_ADDRESS")
            return (settings_network_doc[String("ip_address")]);
        if(var == "SUBNET_MASK")
            return (settings_network_doc[String("subnet_mask")]);
        if(var == "GATEWAY")
            return (settings_network_doc[String("gateway")]);
        if(var == "PRIMARY_DNS")
            return (settings_network_doc[String("primary_dns")]);
        if(var == "SECONDARY_DNS")
            return (settings_network_doc[String("secondary_dns")]);
    }
    else {
        status = "<font color=\"red\">Network settings file not found.</font>";
        if (var == "STATUS_NETWORK_CONFIG") {
            return F(status);
        }
    }
    
    /*MQTT Settings processor*/
    if (settings_mqtt_mutex != NULL) {
        if(xSemaphoreTake(settings_mqtt_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            settings_mqtt_file_present = check_file_exists(settings_mqtt_path);
            if (settings_mqtt_file_present == 1) {
                settings_mqtt_json = read_config_file(settings_mqtt_path);
                deserializeJson(settings_mqtt_doc, settings_mqtt_json);
            }
            xSemaphoreGive(settings_mqtt_mutex);
        }
    }

    if (settings_mqtt_file_present == 1) {
        status = "<font color=\"green\">MQTT settings file found.</font>";
        if (var == "STATUS_MQTT_CONFIG") 
            return F(status);
        if(var == "ENABLE_MQTT")
            return (settings_mqtt_doc[String("enable_mqtt")]);
        if(var == "MQTT_SERVER")
            return (settings_mqtt_doc[String("mqtt_server")]);
        if(var == "MQTT_PORT")
            return (settings_mqtt_doc[String("mqtt_port")]);
        if(var == "MQTT_BASE_TOPIC")
            return (settings_mqtt_doc[String("mqtt_base_topic")]);
    }
    else {
        status = "<font color=\"red\">MQTT settings file not found.</font>";
        if (var == "STATUS_MQTT_CONFIG") {
            return F(status);
        }
    }

    /*I2C Settings processor*/
    if (settings_i2c_mutex != NULL) {
        if(xSemaphoreTake(settings_i2c_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            settings_i2c_file_present = check_file_exists(settings_i2c_path);
            if (settings_i2c_file_present == 1) {
                settings_i2c_json = read_config_file(settings_i2c_path);
                deserializeJson(settings_i2c_doc, settings_i2c_json);
            }
            xSemaphoreGive(settings_i2c_mutex);
        }
    }

    if (settings_i2c_file_present == 1) {
        status = "<font color=\"green\">I2C settings file found.</font>";
        if (var == "STATUS_I2C_HARDWARE_CONFIG")
            return F(status);
        if(var == "BUS0_MULTIPLEXER_ADDRESS")
            return (settings_i2c_doc[String("bus0_multiplexer_address")]);
        if(var == "BUS1_MULTIPLEXER_ADDRESS")
            return (settings_i2c_doc[String("bus1_multiplexer_address")]);
        if(var == "ENABLE_LCD")   
            return (settings_i2c_doc[String("enable_lcd")]);
        if(var == "DISPLAY_I2C_ADDRESS")
            return (settings_i2c_doc[String("display_i2c_address")]);
    }
    else {
        status = "<font color=\"red\">I2C settings file not found.</font>";
        if (var == "STATUS_I2C_HARDWARE_CONFIG") {
            return F(status);
        }
    }

    /*Fan settings processor*/
    if (settings_fan_mutex != NULL) {
        if(xSemaphoreTake(settings_fan_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            settings_fan_file_present = check_file_exists(settings_fan_path);
            if (settings_fan_file_present == 1) {
                settings_fan_json = read_config_file(settings_fan_path);
                deserializeJson(settings_i2c_doc, settings_fan_json);
            }
            xSemaphoreGive(settings_fan_mutex);
        }
    }

    if (settings_fan_file_present == 1) {
        status = "<font color=\"green\">Fan settings file found.</font>";
        if (var == "STATUS_FAN_CONTROL_CONFIG")
            return F(status);
        if(var == "FAN_CONTROL_MODE")
            return (settings_i2c_doc[String("fan_control_mode")]);
        if(var == "FAN_CONTROL_MQTT_TOPIC")
            return (settings_i2c_doc[String("fan_control_mqtt_topic")]);
        if(var == "FAN_CONTROL_URL_HIGH_SPEED")
            return (settings_i2c_doc[String("fan_control_url_high_speed")]);
        if(var == "FAN_CONTROL_URL_MEDIUM_SPEED")
            return (settings_i2c_doc[String("fan_control_url_medium_speed")]);
        if(var == "FAN_CONTROL_URL_LOW_SPEED")
            return (settings_i2c_doc[String("fan_control_url_low_speed")]);
    }
    else {
        status = "<font color=\"red\">Fan settings file not found.</font>";
        if (var == "STATUS_FAN_CONTROL_CONFIG") {
            return F(status);
        }
    }

    /*Statemachine settings processor*/
    if (settings_statemachine_mutex != NULL) {
        if(xSemaphoreTake(settings_statemachine_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            settings_statemachine_file_present = check_file_exists(settings_statemachine_path);
            if (settings_statemachine_file_present == 1) {
                settings_statemachine_json = read_config_file(settings_statemachine_path);
                deserializeJson(settings_statemachine_doc, settings_statemachine_json);
            }
            xSemaphoreGive(settings_statemachine_mutex);
        }
    }

    if (settings_statemachine_file_present == 1) {
        status = "<font color=\"green\">Statemachine settings file found.</font>";
        if (var == "STATUS_STATEMACHINE_CONFIG") 
            return F(status);
        if(var == "STATEMACHINE_RH_SENSOR")
            return (settings_statemachine_doc[String("statemachine_rh_sensor")]);
        if(var == "STATEMACHINE_CO2_SENSOR")
            return (settings_statemachine_doc[String("statemachine_co2_sensor")]);
    }
    else {
        status = "<font color=\"red\">Statemachine settings file not found.</font>";
        if (var == "STATUS_STATEMACHINE_CONFIG") {
            return F(status);
        }
    }

    return String();
}

String settings_valve_state(const String& var) {
    
    /*Day state*/


    /*Night state*/


    /*High CO2 day state*/


    /*High CO2 night state*/


    /*High RH day state*/


    /*High RH night state*/


    /*Cooking state*/


    /*Valve cycling day state*/


    /*Valve cycling night state*/

    
    
    return String();
}