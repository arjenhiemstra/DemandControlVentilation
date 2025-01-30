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
const char* WIRE_SENSOR0_RH = "wire_sensor0_RH";
const char* WIRE_SENSOR0_CO2 = "wire_sensor0_CO2";
const char* WIRE_SENSOR1_TYPE = "wire_sensor1_type";
const char* WIRE_SENSOR1_ADDRESS = "wire_sensor1_address";
const char* WIRE_SENSOR1_VALVE = "wire_sensor1_valve";
const char* WIRE_SENSOR1_LOCATION = "wire_sensor1_location";
const char* WIRE_SENSOR1_RH = "wire_sensor1_RH";
const char* WIRE_SENSOR1_CO2 = "wire_sensor1_CO2";
const char* WIRE_SENSOR2_TYPE = "wire_sensor2_type";
const char* WIRE_SENSOR2_ADDRESS = "wire_sensor2_address";
const char* WIRE_SENSOR2_VALVE = "wire_sensor2_valve";
const char* WIRE_SENSOR2_LOCATION = "wire_sensor2_location";
const char* WIRE_SENSOR2_RH = "wire_sensor2_RH";
const char* WIRE_SENSOR2_CO2 = "wire_sensor2_CO2";
const char* WIRE_SENSOR3_TYPE = "wire_sensor3_type";
const char* WIRE_SENSOR3_ADDRESS = "wire_sensor3_address";
const char* WIRE_SENSOR3_VALVE = "wire_sensor3_valve";
const char* WIRE_SENSOR3_LOCATION = "wire_sensor3_location";
const char* WIRE_SENSOR3_RH = "wire_sensor3_RH";
const char* WIRE_SENSOR3_CO2 = "wire_sensor3_CO2";
const char* WIRE_SENSOR4_TYPE = "wire_sensor4_type";
const char* WIRE_SENSOR4_ADDRESS = "wire_sensor4_address";
const char* WIRE_SENSOR4_VALVE = "wire_sensor4_valve";
const char* WIRE_SENSOR4_LOCATION = "wire_sensor4_location";
const char* WIRE_SENSOR4_RH = "wire_sensor4_RH";
const char* WIRE_SENSOR4_CO2 = "wire_sensor4_CO2";
const char* WIRE_SENSOR5_TYPE = "wire_sensor5_type";
const char* WIRE_SENSOR5_ADDRESS = "wire_sensor5_address";
const char* WIRE_SENSOR5_VALVE = "wire_sensor5_valve";
const char* WIRE_SENSOR5_LOCATION = "wire_sensor5_location";
const char* WIRE_SENSOR5_RH = "wire_sensor5_RH";
const char* WIRE_SENSOR5_CO2 = "wire_sensor5_CO2";
const char* WIRE_SENSOR6_TYPE = "wire_sensor6_type";
const char* WIRE_SENSOR6_ADDRESS = "wire_sensor6_address";
const char* WIRE_SENSOR6_VALVE = "wire_sensor6_valve";
const char* WIRE_SENSOR6_LOCATION = "wire_sensor6_location";
const char* WIRE_SENSOR6_RH = "wire_sensor6_RH";
const char* WIRE_SENSOR6_CO2 = "wire_sensor6_CO2";
const char* WIRE_SENSOR7_TYPE = "wire_sensor7_type";
const char* WIRE_SENSOR7_ADDRESS = "wire_sensor7_address";
const char* WIRE_SENSOR7_VALVE = "wire_sensor7_valve";
const char* WIRE_SENSOR7_LOCATION = "wire_sensor7_location";
const char* WIRE_SENSOR7_RH = "wire_sensor7_RH";
const char* WIRE_SENSOR7_CO2 = "wire_sensor7_CO2";

