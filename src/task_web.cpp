#include "task_web.h"
#include "config_files.h"

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

String valve0_position_move,valve0_direction;
String valve1_position_move,valve1_direction;
String valve2_position_move,valve2_direction;
String valve3_position_move,valve3_direction;
String valve4_position_move,valve4_direction;
String valve5_position_move,valve5_direction;
String valve6_position_move,valve6_direction;
String valve7_position_move,valve7_direction;
String valve8_position_move,valve8_direction;
String valve9_position_move,valve9_direction;
String valve10_position_move,valve10_direction;
String valve11_position_move,valve11_direction;
String check_valve_position;            // True when check is required if valve moves within operating range
String store_valve_position_in_file;    // True to enable storing of new position in valve position file

//Variables for sensor config page
const char* I2C1_SENSOR0_TYPE = "I2C1_sensor0_type";
const char* I2C1_SENSOR0_ADDRESS = "I2C1_sensor0_address";
const char* I2C1_SENSOR0_VALVE = "I2C1_sensor0_valve";
const char* I2C1_SENSOR0_LOCATION = "I2C1_sensor0_location";
const char* I2C1_SENSOR0_RH = "I2C1_sensor0_RH";
const char* I2C1_SENSOR0_CO2 = "I2C1_sensor0_CO2";
const char* I2C1_SENSOR1_TYPE = "I2C1_sensor1_type";
const char* I2C1_SENSOR1_ADDRESS = "I2C1_sensor1_address";
const char* I2C1_SENSOR1_VALVE = "I2C1_sensor1_valve";
const char* I2C1_SENSOR1_LOCATION = "I2C1_sensor1_location";
const char* I2C1_SENSOR1_RH = "I2C1_sensor1_RH";
const char* I2C1_SENSOR1_CO2 = "I2C1_sensor1_CO2";
const char* I2C1_SENSOR2_TYPE = "I2C1_sensor2_type";
const char* I2C1_SENSOR2_ADDRESS = "I2C1_sensor2_address";
const char* I2C1_SENSOR2_VALVE = "I2C1_sensor2_valve";
const char* I2C1_SENSOR2_LOCATION = "I2C1_sensor2_location";
const char* I2C1_SENSOR2_RH = "I2C1_sensor2_RH";
const char* I2C1_SENSOR2_CO2 = "I2C1_sensor2_CO2";
const char* I2C1_SENSOR3_TYPE = "I2C1_sensor3_type";
const char* I2C1_SENSOR3_ADDRESS = "I2C1_sensor3_address";
const char* I2C1_SENSOR3_VALVE = "I2C1_sensor3_valve";
const char* I2C1_SENSOR3_LOCATION = "I2C1_sensor3_location";
const char* I2C1_SENSOR3_RH = "I2C1_sensor3_RH";
const char* I2C1_SENSOR3_CO2 = "I2C1_sensor3_CO2";
const char* I2C1_SENSOR4_TYPE = "I2C1_sensor4_type";
const char* I2C1_SENSOR4_ADDRESS = "I2C1_sensor4_address";
const char* I2C1_SENSOR4_VALVE = "I2C1_sensor4_valve";
const char* I2C1_SENSOR4_LOCATION = "I2C1_sensor4_location";
const char* I2C1_SENSOR4_RH = "I2C1_sensor4_RH";
const char* I2C1_SENSOR4_CO2 = "I2C1_sensor4_CO2";
const char* I2C1_SENSOR5_TYPE = "I2C1_sensor5_type";
const char* I2C1_SENSOR5_ADDRESS = "I2C1_sensor5_address";
const char* I2C1_SENSOR5_VALVE = "I2C1_sensor5_valve";
const char* I2C1_SENSOR5_LOCATION = "I2C1_sensor5_location";
const char* I2C1_SENSOR5_RH = "I2C1_sensor5_RH";
const char* I2C1_SENSOR5_CO2 = "I2C1_sensor5_CO2";
const char* I2C1_SENSOR6_TYPE = "I2C1_sensor6_type";
const char* I2C1_SENSOR6_ADDRESS = "I2C1_sensor6_address";
const char* I2C1_SENSOR6_VALVE = "I2C1_sensor6_valve";
const char* I2C1_SENSOR6_LOCATION = "I2C1_sensor6_location";
const char* I2C1_SENSOR6_RH = "I2C1_sensor6_RH";
const char* I2C1_SENSOR6_CO2 = "I2C1_sensor6_CO2";
const char* I2C1_SENSOR7_TYPE = "I2C1_sensor7_type";
const char* I2C1_SENSOR7_ADDRESS = "I2C1_sensor7_address";
const char* I2C1_SENSOR7_VALVE = "I2C1_sensor7_valve";
const char* I2C1_SENSOR7_LOCATION = "I2C1_sensor7_location";
const char* I2C1_SENSOR7_RH = "I2C1_sensor7_RH";
const char* I2C1_SENSOR7_CO2 = "I2C1_sensor7_CO2";

