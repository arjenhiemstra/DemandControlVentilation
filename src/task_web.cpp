#include "task_web.h"

TaskHandle_t h_Task_web;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//Variables for valvecontrol page
const char* VALVE0_POSITION_MOVE = "valve0_position_move";
const char* VALVE0_DIRECTION = "valve0_direction";
const char* VALVE1_POSITION_MOVE = "valve1_position_move";
const char* VALVE1_DIRECTION = "valve1_direction";
const char* VALVE2_POSITION_MOVE = "valve2_position_move";
const char* VALVE2_DIRECTION = "valve2_direction";
const char* VALVE3_POSITION_MOVE = "valve3_position_move";
const char* VALVE3_DIRECTION = "valve3_direction";
const char* VALVE4_POSITION_MOVE = "valve4_position_move";
const char* VALVE4_DIRECTION = "valve4_direction";
const char* VALVE5_POSITION_MOVE = "valve5_position_move";
const char* VALVE5_DIRECTION = "valve5_direction";
const char* VALVE6_POSITION_MOVE = "valve6_position_move";
const char* VALVE6_DIRECTION = "valve6_direction";
const char* VALVE7_POSITION_MOVE = "valve7_position_move";
const char* VALVE7_DIRECTION = "valve7_direction";
const char* VALVE8_POSITION_MOVE = "valve8_position_move";
const char* VALVE8_DIRECTION = "valve8_direction";
const char* VALVE9_POSITION_MOVE = "valve9_position_move";
const char* VALVE9_DIRECTION = "valve9_direction";
const char* VALVE10_POSITION_MOVE = "valve10_position_move";
const char* VALVE10_DIRECTION = "valve10_direction";
const char* VALVE11_POSITION_MOVE = "valve11_position_move";
const char* VALVE11_DIRECTION = "valve11_direction";
const char* STORE_VALVE_POSITION_IN_FILE = "store_valve_position_in_file";
const char* CHECK_VALVE_POSITION = "check_valve_position";
const char* STATUS_VALVE_POSITION_FILE;

String valve0_direction,valve1_direction,valve2_direction,valve3_direction,valve4_direction,valve5_direction,valve6_direction,valve7_direction,valve8_direction,valve9_direction,valve10_direction,valve11_direction;
String check_valve_position;            // True when check is required if valve moves within operating range
String store_valve_position_in_file;    // True to enable storing of new position in valve position file

//Variables for sensor config page
const char* WIRE_SENSOR0_TYPE = "wire_sensor0_type";
const char* WIRE_SENSOR0_ADDRESS = "wire_sensor0_address";
const char* WIRE_SENSOR0_VALVE = "wire_sensor0_valve";
const char* WIRE_SENSOR0_LOCATION = "wire_sensor0_location";
const char* WIRE_SENSOR1_TYPE = "wire_sensor1_type";
const char* WIRE_SENSOR1_ADDRESS = "wire_sensor1_address";
const char* WIRE_SENSOR1_VALVE = "wire_sensor1_valve";
const char* WIRE_SENSOR1_LOCATION = "wire_sensor1_location";
const char* WIRE_SENSOR2_TYPE = "wire_sensor2_type";
const char* WIRE_SENSOR2_ADDRESS = "wire_sensor2_address";
const char* WIRE_SENSOR2_VALVE = "wire_sensor2_valve";
const char* WIRE_SENSOR2_LOCATION = "wire_sensor2_location";
const char* WIRE_SENSOR3_TYPE = "wire_sensor3_type";
const char* WIRE_SENSOR3_ADDRESS = "wire_sensor3_address";
const char* WIRE_SENSOR3_VALVE = "wire_sensor3_valve";
const char* WIRE_SENSOR3_LOCATION = "wire_sensor3_location";
const char* WIRE_SENSOR4_TYPE = "wire_sensor4_type";
const char* WIRE_SENSOR4_ADDRESS = "wire_sensor4_address";
const char* WIRE_SENSOR4_VALVE = "wire_sensor4_valve";
const char* WIRE_SENSOR4_LOCATION = "wire_sensor4_location";
const char* WIRE_SENSOR5_TYPE = "wire_sensor5_type";
const char* WIRE_SENSOR5_ADDRESS = "wire_sensor5_address";
const char* WIRE_SENSOR5_VALVE = "wire_sensor5_valve";
const char* WIRE_SENSOR5_LOCATION = "wire_sensor5_location";
const char* WIRE_SENSOR6_TYPE = "wire_sensor6_type";
const char* WIRE_SENSOR6_ADDRESS = "wire_sensor6_address";
const char* WIRE_SENSOR6_VALVE = "wire_sensor6_valve";
const char* WIRE_SENSOR6_LOCATION = "wire_sensor6_location";
const char* WIRE_SENSOR7_TYPE = "wire_sensor7_type";
const char* WIRE_SENSOR7_ADDRESS = "wire_sensor7_address";
const char* WIRE_SENSOR7_VALVE = "wire_sensor7_valve";
const char* WIRE_SENSOR7_LOCATION = "wire_sensor7_location";

