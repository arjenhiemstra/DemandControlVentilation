#include "task_web.h"
#include "config_files.h"

TaskHandle_t h_Task_web;
//TaskHandle_t Task1;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

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

char output[1024];

String valve0_position_move;
String valve0_direction;
String valve1_position_move;
String valve1_direction;
String valve2_position_move;
String valve2_direction;
String valve3_position_move;
String valve3_direction;
String valve4_position_move;
String valve4_direction;
String valve5_position_move;
String valve5_direction;
String valve6_position_move;
String valve6_direction;
String valve7_position_move;
String valve7_direction;
String valve8_position_move;
String valve8_direction;
String valve9_position_move;
String valve9_direction;
String valve10_position_move;
String valve10_direction;
String valve11_position_move;
String valve11_direction;
String check_valve_position;            // True when check is required if valve moves within operating range
String store_valve_position_in_file;    // True to enable storing of new position in valve position file

int i;
int params;

JsonDocument valve_control_data;
JsonDocument doc;

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

void Taskwebcode(void *pvParameters)
{ 
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
  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
    params = request->params();
    for(i=0;i<params;i++){
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
    //request->send(LittleFS, "/html/valvecontrol.html", "text/html");
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, processor);
    serializeJson(valve_control_data, output);
    //move_valve(output);
    xTaskNotifyGive(xTaskGetHandle("task_valvectrl"));
  });

  //POST on button create config file - name must match with action of the form submit
  server.on("/create_config_file", HTTP_POST, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/html/valvecontrol.html", "text/html");
    valve_status_file_create();
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, processor);
  });
    
  server.on("/delete_config_file", HTTP_POST, [](AsyncWebServerRequest *request) {
    //request->send(LittleFS, "/html/valvecontrol.html", "text/html");
    const char* path = "/valvepositions.json";
    delete_file(path);
    request->send(LittleFS, "/html/valvecontrol.html", String(), false, processor);
  });

  // Start server
  server.begin();
  vTaskDelete(NULL);
}

//JSON valve_control_data Structure
/*{
    "valve0_data": [valve_vumber,valve move,valvemove_direction],
    "valve1_data": [valve_vumber,valve move,valvemove_direction],
    "valve2_data": [valve_vumber,valve move,valvemove_direction],
    ......
    ......
    "valve11_data": [valve_vumber,valve move,valvemove_direction]
  }









}*/