const char* I2C2_SENSOR0_TYPE = "I2C2_sensor0_type";
const char* I2C2_SENSOR0_ADDRESS = "I2C2_sensor0_address";
const char* I2C2_SENSOR0_VALVE = "I2C2_sensor0_valve";
const char* I2C2_SENSOR0_LOCATION = "I2C2_sensor0_location";
const char* I2C2_SENSOR0_RH = "I2C2_sensor0_RH";
const char* I2C2_SENSOR0_CO2 = "I2C2_sensor0_CO2";
const char* I2C2_SENSOR1_TYPE = "I2C2_sensor1_type";
const char* I2C2_SENSOR1_ADDRESS = "I2C2_sensor1_address";
const char* I2C2_SENSOR1_VALVE = "I2C2_sensor1_valve";
const char* I2C2_SENSOR1_LOCATION = "I2C2_sensor1_location";
const char* I2C2_SENSOR1_RH = "I2C2_sensor1_RH";
const char* I2C2_SENSOR1_CO2 = "I2C2_sensor1_CO2";
const char* I2C2_SENSOR2_TYPE = "I2C2_sensor2_type";
const char* I2C2_SENSOR2_ADDRESS = "I2C2_sensor2_address";
const char* I2C2_SENSOR2_VALVE = "I2C2_sensor2_valve";
const char* I2C2_SENSOR2_LOCATION = "I2C2_sensor2_location";
const char* I2C2_SENSOR2_RH = "I2C2_sensor2_RH";
const char* I2C2_SENSOR2_CO2 = "I2C2_sensor2_CO2";
const char* I2C2_SENSOR3_TYPE = "I2C2_sensor3_type";
const char* I2C2_SENSOR3_ADDRESS = "I2C2_sensor3_address";
const char* I2C2_SENSOR3_VALVE = "I2C2_sensor3_valve";
const char* I2C2_SENSOR3_LOCATION = "I2C2_sensor3_location";
const char* I2C2_SENSOR3_RH = "I2C2_sensor3_RH";
const char* I2C2_SENSOR3_CO2 = "I2C2_sensor3_CO2";
const char* I2C2_SENSOR4_TYPE = "I2C2_sensor4_type";
const char* I2C2_SENSOR4_ADDRESS = "I2C2_sensor4_address";
const char* I2C2_SENSOR4_VALVE = "I2C2_sensor4_valve";
const char* I2C2_SENSOR4_LOCATION = "I2C2_sensor4_location";
const char* I2C2_SENSOR4_RH = "I2C2_sensor4_RH";
const char* I2C2_SENSOR4_CO2 = "I2C2_sensor4_CO2";
const char* I2C2_SENSOR5_TYPE = "I2C2_sensor5_type";
const char* I2C2_SENSOR5_ADDRESS = "I2C2_sensor5_address";
const char* I2C2_SENSOR5_VALVE = "I2C2_sensor5_valve";
const char* I2C2_SENSOR5_LOCATION = "I2C2_sensor5_location";
const char* I2C2_SENSOR5_RH = "I2C2_sensor5_RH";
const char* I2C2_SENSOR5_CO2 = "I2C2_sensor5_CO2";
const char* I2C2_SENSOR6_TYPE = "I2C2_sensor6_type";
const char* I2C2_SENSOR6_ADDRESS = "I2C2_sensor6_address";
const char* I2C2_SENSOR6_VALVE = "I2C2_sensor6_valve";
const char* I2C2_SENSOR6_LOCATION = "I2C2_sensor6_location";
const char* I2C2_SENSOR6_RH = "I2C2_sensor6_RH";
const char* I2C2_SENSOR6_CO2 = "I2C2_sensor6_CO2";
const char* I2C2_SENSOR7_TYPE = "I2C2_sensor7_type";
const char* I2C2_SENSOR7_ADDRESS = "I2C2_sensor7_address";
const char* I2C2_SENSOR7_VALVE = "I2C2_sensor7_valve";
const char* I2C2_SENSOR7_LOCATION = "I2C2_sensor7_location";
const char* I2C2_SENSOR7_RH = "I2C2_sensor7_RH";
const char* I2C2_SENSOR7_CO2 = "I2C2_sensor7_CO2";