const char* WIRE1_SENSOR0_TYPE = "wire1_sensor0_type";
const char* WIRE1_SENSOR0_ADDRESS = "wire1_sensor0_address";
const char* WIRE1_SENSOR0_VALVE = "wire1_sensor0_valve";
const char* WIRE1_SENSOR0_LOCATION = "wire1_sensor0_location";
const char* WIRE1_SENSOR1_TYPE = "wire1_sensor1_type";
const char* WIRE1_SENSOR1_ADDRESS = "wire1_sensor1_address";
const char* WIRE1_SENSOR1_VALVE = "wire1_sensor1_valve";
const char* WIRE1_SENSOR1_LOCATION = "wire1_sensor1_location";
const char* WIRE1_SENSOR2_TYPE = "wire1_sensor2_type";
const char* WIRE1_SENSOR2_ADDRESS = "wire1_sensor2_address";
const char* WIRE1_SENSOR2_VALVE = "wire1_sensor2_valve";
const char* WIRE1_SENSOR2_LOCATION = "wire1_sensor2_location";
const char* WIRE1_SENSOR3_TYPE = "wire1_sensor3_type";
const char* WIRE1_SENSOR3_ADDRESS = "wire1_sensor3_address";
const char* WIRE1_SENSOR3_VALVE = "wire1_sensor3_valve";
const char* WIRE1_SENSOR3_LOCATION = "wire1_sensor3_location";
const char* WIRE1_SENSOR4_TYPE = "wire1_sensor4_type";
const char* WIRE1_SENSOR4_ADDRESS = "wire1_sensor4_address";
const char* WIRE1_SENSOR4_VALVE = "wire1_sensor4_valve";
const char* WIRE1_SENSOR4_LOCATION = "wire1_sensor4_location";
const char* WIRE1_SENSOR5_TYPE = "wire1_sensor5_type";
const char* WIRE1_SENSOR5_ADDRESS = "wire1_sensor5_address";
const char* WIRE1_SENSOR5_VALVE = "wire1_sensor5_valve";
const char* WIRE1_SENSOR5_LOCATION = "wire1_sensor5_location";
const char* WIRE1_SENSOR6_TYPE = "wire1_sensor6_type";
const char* WIRE1_SENSOR6_ADDRESS = "wire1_sensor6_address";
const char* WIRE1_SENSOR6_VALVE = "wire1_sensor6_valve";
const char* WIRE1_SENSOR6_LOCATION = "wire1_sensor6_location";
const char* WIRE1_SENSOR7_TYPE = "wire1_sensor7_type";
const char* WIRE1_SENSOR7_ADDRESS = "wire1_sensor7_address";
const char* WIRE1_SENSOR7_VALVE = "wire1_sensor7_valve";
const char* WIRE1_SENSOR7_LOCATION = "wire1_sensor7_location";

const char* WIRE_SENSOR_CONFIG = "wire_sensor_config";
const char* WIRE1_SENSOR_CONFIG = "wire1_sensor_config";

const char* STATUS_NETWORK_CONFIG = "status_network_config";
const char* SSID = "ssid";
const char* WIFI_PASSWORD = "wifi_password";
const char* IP_ADDRESS = "ip_address";
const char* SUBNET_MASK = "subnet_mask";
const char* GATEWAY = "gateway";
const char* PRIMARY_DNS = "primary_dns";
const char* SECONDARY_DNS = "secondary_dns";

const char* STATUS_MQTT_CONFIG = "status_mqtt_config";
const char* MQTT_SERVER = "mqtt_server";
const char* MQTT_PORT = "mqtt_port";
const char* MQTT_BASE_TOPIC = "mqtt_base_topic";