const char* WIRE1_SENSOR0_TYPE = "wire1_sensor0_type";
const char* WIRE1_SENSOR0_ADDRESS = "wire1_sensor0_address";
const char* WIRE1_SENSOR0_VALVE = "wire1_sensor0_valve";
const char* WIRE1_SENSOR0_LOCATION = "wire1_sensor0_location";
const char* WIRE1_SENSOR0_RH = "wire1_sensor0_RH";
const char* WIRE1_SENSOR0_CO2 = "wire1_sensor0_CO2";
const char* WIRE1_SENSOR1_TYPE = "wire1_sensor1_type";
const char* WIRE1_SENSOR1_ADDRESS = "wire1_sensor1_address";
const char* WIRE1_SENSOR1_VALVE = "wire1_sensor1_valve";
const char* WIRE1_SENSOR1_LOCATION = "wire1_sensor1_location";
const char* WIRE1_SENSOR1_RH = "wire1_sensor1_RH";
const char* WIRE1_SENSOR1_CO2 = "wire1_sensor1_CO2";
const char* WIRE1_SENSOR2_TYPE = "wire1_sensor2_type";
const char* WIRE1_SENSOR2_ADDRESS = "wire1_sensor2_address";
const char* WIRE1_SENSOR2_VALVE = "wire1_sensor2_valve";
const char* WIRE1_SENSOR2_LOCATION = "wire1_sensor2_location";
const char* WIRE1_SENSOR2_RH = "wire1_sensor2_RH";
const char* WIRE1_SENSOR2_CO2 = "wire1_sensor2_CO2";
const char* WIRE1_SENSOR3_TYPE = "wire1_sensor3_type";
const char* WIRE1_SENSOR3_ADDRESS = "wire1_sensor3_address";
const char* WIRE1_SENSOR3_VALVE = "wire1_sensor3_valve";
const char* WIRE1_SENSOR3_LOCATION = "wire1_sensor3_location";
const char* WIRE1_SENSOR3_RH = "wire1_sensor3_RH";
const char* WIRE1_SENSOR3_CO2 = "wire1_sensor3_CO2";
const char* WIRE1_SENSOR4_TYPE = "wire1_sensor4_type";
const char* WIRE1_SENSOR4_ADDRESS = "wire1_sensor4_address";
const char* WIRE1_SENSOR4_VALVE = "wire1_sensor4_valve";
const char* WIRE1_SENSOR4_LOCATION = "wire1_sensor4_location";
const char* WIRE1_SENSOR4_RH = "wire1_sensor4_RH";
const char* WIRE1_SENSOR4_CO2 = "wire1_sensor4_CO2";
const char* WIRE1_SENSOR5_TYPE = "wire1_sensor5_type";
const char* WIRE1_SENSOR5_ADDRESS = "wire1_sensor5_address";
const char* WIRE1_SENSOR5_VALVE = "wire1_sensor5_valve";
const char* WIRE1_SENSOR5_LOCATION = "wire1_sensor5_location";
const char* WIRE1_SENSOR5_RH = "wire1_sensor5_RH";
const char* WIRE1_SENSOR5_CO2 = "wire1_sensor5_CO2";
const char* WIRE1_SENSOR6_TYPE = "wire1_sensor6_type";
const char* WIRE1_SENSOR6_ADDRESS = "wire1_sensor6_address";
const char* WIRE1_SENSOR6_VALVE = "wire1_sensor6_valve";
const char* WIRE1_SENSOR6_LOCATION = "wire1_sensor6_location";
const char* WIRE1_SENSOR6_RH = "wire1_sensor6_RH";
const char* WIRE1_SENSOR6_CO2 = "wire1_sensor6_CO2";
const char* WIRE1_SENSOR7_TYPE = "wire1_sensor7_type";
const char* WIRE1_SENSOR7_ADDRESS = "wire1_sensor7_address";
const char* WIRE1_SENSOR7_VALVE = "wire1_sensor7_valve";
const char* WIRE1_SENSOR7_LOCATION = "wire1_sensor7_location";
const char* WIRE1_SENSOR7_RH = "wire1_sensor7_RH";
const char* WIRE1_SENSOR7_CO2 = "wire1_sensor7_CO2";

const char* WIRE_SENSOR_CONFIG = "wire_sensor_config";
const char* WIRE1_SENSOR_CONFIG = "wire1_sensor_config";