/*
String I2C1_sensor0_type,I2C1_sensor0_address,I2C1_sensor0_valve,I2C1_sensor0_location,I2C1_sensor0_RH,I2C1_sensor0_CO2;
String I2C1_sensor1_type,I2C1_sensor1_address,I2C1_sensor1_valve,I2C1_sensor1_location,I2C1_sensor1_RH,I2C1_sensor1_CO2;
String I2C1_sensor2_type,I2C1_sensor2_address,I2C1_sensor2_valve,I2C1_sensor2_location,I2C1_sensor2_RH,I2C1_sensor2_CO2;
String I2C1_sensor3_type,I2C1_sensor3_address,I2C1_sensor3_valve,I2C1_sensor3_location,I2C1_sensor3_RH,I2C1_sensor3_CO2;
String I2C1_sensor4_type,I2C1_sensor4_address,I2C1_sensor4_valve,I2C1_sensor4_location,I2C1_sensor4_RH,I2C1_sensor4_CO2;
String I2C1_sensor5_type,I2C1_sensor5_address,I2C1_sensor5_valve,I2C1_sensor5_location,I2C1_sensor5_RH,I2C1_sensor5_CO2;
String I2C1_sensor6_type,I2C1_sensor6_address,I2C1_sensor6_valve,I2C1_sensor6_location,I2C1_sensor6_RH,I2C1_sensor6_CO2;
String I2C1_sensor7_type,I2C1_sensor7_address,I2C1_sensor7_valve,I2C1_sensor7_location,I2C1_sensor7_RH,I2C1_sensor7_CO2;

String I2C2_sensor0_type,I2C2_sensor0_address,I2C2_sensor0_valve,I2C2_sensor0_location,I2C2_sensor0_RH,I2C2_sensor0_CO2;
String I2C2_sensor1_type,I2C2_sensor1_address,I2C2_sensor1_valve,I2C2_sensor1_location,I2C2_sensor1_RH,I2C2_sensor1_CO2;
String I2C2_sensor2_type,I2C2_sensor2_address,I2C2_sensor2_valve,I2C2_sensor2_location,I2C2_sensor2_RH,I2C2_sensor2_CO2;
String I2C2_sensor3_type,I2C2_sensor3_address,I2C2_sensor3_valve,I2C2_sensor3_location,I2C2_sensor3_RH,I2C2_sensor3_CO2;
String I2C2_sensor4_type,I2C2_sensor4_address,I2C2_sensor4_valve,I2C2_sensor4_location,I2C2_sensor4_RH,I2C2_sensor4_CO2;
String I2C2_sensor5_type,I2C2_sensor5_address,I2C2_sensor5_valve,I2C2_sensor5_location,I2C2_sensor5_RH,I2C2_sensor5_CO2;
String I2C2_sensor6_type,I2C2_sensor6_address,I2C2_sensor6_valve,I2C2_sensor6_location,I2C2_sensor6_RH,I2C2_sensor6_CO2;
String I2C2_sensor7_type,I2C2_sensor7_address,I2C2_sensor7_valve,I2C2_sensor7_location,I2C2_sensor7_RH,I2C2_sensor7_CO2;
*/

//Global variables
JsonDocument valve_control_data;
JsonDocument I2C1_sensor_data;
JsonDocument I2C2_sensor_data;

//Make array of sensors inside JsonDocument for each sensor
JsonArray I2C1_sensors = I2C1_sensor_data["I2C1_sensors"].to<JsonArray>();
JsonObject I2C1_sensors0 = I2C1_sensors.add<JsonObject>();
JsonObject I2C1_sensors1 = I2C1_sensors.add<JsonObject>();
JsonObject I2C1_sensors2 = I2C1_sensors.add<JsonObject>();
JsonObject I2C1_sensors3 = I2C1_sensors.add<JsonObject>();
JsonObject I2C1_sensors4 = I2C1_sensors.add<JsonObject>();
JsonObject I2C1_sensors5 = I2C1_sensors.add<JsonObject>();
JsonObject I2C1_sensors6 = I2C1_sensors.add<JsonObject>();
JsonObject I2C1_sensors7 = I2C1_sensors.add<JsonObject>();