const char* STATUS_I2C_CONFIG = "status_i2c_config";
const char* BUS0_MULTIPLEXER_ADDRESS = "bus0_multiplexer_address";
const char* BUS1_MULTIPLEXER_ADDRESS = "bus0_multiplexer_address";
const char* DISPLAY_I2C_ADDRESS = "display_i2c_address";

const char* STATUS_FAN_CONTROL_CONFIG = "status_fan_control_config";
const char* FAN_CONTROL_MODE = "fan_control_mode";
const char* FAN_CONTROL_MQTT_TOPIC = "fan_control_mqtt_topic";
const char* FAN_CONTROL_URL_HIGH_SPEED = "fan_control_url_high_speed";
const char* FAN_CONTROL_URL_MEDIUM_SPEED = "fan_control_url_medium_speed";
const char* FAN_CONTROL_URL_LOW_SPEED = "fan_control_url_low_speed";

const char* STATUS_STATEMACHINE_CONFIG = "status_statemachine_config";
const char* STATEMACHINE_RH_SENSOR = "statemachine_rh_sensor";
const char* STATEMACHINE_CO2_SENSOR = "statemachine_co2_sensor";

void startTaskwebcode(void) {

  xTaskCreatePinnedToCore(Taskwebcode, "Task_web", 10000, NULL, 9, &h_Task_web, 0);

}