/*
String wire_sensor_config_string;
String wire1_sensor_config_string;

//Globals defined in globals.cpp
extern JsonDocument valve_control_data;
extern JsonDocument wire_sensor_data;
extern JsonDocument wire1_sensor_data;

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
extern JsonObject wire1_sensors7;*/

void startTaskwebcode(void) {

  xTaskCreatePinnedToCore(Taskwebcode, "Task_web", 10000, NULL, 1, &h_Task_web, 0);

}

void Taskwebcode(void *pvParameters) {

  //extern SemaphoreHandle_t sensor_config_file_mutex;
  //sensor_config_file_mutex = xSemaphoreCreateMutex();
    
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/html//index.html", "text/html");
  });

  server.on("/css/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/css/styles.css", "text/css");
  });

  server.on("/js/ui.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/js/ui.js", "text/javascript");
  });

  //Not found handling
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "The content you are looking for was not found.");
  });

  //Settings web pages processing
  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/html/settings.html", "text/html");
  });

  //Valve control web pages processing
  server.on("/valvecontrol", HTTP_GET, [](AsyncWebServerRequest *request){
    //request->send(LittleFS, "/html/valvecontrol.html", "text/html");
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, valvecontrol_processor);
  });

  //Response for POST action in webform valvecontrol manual move valves
  server.on("/valvecontrol", HTTP_POST, [](AsyncWebServerRequest *request) {
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
          if (valve0_direction == "Forward") {
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
          if (valve1_direction == "Forward") {
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
          if (valve2_direction == "Forward") {
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
          if (valve3_direction == "Forward") {
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
          if (valve4_direction == "Forward") {
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
          if (valve5_direction == "Forward") {
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
          if (valve6_direction == "Forward") {
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
          if (valve7_direction == "Forward") {
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
          if (valve8_direction == "Forward") {
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
          if (valve9_direction == "Forward") {
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
          if (valve10_direction == "Forward") {
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
          if (valve11_direction == "Forward") {
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
    xTaskNotifyGive(xTaskGetHandle("task_valvectrl"));
  });

  //POST on button create config file - name must match with action of the form submit
  server.on("/create_config_file", HTTP_POST, [](AsyncWebServerRequest *request) {
    valve_status_file_create();
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, valvecontrol_processor);
  });
    
  server.on("/delete_config_file", HTTP_POST, [](AsyncWebServerRequest *request) {
    const char* path = "/valvepositions.json";
    delete_file(path);
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, valvecontrol_processor);
  });

  //Sensor config web page processing
  server.on("/sensorconfig", HTTP_GET, [](AsyncWebServerRequest *request){

    //xSemaphoreTake(sensor_config_file_mutex, portMAX_DELAY);
    //sensor_config_data_read();
    serializeJson(wire_sensor_data, wire_sensor_config_string);
    serializeJson(wire1_sensor_data, wire1_sensor_config_string);

    //xSemaphoreGive(sensor_config_file_mutex);
    //request->send(LittleFS, "/html/sensor_config.html", "text/html");
    request->send(LittleFS, "/html/sensor_config.html", String(), false, sensor_config_processor);
  });

  server.on("/delete_sensor_config_file1", HTTP_POST, [](AsyncWebServerRequest *request) {
    const char* path = "/sensor_config1.json";
    delete_file(path);
    request->send(LittleFS, "/html/sensor_config.html", String(), false, sensor_config_processor);
  });

  server.on("/delete_sensor_config_file2", HTTP_POST, [](AsyncWebServerRequest *request) {
    const char* path = "/sensor_config2.json";
    delete_file(path);
    request->send(LittleFS, "/html/sensor_config.html", String(), false, sensor_config_processor);
  });
  
  server.on("/sensorconfig1", HTTP_POST, [](AsyncWebServerRequest *request) {
    //xSemaphoreTake(sensor_config_file_mutex, portMAX_DELAY);
    int params = request->params();
    for(int i=0;i<params;i++){
      const AsyncWebParameter* p = request->getParam(i);
      if(p->isPost()){
        if (p->name() == WIRE_SENSOR0_TYPE) {
          wire_sensors0["type"] = p->value().c_str();;
        }
        if (p->name() == WIRE_SENSOR0_ADDRESS) {
          wire_sensors0["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR0_VALVE) {
          wire_sensors0["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR0_LOCATION) {
          wire_sensors0["location"] = p->value().c_str();;
        }
        if (p->name() == WIRE_SENSOR0_RH) {
          wire_sensors0["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR0_CO2) {
          wire_sensors0["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR1_TYPE) {
          wire_sensors1["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR1_ADDRESS) {
          wire_sensors1["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR1_VALVE) {
          wire_sensors1["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR1_LOCATION) {
          wire_sensors1["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR1_RH) {
          wire_sensors1["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR1_CO2) {
          wire_sensors1["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR2_TYPE) {
          wire_sensors2["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR2_ADDRESS) {
          wire_sensors2["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR2_VALVE) {
          wire_sensors2["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR2_LOCATION) {
          wire_sensors2["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR2_RH) {
          wire_sensors2["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR2_CO2) {
          wire_sensors2["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR3_TYPE) {
          wire_sensors3["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR3_ADDRESS) {
          wire_sensors3["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR3_VALVE) {
          wire_sensors3["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR3_LOCATION) {
          wire_sensors3["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR3_RH) {
          wire_sensors3["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR3_CO2) {
          wire_sensors3["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR4_TYPE) {
          wire_sensors4["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR4_ADDRESS) {
          wire_sensors4["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR4_VALVE) {
          wire_sensors4["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR4_LOCATION) {
          wire_sensors4["location"] = p->value().c_str(); 
        }
        if (p->name() == WIRE_SENSOR4_RH) {
          wire_sensors4["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR4_CO2) {
          wire_sensors4["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR5_TYPE) {
          wire_sensors5["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR5_ADDRESS) {
          wire_sensors5["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR5_VALVE) {
          wire_sensors5["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR5_LOCATION) {
          wire_sensors5["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR5_RH) {
          wire_sensors5["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR5_CO2) {
          wire_sensors5["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR6_TYPE) {
          wire_sensors6["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR6_ADDRESS) {
          wire_sensors6["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR6_VALVE) {
          wire_sensors6["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR6_LOCATION) {
          wire_sensors6["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR6_RH) {
          wire_sensors6["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR6_CO2) {
          wire_sensors6["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR7_TYPE) {
          wire_sensors7["type"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR7_ADDRESS) {
          wire_sensors7["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE_SENSOR7_VALVE) {
          wire_sensors7["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR7_LOCATION) {
          wire_sensors7["location"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR7_RH) {
          wire_sensors7["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE_SENSOR7_CO2) {
          wire_sensors7["co2"] = p->value().c_str();
        }
      }
    }
    
    const char* path1 = "/sensor_config1.json";
    String sensor_config1;

    serializeJson(wire_sensor_data, sensor_config1);
    write_config_file(path1, sensor_config1);
    
    /*wire_sensors0["slot"] = 0;
    wire_sensors1["slot"] = 1;
    wire_sensors2["slot"] = 2;
    wire_sensors3["slot"] = 3;
    wire_sensors4["slot"] = 4;
    wire_sensors5["slot"] = 5;
    wire_sensors6["slot"] = 6;
    wire_sensors7["slot"] = 7;*/
    
    Serial.print("\n\n");
    serializeJson(wire_sensor_data, Serial);
    Serial.print("\n\n");
 
    //xSemaphoreGive(sensor_config_file_mutex);
    //request->send(LittleFS, "/html/sensor_config.html", "text/html");
    request->send(LittleFS, "/html/sensor_config.html", String(), false, sensor_config_processor); 
  });
  
  server.on("/sensorconfig2", HTTP_POST, [](AsyncWebServerRequest *request) {
    //xSemaphoreTake(sensor_config_file_mutex, portMAX_DELAY);
    int params = request->params();
    for(int i=0;i<params;i++){
      const AsyncWebParameter* p = request->getParam(i);
      if(p->isPost()){
        if (p->name() == WIRE1_SENSOR0_TYPE) {
          wire1_sensors0["type"] = p->value().c_str();;
        }
        if (p->name() == WIRE1_SENSOR0_ADDRESS) {
          wire1_sensors0["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR0_VALVE) {
          wire1_sensors0["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR0_LOCATION) {
          wire1_sensors0["location"] = p->value().c_str();;
        }
        if (p->name() == WIRE1_SENSOR0_RH) {
          wire1_sensors0["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR0_CO2) {
          wire1_sensors0["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR1_TYPE) {
          wire1_sensors1["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR1_ADDRESS) {
          wire1_sensors1["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR1_VALVE) {
          wire1_sensors1["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR1_LOCATION) {
          wire1_sensors1["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR1_RH) {
          wire1_sensors1["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR1_CO2) {
          wire1_sensors1["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR2_TYPE) {
          wire1_sensors2["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR2_ADDRESS) {
          wire1_sensors2["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR2_VALVE) {
          wire1_sensors2["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR2_LOCATION) {
          wire1_sensors2["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR2_RH) {
          wire1_sensors2["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR2_CO2) {
          wire1_sensors2["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR3_TYPE) {
          wire1_sensors3["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR3_ADDRESS) {
          wire1_sensors3["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR3_VALVE) {
          wire1_sensors3["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR3_LOCATION) {
          wire1_sensors3["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR3_RH) {
          wire1_sensors3["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR3_CO2) {
          wire1_sensors3["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR4_TYPE) {
          wire1_sensors4["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR4_ADDRESS) {
          wire1_sensors4["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR4_VALVE) {
          wire1_sensors4["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR4_LOCATION) {
          wire1_sensors4["location"] = p->value().c_str(); 
        }
        if (p->name() == WIRE1_SENSOR4_RH) {
          wire1_sensors4["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR4_CO2) {
          wire1_sensors4["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR5_TYPE) {
          wire1_sensors5["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR5_ADDRESS) {
          wire1_sensors5["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR5_VALVE) {
          wire1_sensors5["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR5_LOCATION) {
          wire1_sensors5["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR5_RH) {
          wire1_sensors5["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR5_CO2) {
          wire1_sensors5["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR6_TYPE) {
          wire1_sensors6["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR6_ADDRESS) {
          wire1_sensors6["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR6_VALVE) {
          wire1_sensors6["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR6_LOCATION) {
          wire1_sensors6["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR6_RH) {
          wire1_sensors6["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR6_CO2) {
          wire1_sensors6["co2"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR7_TYPE) {
          wire1_sensors7["type"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR7_ADDRESS) {
          wire1_sensors7["address"] = p->value().c_str();
        }     
        if (p->name() == WIRE1_SENSOR7_VALVE) {
          wire1_sensors7["valve"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR7_LOCATION) {
          wire1_sensors7["location"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR7_RH) {
          wire1_sensors7["rh"] = p->value().c_str();
        }
        if (p->name() == WIRE1_SENSOR7_CO2) {
          wire1_sensors7["co2"] = p->value().c_str();
        }
      }
    }
    
    const char* path2 = "/sensor_config2.json";
    String sensor_config2;

    serializeJson(wire1_sensor_data, sensor_config2);
    write_config_file(path2, sensor_config2);
    
    /*wire1_sensors0["slot"] = 0;
    wire1_sensors1["slot"] = 1;
    wire1_sensors2["slot"] = 2;
    wire1_sensors3["slot"] = 3;
    wire1_sensors4["slot"] = 4;
    wire1_sensors5["slot"] = 5;
    wire1_sensors6["slot"] = 6;
    wire1_sensors7["slot"] = 7;*/
    
    Serial.print("\n\n");
    serializeJson(wire1_sensor_data, Serial);
    Serial.print("\n\n");
    
    //xSemaphoreGive(sensor_config_file_mutex);
    //request->send(LittleFS, "/html/sensor_config.html", "text/html");
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