JsonArray I2C2_sensors = I2C2_sensor_data["I2C2_sensors"].to<JsonArray>();
JsonObject I2C2_sensors0 = I2C2_sensors.add<JsonObject>();
JsonObject I2C2_sensors1 = I2C2_sensors.add<JsonObject>();
JsonObject I2C2_sensors2 = I2C2_sensors.add<JsonObject>();
JsonObject I2C2_sensors3 = I2C2_sensors.add<JsonObject>();
JsonObject I2C2_sensors4 = I2C2_sensors.add<JsonObject>();
JsonObject I2C2_sensors5 = I2C2_sensors.add<JsonObject>();
JsonObject I2C2_sensors6 = I2C2_sensors.add<JsonObject>();
JsonObject I2C2_sensors7 = I2C2_sensors.add<JsonObject>();

void startTaskwebcode(void) {

    xTaskCreatePinnedToCore(Taskwebcode, "Task_web", 10000, NULL, 1, &h_Task_web, CONFIG_ARDUINO_RUNNING_CORE);
}

String processor(const String& var) {

  const char* path = "/valvepositions.json";
  const char* status;
  bool status_file_present;
  
  String json;
  JsonDocument doc;
  
  status_file_present = check_valve_position_file_exists(path);

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

void Taskwebcode(void *pvParameters) { 
 
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
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, processor);
  });

  //Response for POST action in webform valvecontrol manual move valves
  server.on("/valvecontrol", HTTP_POST, [](AsyncWebServerRequest *request) {
    int params = request->params();
    for(int i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
      if(p->isPost()){
        if (p->name() == VALVE0_POSITION_MOVE) {
          valve0_position_move = p->value().c_str();
          valve_control_data["valve0_data"][0] = 0;
          valve_control_data["valve0_data"][1] = valve0_position_move.toInt();
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
          valve1_position_move = p->value().c_str();
          valve_control_data["valve1_data"][0] = 1;
          valve_control_data["valve1_data"][1] = valve1_position_move.toInt();
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
          valve2_position_move = p->value().c_str();
          valve_control_data["valve2_data"][0] = 2;
          valve_control_data["valve2_data"][1] = valve2_position_move.toInt();
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
          valve3_position_move = p->value().c_str();
          valve_control_data["valve3_data"][0] = 3;
          valve_control_data["valve3_data"][1] = valve3_position_move.toInt();
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
          valve4_position_move = p->value().c_str();
          valve_control_data["valve4_data"][0] = 4;
          valve_control_data["valve4_data"][1] = valve4_position_move.toInt();
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
          valve5_position_move = p->value().c_str();
          valve_control_data["valve5_data"][0] = 5;
          valve_control_data["valve5_data"][1] = valve5_position_move.toInt();
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
          valve6_position_move = p->value().c_str();
          valve_control_data["valve6_data"][0] = 6;
          valve_control_data["valve6_data"][1] = valve6_position_move.toInt();
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
          valve7_position_move = p->value().c_str();
          valve_control_data["valve7_data"][0] = 7;
          valve_control_data["valve7_data"][1] = valve7_position_move.toInt();
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
          valve8_position_move = p->value().c_str();
          valve_control_data["valve8_data"][0] = 8;
          valve_control_data["valve8_data"][1] = valve8_position_move.toInt();
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
          valve9_position_move = p->value().c_str();
          valve_control_data["valve9_data"][0] = 9;
          valve_control_data["valve9_data"][1] = valve9_position_move.toInt();
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
          valve10_position_move = p->value().c_str();
          valve_control_data["valve10_data"][0] = 10;
          valve_control_data["valve10_data"][1] = valve10_position_move.toInt();
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
          valve11_position_move = p->value().c_str();
          valve_control_data["valve11_data"][0] = 11;
          valve_control_data["valve11_data"][1] = valve11_position_move.toInt();
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
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, processor);
    xTaskNotifyGive(xTaskGetHandle("task_valvectrl"));
  });

  //POST on button create config file - name must match with action of the form submit
  server.on("/create_config_file", HTTP_POST, [](AsyncWebServerRequest *request) {
    valve_status_file_create();
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, processor);
  });
    
  server.on("/delete_config_file", HTTP_POST, [](AsyncWebServerRequest *request) {
    const char* path = "/valvepositions.json";
    delete_file(path);
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, processor);
  });

  //Sensor config web page processing
  server.on("/sensorconfig", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/html/sensor_config.html", "text/html");
  });

  //Response for POST action in webform sensor_config
  I2C1_sensors0["slot"] = 0;
  I2C1_sensors1["slot"] = 1;
  I2C1_sensors2["slot"] = 2;
  I2C1_sensors3["slot"] = 3;
  I2C1_sensors4["slot"] = 4;
  I2C1_sensors5["slot"] = 5;
  I2C1_sensors6["slot"] = 6;
  I2C1_sensors7["slot"] = 7;

  server.on("/sensorconfig", HTTP_POST, [](AsyncWebServerRequest *request) {
    int params = request->params();
    for(int i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
      if(p->isPost()){
        if (p->name() == I2C1_SENSOR0_TYPE) {
          I2C1_sensors0["type"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR0_ADDRESS) {
          I2C1_sensors0["address"] = p->value().c_str();
        }     
        if (p->name() == I2C1_SENSOR0_VALVE) {
          I2C1_sensors0["valve"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR0_LOCATION) {
          I2C1_sensors0["location"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR0_RH) {
          I2C1_sensors0["rh"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR0_CO2) {
          I2C1_sensors0["co2"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR1_TYPE) {
          I2C1_sensors1["type"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR1_ADDRESS) {
          I2C1_sensors1["address"] = p->value().c_str();
        }     
        if (p->name() == I2C1_SENSOR1_VALVE) {
          I2C1_sensors1["valve"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR1_LOCATION) {
          I2C1_sensors1["location"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR1_RH) {
          I2C1_sensors1["rh"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR1_CO2) {
          I2C1_sensors1["co2"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR2_TYPE) {
          I2C1_sensors2["type"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR2_ADDRESS) {
          I2C1_sensors2["address"] = p->value().c_str();
        }     
        if (p->name() == I2C1_SENSOR2_VALVE) {
          I2C1_sensors2["valve"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR2_LOCATION) {
          I2C1_sensors2["location"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR2_RH) {
          I2C1_sensors2["rh"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR2_CO2) {
          I2C1_sensors2["co2"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR3_TYPE) {
          I2C1_sensors3["type"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR3_ADDRESS) {
          I2C1_sensors3["address"] = p->value().c_str();
        }     
        if (p->name() == I2C1_SENSOR3_VALVE) {
          I2C1_sensors3["valve"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR3_LOCATION) {
          I2C1_sensors3["location"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR3_RH) {
          I2C1_sensors3["rh"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR3_CO2) {
          I2C1_sensors3["co2"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR4_TYPE) {
          I2C1_sensors4["type"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR4_ADDRESS) {
          I2C1_sensors4["address"] = p->value().c_str();
        }     
        if (p->name() == I2C1_SENSOR4_VALVE) {
          I2C1_sensors4["valve"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR4_LOCATION) {
          I2C1_sensors4["location"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR4_RH) {
          I2C1_sensors4["rh"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR4_CO2) {
          I2C1_sensors4["co2"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR5_TYPE) {
          I2C1_sensors5["type"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR5_ADDRESS) {
          I2C1_sensors5["address"] = p->value().c_str();
        }     
        if (p->name() == I2C1_SENSOR5_VALVE) {
          I2C1_sensors5["valve"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR5_LOCATION) {
          I2C1_sensors5["location"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR5_RH) {
          I2C1_sensors5["rh"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR5_CO2) {
          I2C1_sensors5["co2"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR6_TYPE) {
          I2C1_sensors6["type"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR6_ADDRESS) {
          I2C1_sensors6["address"] = p->value().c_str();
        }     
        if (p->name() == I2C1_SENSOR6_VALVE) {
          I2C1_sensors6["valve"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR6_LOCATION) {
          I2C1_sensors6["location"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR6_RH) {
          I2C1_sensors6["rh"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR6_CO2) {
          I2C1_sensors6["co2"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR7_TYPE) {
          I2C1_sensors7["type"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR7_ADDRESS) {
          I2C1_sensors7["address"] = p->value().c_str();
        }     
        if (p->name() == I2C1_SENSOR7_VALVE) {
          I2C1_sensors7["valve"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR7_LOCATION) {
          I2C1_sensors7["location"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR7_RH) {
          I2C1_sensors7["rh"] = p->value().c_str();
        }
        if (p->name() == I2C1_SENSOR7_CO2) {
          I2C1_sensors7["co2"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR0_TYPE) {
          I2C2_sensors0["type"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR0_ADDRESS) {
          I2C2_sensors0["address"] = p->value().c_str();
        }     
        if (p->name() == I2C2_SENSOR0_VALVE) {
          I2C2_sensors0["valve"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR0_LOCATION) {
          I2C2_sensors0["location"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR0_RH) {
          I2C2_sensors0["rh"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR0_CO2) {
          I2C2_sensors0["co2"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR1_TYPE) {
          I2C2_sensors1["type"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR1_ADDRESS) {
          I2C2_sensors1["address"] = p->value().c_str();
        }     
        if (p->name() == I2C2_SENSOR1_VALVE) {
          I2C2_sensors1["valve"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR1_LOCATION) {
          I2C2_sensors1["location"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR1_RH) {
          I2C2_sensors1["rh"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR1_CO2) {
          I2C2_sensors1["co2"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR2_TYPE) {
          I2C2_sensors2["type"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR2_ADDRESS) {
          I2C2_sensors2["address"] = p->value().c_str();
        }     
        if (p->name() == I2C2_SENSOR2_VALVE) {
          I2C2_sensors2["valve"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR2_LOCATION) {
          I2C2_sensors2["location"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR2_RH) {
          I2C2_sensors2["rh"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR2_CO2) {
          I2C2_sensors2["co2"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR3_TYPE) {
          I2C2_sensors3["type"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR3_ADDRESS) {
          I2C2_sensors3["address"] = p->value().c_str();
        }     
        if (p->name() == I2C2_SENSOR3_VALVE) {
          I2C2_sensors3["valve"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR3_LOCATION) {
          I2C2_sensors3["location"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR3_RH) {
          I2C2_sensors3["rh"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR3_CO2) {
          I2C2_sensors3["co2"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR4_TYPE) {
          I2C2_sensors4["type"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR4_ADDRESS) {
          I2C2_sensors4["address"] = p->value().c_str();
        }     
        if (p->name() == I2C2_SENSOR4_VALVE) {
          I2C2_sensors4["valve"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR4_LOCATION) {
          I2C2_sensors4["location"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR4_RH) {
          I2C2_sensors4["rh"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR4_CO2) {
          I2C2_sensors4["co2"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR5_TYPE) {
          I2C2_sensors5["type"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR5_ADDRESS) {
          I2C2_sensors5["address"] = p->value().c_str();
        }     
        if (p->name() == I2C2_SENSOR5_VALVE) {
          I2C2_sensors5["valve"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR5_LOCATION) {
          I2C2_sensors5["location"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR5_RH) {
          I2C2_sensors5["rh"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR5_CO2) {
          I2C2_sensors5["co2"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR6_TYPE) {
          I2C2_sensors6["type"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR6_ADDRESS) {
          I2C2_sensors6["address"] = p->value().c_str();
        }     
        if (p->name() == I2C2_SENSOR6_VALVE) {
          I2C2_sensors6["valve"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR6_LOCATION) {
          I2C2_sensors6["location"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR6_RH) {
          I2C2_sensors6["rh"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR6_CO2) {
          I2C2_sensors6["co2"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR7_TYPE) {
          I2C2_sensors7["type"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR7_ADDRESS) {
          I2C2_sensors7["address"] = p->value().c_str();
        }     
        if (p->name() == I2C2_SENSOR7_VALVE) {
          I2C2_sensors7["valve"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR7_LOCATION) {
          I2C2_sensors7["location"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR7_RH) {
          I2C2_sensors7["rh"] = p->value().c_str();
        }
        if (p->name() == I2C2_SENSOR7_CO2) {
          I2C2_sensors7["co2"] = p->value().c_str();
        }
      }
    }
    request->send(LittleFS, "/html/sensor_config.html", "text/html");
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

JSON for sensor data. One dataset for one bus (I2C1,I2C2)
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
    .....
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