void Taskwebcode(void *pvParameters) {
   
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/html/index.html", "text/html");
    request->send(LittleFS, "/html/index.html", String(), false, status_processor);
  });

  server.on("/css/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/css/styles.css", "text/css");
  });

  server.on("/js/ui.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/js/ui.js", "text/javascript");
  });

  //Not found handling
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "The content you are looking for was not found.");
  });

  //Settings web pages processing
  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/html/settings.html", "text/html");
  });

  //Save settings from network settings
  server.on("/settings_network", HTTP_POST, [](AsyncWebServerRequest *request) {
    
    if (settings_network_mutex != NULL) {
      if(xSemaphoreTake(settings_network_mutex, ( TickType_t ) 10 ) == pdTRUE) {
        int params = request->params();
        for(int i=0;i<params;i++){
          const AsyncWebParameter* p = request->getParam(i);
          if(p->isPost()){
            if (p->name() == SSID) {
              settings_network_data["ssid"] = p->value().c_str();;
            }
            if (p->name() == WIFI_PASSWORD) {
              settings_network_data["wifi_password"] = p->value().c_str();;
            }
            if (p->name() == IP_ADDRESS) {
              settings_network_data["ip_address"] = p->value().c_str();;
            }
            if (p->name() == SUBNET_MASK) {
              settings_network_data["subnet_mask"] = p->value().c_str();;
            }
            if (p->name() == GATEWAY) {
              settings_network_data["gateway"] = p->value().c_str();;
            }
            if (p->name() == PRIMARY_DNS) {
              settings_network_data["primary_dns"] = p->value().c_str();;
            }
            if (p->name() == SECONDARY_DNS) {
              settings_network_data["secondary_dns"] = p->value().c_str();;
            }
          }
        }
        const char* path = "/json/settings_network.json";
        String settings_network_str;

        serializeJson(settings_network_data, settings_network_str);
        write_config_file(path, settings_network_str);
             
        //request->send(LittleFS, "/html/sensor_config.html", "text/html");
        request->send(LittleFS, "/html/settings.html", String(), false, settings_processor);
        xSemaphoreGive(settings_network_mutex);
      }
    }
  });

  //Save settings from MQTT settings
  server.on("/settings_mqtt", HTTP_POST, [](AsyncWebServerRequest *request) {
    
    if (settings_mqtt_mutex != NULL) {
      if(xSemaphoreTake(settings_mqtt_mutex, ( TickType_t ) 10 ) == pdTRUE) {
        int params = request->params();
        for(int i=0;i<params;i++){
          const AsyncWebParameter* p = request->getParam(i);
          if(p->isPost()){
            if (p->name() == STATUS_MQTT_CONFIG) {
              settings_mqtt_data["status_mqtt_config"] = p->value().c_str();;
            }
            if (p->name() == MQTT_SERVER) {
              settings_mqtt_data["mqtt_server"] = p->value().c_str();;
            }
            if (p->name() == MQTT_PORT) {
              settings_mqtt_data["mqtt_port"] = p->value().c_str();;
            }
            if (p->name() == MQTT_BASE_TOPIC) {
              settings_mqtt_data["mqtt_base_topic"] = p->value().c_str();;
            }
          }
        }
        const char* path = "/json/settings_mqtt.json";
        String settings_mqtt_str;

        serializeJson(settings_mqtt_data, settings_mqtt_str);
        write_config_file(path, settings_mqtt_str);
             
        request->send(LittleFS, "/html/settings.html", String(), false, settings_processor);
        xSemaphoreGive(settings_mqtt_mutex);
      }
    }
  });

  //Save settings from I2C settings
  server.on("/settings_i2c", HTTP_POST, [](AsyncWebServerRequest *request) {
    
    if (settings_i2c_mutex != NULL) {
      if(xSemaphoreTake(settings_i2c_mutex, ( TickType_t ) 10 ) == pdTRUE) {
        int params = request->params();
        for(int i=0;i<params;i++){
          const AsyncWebParameter* p = request->getParam(i);
          if(p->isPost()){
            if (p->name() == STATUS_I2C_CONFIG) {
              settings_i2c_data["status_i2c_config"] = p->value().c_str();;
            }
            if (p->name() == BUS0_MULTIPLEXER_ADDRESS) {
              settings_i2c_data["bus0_multiplexer_address"] = p->value().c_str();;
            }
            if (p->name() == BUS1_MULTIPLEXER_ADDRESS) {
              settings_i2c_data["bus0_multiplexer_address"] = p->value().c_str();;
            }
            if (p->name() == DISPLAY_I2C_ADDRESS) {
              settings_i2c_data["display_i2c_address"] = p->value().c_str();;
            }
          }
        }
        const char* path = "/json/settings_i2c.json";
        String settings_i2c_str;

        serializeJson(settings_i2c_data, settings_i2c_str);
        write_config_file(path, settings_i2c_str);
             
        request->send(LittleFS, "/html/settings.html", String(), false, settings_processor);
        xSemaphoreGive(settings_i2c_mutex);
      }
    }
  });

  //Save settings from fan control settings
  server.on("/settings_fan", HTTP_POST, [](AsyncWebServerRequest *request) {
    
    if (settings_fan_mutex != NULL) {
      if(xSemaphoreTake(settings_fan_mutex, ( TickType_t ) 10 ) == pdTRUE) {
        int params = request->params();
        for(int i=0;i<params;i++){
          const AsyncWebParameter* p = request->getParam(i);
          if(p->isPost()){
            if (p->name() == STATUS_FAN_CONTROL_CONFIG) {
              settings_fan_data["status_fan_control_config"] = p->value().c_str();;
            }
            if (p->name() == FAN_CONTROL_MODE) {
              settings_fan_data["fan_control_mode"] = p->value().c_str();;
            }
            if (p->name() == FAN_CONTROL_MQTT_TOPIC) {
              settings_fan_data["fan_control_mqtt_topic"] = p->value().c_str();;
            }
            if (p->name() == FAN_CONTROL_URL_HIGH_SPEED) {
              settings_fan_data["fan_control_url_high_speed"] = p->value().c_str();;
            }
            if (p->name() == FAN_CONTROL_URL_MEDIUM_SPEED) {
              settings_fan_data["fan_control_url_medium_speed"] = p->value().c_str();;
            }
            if (p->name() == FAN_CONTROL_URL_LOW_SPEED) {
              settings_fan_data["fan_control_url_low_speed"] = p->value().c_str();;
            }
          }
        }
        const char* path = "/json/settings_fan.json";
        String settings_fan_str;

        serializeJson(settings_fan_data, settings_fan_str);
        write_config_file(path, settings_fan_str);
             
        request->send(LittleFS, "/html/settings.html", String(), false, settings_processor);
        xSemaphoreGive(settings_fan_mutex);
      }
    }
  });

  //Save settings from statemachine settings
  server.on("/settings_statemachine", HTTP_POST, [](AsyncWebServerRequest *request) {
    
    if (settings_statemachine_mutex != NULL) {
      if(xSemaphoreTake(settings_statemachine_mutex, ( TickType_t ) 10 ) == pdTRUE) {
        int params = request->params();
        for(int i=0;i<params;i++){
          const AsyncWebParameter* p = request->getParam(i);
          if(p->isPost()){
            if (p->name() == STATUS_STATEMACHINE_CONFIG) {
              settings_statemachine_data["status_statemachine_config"] = p->value().c_str();;
            }
            if (p->name() == STATEMACHINE_RH_SENSOR) {
              settings_statemachine_data["statemachine_rh_sensor"] = p->value().c_str();;
            }
            if (p->name() == STATEMACHINE_CO2_SENSOR) {
              settings_statemachine_data["statemachine_co2_sensor"] = p->value().c_str();;
            }
          }
        }
        const char* path = "/json/settings_statemachine.json";
        String settings_statemachine_str;

        serializeJson(settings_statemachine_data, settings_statemachine_str);
        write_config_file(path, settings_statemachine_str);
             
        request->send(LittleFS, "/html/settings.html", String(), false, settings_processor);
        xSemaphoreGive(settings_statemachine_mutex);
      }
    }
  });

  //Valve control web pages processing
  server.on("/valvecontrol", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/html/valvecontrol.html", "text/html");
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, valvecontrol_processor);
  });
  
  //Valve control web pages processing
  server.on("/valvecontrol", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, valvecontrol_processor);
  });

  //Response for POST action in webform valvecontrol manual move valves
  server.on("/valvecontrol", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (valve_control_data_mutex != NULL) {
        if(xSemaphoreTake(valve_control_data_mutex, ( TickType_t ) 10 ) == pdTRUE) {
        int params = request->params();
        for(int i=0;i<params;i++){
          const AsyncWebParameter* p = request->getParam(i);
          if(p->isPost()){
            if (p->name() == VALVE0_POSITION_MOVE) {
              valve_control_data["valve0_data"][0] = 0;
              valve_control_data["valve0_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE0_DIRECTION) {
              valve0_direction = p->value().c_str();
              if (valve0_direction == "Close") {
                valve_control_data["valve0_data"][2] = 0;
              }
              else {
                valve_control_data["valve0_data"][2] = 1;
              }
            }
            if (p->name() == VALVE1_POSITION_MOVE) {
              valve_control_data["valve1_data"][0] = 1;
              valve_control_data["valve1_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE1_DIRECTION) {
              valve1_direction = p->value().c_str();
              if (valve1_direction == "Close") {
                valve_control_data["valve1_data"][2] = 0;
              }
              else {
                valve_control_data["valve1_data"][2] = 1;
              }
            }
            if (p->name() == VALVE2_POSITION_MOVE) {
              valve_control_data["valve2_data"][0] = 2;
              valve_control_data["valve2_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE2_DIRECTION) {
              valve2_direction = p->value().c_str();
              if (valve2_direction == "Close") {
                valve_control_data["valve2_data"][2] = 0;
              }
              else {
                valve_control_data["valve2_data"][2] = 1;
              }
            }
            if (p->name() == VALVE3_POSITION_MOVE) {
              valve_control_data["valve3_data"][0] = 3;
              valve_control_data["valve3_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE3_DIRECTION) {
              valve3_direction = p->value().c_str();
              if (valve3_direction == "Close") {
                valve_control_data["valve3_data"][2] = 0;
              }
              else {
                valve_control_data["valve3_data"][2] = 1;
              }
            }
            if (p->name() == VALVE4_POSITION_MOVE) {
              valve_control_data["valve4_data"][0] = 4;
              valve_control_data["valve4_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE4_DIRECTION) {
              valve4_direction = p->value().c_str();
              if (valve4_direction == "Close") {
                valve_control_data["valve4_data"][2] = 0;
              }
              else {
                valve_control_data["valve4_data"][2] = 1;
              }
            }
            if (p->name() == VALVE5_POSITION_MOVE) {
              valve_control_data["valve5_data"][0] = 5;
              valve_control_data["valve5_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE5_DIRECTION) {
              valve5_direction = p->value().c_str();
              if (valve5_direction == "Close") {
                valve_control_data["valve5_data"][2] = 0;
              }
              else {
                valve_control_data["valve5_data"][2] = 1;
              }
            }
            if (p->name() == VALVE6_POSITION_MOVE) {
              valve_control_data["valve6_data"][0] = 6;
              valve_control_data["valve6_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE6_DIRECTION) {
              valve6_direction = p->value().c_str();
              if (valve6_direction == "Close") {
                valve_control_data["valve6_data"][2] = 0;
              }
              else {
                valve_control_data["valve6_data"][2] = 1;
              }
            }
            if (p->name() == VALVE7_POSITION_MOVE) {
              valve_control_data["valve7_data"][0] = 7;
              valve_control_data["valve7_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE7_DIRECTION) {
              valve7_direction = p->value().c_str();
              if (valve7_direction == "Close") {
                valve_control_data["valve7_data"][2] = 0;
              }
              else {
                valve_control_data["valve7_data"][2] = 1;
              }
            }
            if (p->name() == VALVE8_POSITION_MOVE) {
              valve_control_data["valve8_data"][0] = 8;
              valve_control_data["valve8_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE8_DIRECTION) {
              valve8_direction = p->value().c_str();
              if (valve8_direction == "Close") {
                valve_control_data["valve8_data"][2] = 0;
              }
              else {
                valve_control_data["valve8_data"][2] = 1;
              }
            }
            if (p->name() == VALVE9_POSITION_MOVE) {
              valve_control_data["valve9_data"][0] = 9;
              valve_control_data["valve9_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE9_DIRECTION) {
              valve9_direction = p->value().c_str();
              if (valve9_direction == "Close") {
                valve_control_data["valve9_data"][2] = 0;
              }
              else {
                valve_control_data["valve9_data"][2] = 1;
              }
            }
            if (p->name() == VALVE10_POSITION_MOVE) {
              valve_control_data["valve10_data"][0] = 10;
              valve_control_data["valve10_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE10_DIRECTION) {
              valve10_direction = p->value().c_str();
              if (valve10_direction == "Close") {
                valve_control_data["valve10_data"][2] = 0;
              }
              else {
                valve_control_data["valve10_data"][2] = 1;
              }
            }
            if (p->name() == VALVE11_POSITION_MOVE) {
              valve_control_data["valve11_data"][0] = 11;
              valve_control_data["valve11_data"][1] =  p->value().toInt();
            }
            if (p->name() == VALVE11_DIRECTION) {
              valve11_direction = p->value().c_str();
              if (valve11_direction == "Close") {
                valve_control_data["valve11_data"][2] = 0;
              }
              else {
                valve_control_data["valve11_data"][2] = 1;
              }
            }
            if (p->name() == STORE_VALVE_POSITION_IN_FILE) {
              store_valve_position_in_file = p->value().c_str();
              if (store_valve_position_in_file == "true") {
                valve_control_data["checks"][0] = 1;
              }
              else {
                valve_control_data["checks"][0] = 0;
              }
            }
            if (p->name() == CHECK_VALVE_POSITION) {
              check_valve_position = p->value().c_str();
              if (check_valve_position == "true") {
                valve_control_data["checks"][1] = 1;
              }
              else {
                valve_control_data["checks"][1] = 0;
              }
            }
          }
        }
        request->send(LittleFS, "/html/valvecontrol.html", String(), false, valvecontrol_processor);
        xSemaphoreGive(valve_control_data_mutex);
        xTaskNotifyGive(xTaskGetHandle("task_valvectrl"));
      }
    }
  });

  //POST on button create config file - name must match with action of the form submit
  server.on("/create_config_file", HTTP_POST, [](AsyncWebServerRequest *request) {
    valve_status_file_create();
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, valvecontrol_processor);
  });
    
  server.on("/delete_config_file", HTTP_POST, [](AsyncWebServerRequest *request) {
    const char* path = "/json/valvepositions.json";
    delete_file(path);
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, valvecontrol_processor);
  });

  //Sensor config web page processing
  server.on("/sensorconfig", HTTP_GET, [](AsyncWebServerRequest *request){
  
    //Serial.print("\n\nwire sensor data from HTTP GET sensorconfig: \n\n");
    //serializeJson(wire_sensor_data, Serial);
    //Serial.print("\n\n");

    //Update config file data for display in browser
    //serializeJson(wire_sensor_data, wire_sensor_config_string);
    //serializeJson(wire1_sensor_data, wire1_sensor_config_string);
        
    //request->send(LittleFS, "/html/sensor_config.html", "text/html");
    request->send(LittleFS, "/html/sensor_config.html", String(), false, sensor_config_processor);
  });

  server.on("/delete_sensor_config_file1", HTTP_POST, [](AsyncWebServerRequest *request) {
    const char* path = "/json/sensor_config1.json";
    delete_file(path);
    request->send(LittleFS, "/html/sensor_config.html", String(), false, sensor_config_processor);
  });

  server.on("/delete_sensor_config_file2", HTTP_POST, [](AsyncWebServerRequest *request) {
    const char* path = "/json/sensor_config2.json";
    delete_file(path);
    request->send(LittleFS, "/html/sensor_config.html", String(), false, sensor_config_processor);
  });
  
  //Write sensor config input to file
  server.on("/sensorconfig1", HTTP_POST, [](AsyncWebServerRequest *request) {
    int params = request->params();
    for(int i=0;i<params;i++){
      const AsyncWebParameter* p = request->getParam(i);
      if(p->isPost()){
        if (p->name() == WIRE_SENSOR0_TYPE) {
          wire_sensor_data["wire_sensor0"]["type"] = p->value().c_str();;
        }
        if (p->name() == WIRE_SENSOR0_ADDRESS) {
          wire_sensor_data["wire_sensor0"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR0_VALVE) {
          wire_sensor_data["wire_sensor0"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR0_LOCATION) {
          wire_sensor_data["wire_sensor0"]["location"] = p->value().c_str();;
        }
        if (p->name() == WIRE_SENSOR1_TYPE) {
          wire_sensor_data["wire_sensor1"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR1_ADDRESS) {
          wire_sensor_data["wire_sensor1"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR1_VALVE) {
          wire_sensor_data["wire_sensor1"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR1_LOCATION) {
          wire_sensor_data["wire_sensor1"]["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR2_TYPE) {
          wire_sensor_data["wire_sensor2"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR2_ADDRESS) {
          wire_sensor_data["wire_sensor2"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR2_VALVE) {
          wire_sensor_data["wire_sensor2"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR2_LOCATION) {
          wire_sensor_data["wire_sensor2"]["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR3_TYPE) {
          wire_sensor_data["wire_sensor3"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR3_ADDRESS) {
          wire_sensor_data["wire_sensor3"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR3_VALVE) {
          wire_sensor_data["wire_sensor3"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR3_LOCATION) {
          wire_sensor_data["wire_sensor3"]["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR4_TYPE) {
          wire_sensor_data["wire_sensor4"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR4_ADDRESS) {
          wire_sensor_data["wire_sensor4"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR4_VALVE) {
          wire_sensor_data["wire_sensor4"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR4_LOCATION) {
          wire_sensor_data["wire_sensor4"]["location"] = p->value().c_str(); 
        }
        if (p->name() == WIRE_SENSOR5_TYPE) {
          wire_sensor_data["wire_sensor5"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR5_ADDRESS) {
          wire_sensor_data["wire_sensor5"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR5_VALVE) {
          wire_sensor_data["wire_sensor5"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR5_LOCATION) {
          wire_sensor_data["wire_sensor5"]["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR6_TYPE) {
          wire_sensor_data["wire_sensor6"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR6_ADDRESS) {
          wire_sensor_data["wire_sensor6"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR6_VALVE) {
          wire_sensor_data["wire_sensor6"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR6_LOCATION) {
          wire_sensor_data["wire_sensor6"]["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR7_TYPE) {
          wire_sensor_data["wire_sensor7"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR7_ADDRESS) {
          wire_sensor_data["wire_sensor7"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR7_VALVE) {
          wire_sensor_data["wire_sensor7"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR7_LOCATION) {
          wire_sensor_data["wire_sensor7"]["location"] = p->value().c_str();
        }
      }
    }
      
    const char* path1 = "/json/sensor_config1.json";
    String sensor_config1;
    serializeJson(wire_sensor_data, sensor_config1);
    write_config_file(path1, sensor_config1);
    //Update string to display config file contents after saving config
    //serializeJson(wire_sensor_data, wire_sensor_config_string);
    //request->send(LittleFS, "/html/sensor_config.html", "text/html");
    request->send(LittleFS, "/html/sensor_config.html", String(), false, sensor_config_processor);
  });
  
  server.on("/sensorconfig2", HTTP_POST, [](AsyncWebServerRequest *request) {
    
    int params = request->params();
    for(int i=0;i<params;i++){
      const AsyncWebParameter* p = request->getParam(i);
      if(p->isPost()){
        if (p->name() == WIRE1_SENSOR0_TYPE) {
          wire1_sensor_data["wire1_sensor0"]["type"] = p->value().c_str();;
        }
        if (p->name() == WIRE1_SENSOR0_ADDRESS) {
          wire1_sensor_data["wire1_sensor0"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR0_VALVE) {
          wire1_sensor_data["wire1_sensor0"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR0_LOCATION) {
          wire1_sensor_data["wire1_sensor0"]["location"] = p->value().c_str();;
        }
        if (p->name() == WIRE1_SENSOR1_TYPE) {
          wire1_sensor_data["wire1_sensor1"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR1_ADDRESS) {
          wire1_sensor_data["wire1_sensor1"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR1_VALVE) {
          wire1_sensor_data["wire1_sensor1"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR1_LOCATION) {
          wire1_sensor_data["wire1_sensor1"]["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR2_TYPE) {
          wire1_sensor_data["wire1_sensor2"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR2_ADDRESS) {
          wire1_sensor_data["wire1_sensor2"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR2_VALVE) {
          wire1_sensor_data["wire1_sensor2"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR2_LOCATION) {
          wire1_sensor_data["wire1_sensor2"]["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR3_TYPE) {
          wire1_sensor_data["wire1_sensor3"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR3_ADDRESS) {
          wire1_sensor_data["wire1_sensor3"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR3_VALVE) {
          wire1_sensor_data["wire1_sensor3"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR3_LOCATION) {
          wire1_sensor_data["wire1_sensor3"]["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR4_TYPE) {
          wire1_sensor_data["wire1_sensor4"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR4_ADDRESS) {
          wire1_sensor_data["wire1_sensor4"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR4_VALVE) {
          wire1_sensor_data["wire1_sensor4"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR4_LOCATION) {
          wire1_sensor_data["wire1_sensor4"]["location"] = p->value().c_str(); 
        }
        if (p->name() == WIRE1_SENSOR5_TYPE) {
          wire1_sensor_data["wire1_sensor5"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR5_ADDRESS) {
          wire1_sensor_data["wire1_sensor5"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR5_VALVE) {
          wire1_sensor_data["wire1_sensor5"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR5_LOCATION) {
          wire1_sensor_data["wire1_sensor5"]["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR6_TYPE) {
          wire1_sensor_data["wire1_sensor6"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR6_ADDRESS) {
          wire1_sensor_data["wire1_sensor6"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR6_VALVE) {
          wire1_sensor_data["wire1_sensor6"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR6_LOCATION) {
          wire1_sensor_data["wire1_sensor6"]["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR7_TYPE) {
          wire1_sensor_data["wire1_sensor7"]["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR7_ADDRESS) {
          wire1_sensor_data["wire1_sensor7"]["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR7_VALVE) {
          wire1_sensor_data["wire1_sensor7"]["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR7_LOCATION) {
          wire1_sensor_data["wire1_sensor7"]["location"] = p->value().c_str();
        }
      }
    }
    const char* path2 = "/json/sensor_config2.json";
    String sensor_config2;

    serializeJson(wire1_sensor_data, sensor_config2);
    write_config_file(path2, sensor_config2);

    request->send(LittleFS, "/html/sensor_config.html", String(), false, sensor_config_processor);
  });

  // Start server
  server.begin();
  vTaskDelete(NULL);
}

/*
JSON valve_control_data Structure
{
    "valve0_data": [valve_vumber,valve move,valvemove_direction],
    "valve1_data": [valve_vumber,valve move,valvemove_direction],
    "valve2_data": [valve_vumber,valve move,valvemove_direction],
    ......
    ......
    "valve11_data": [valve_vumber,valve move,valvemove_direction]
}

JSON for sensor data. One dataset for one bus (wire,wire1)
{
  "sensors": [
    {
      "slot": 0,
      "type": "DHT20",
      "address": "0x3F",
      "valve": "valve0",
      "location": "bathroom",
      "rh": 1,
      "co2": 0
    },
    {
      "slot": 1,
      "type": "DHT20",
      "address": "0x70"
      "valve": "valve0",
      "location": "bathroom",
      "rh": 1,
      "co2": 0
    },
    {
      "slot": 7,
      "type": "SCD41",
      "address": "0x70"
      "valve": "valve0",
      "location": "bathroom",
      "rh": 1,
      "co2": 0
    },
  ]
}
*/