#include "task_web.h"

TaskHandle_t Task_web;

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

JsonDocument valve_movement_data;

bool enable_valve_position_check;   //True when check is required if valve moves within operating range

//int i;

void startTaskwebcode(void) {

    xTaskCreatePinnedToCore(Taskwebcode, "Task1", 10000, NULL, 1, &Task_web, 0);
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

    //Valve control web pages processing
    server.on("/valvecontrol", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/html/valvecontrol.html", "text/html");
    });

    //Response for POST action in webform valvecontrol manual move valves
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          if (p->name() == VALVE0_POSITION_MOVE) {
            valve0_position_move = p->value().c_str();
            valve_movement_data["valve0_data"][0] = 0;
            valve_movement_data["valve0_data"][1] = valve0_position_move.toInt();
          }
          if (p->name() == VALVE0_DIRECTION) {
            valve0_direction = p->value().c_str();
            valve_movement_data["valve0_data"][2] = valve0_direction;
          }
          if (p->name() == VALVE1_POSITION_MOVE) {
            valve1_position_move = p->value().c_str();
            valve_movement_data["valve1_number"] = 1;
            valve_movement_data["valve1_position_move"] = valve1_position_move.toInt();
          }
          if (p->name() == VALVE1_DIRECTION) {
            valve1_direction = p->value().c_str();
            valve_movement_data["valve1_direction"] = valve1_direction;
          }
          if (p->name() == VALVE2_POSITION_MOVE) {
            valve2_position_move = p->value().c_str();
            valve_movement_data["valve2_number"] = 2;
            valve_movement_data["valve2_position_move"] = valve2_position_move.toInt();
          }
          if (p->name() == VALVE2_DIRECTION) {
            valve2_direction = p->value().c_str();
            valve_movement_data["valve2_direction"] = valve2_direction;
          }
          if (p->name() == VALVE3_POSITION_MOVE) {
            valve3_position_move = p->value().c_str();
            valve_movement_data["valve3_number"] = 3;
            valve_movement_data["valve3_position_move"] = valve3_position_move.toInt();
          }
          if (p->name() == VALVE3_DIRECTION) {
            valve3_direction = p->value().c_str();
            valve_movement_data["valve3_direction"] = valve3_direction;
          }
          if (p->name() == VALVE4_POSITION_MOVE) {
            valve4_position_move = p->value().c_str();
            valve_movement_data["valve4_number"] = 4;
            valve_movement_data["valve4_position_move"] = valve4_position_move.toInt();
          }
          if (p->name() == VALVE4_DIRECTION) {
            valve4_direction = p->value().c_str();
            valve_movement_data["valve4_direction"] = valve4_direction;
          }
          if (p->name() == VALVE5_POSITION_MOVE) {
            valve5_position_move = p->value().c_str();
            valve_movement_data["valve5_number"] = 5;
            valve_movement_data["valve5_position_move"] = valve5_position_move.toInt();
          }
          if (p->name() == VALVE5_DIRECTION) {
            valve5_direction = p->value().c_str();
            valve_movement_data["valve5_direction"] = valve5_direction;
          }
          if (p->name() == VALVE6_POSITION_MOVE) {
            valve6_position_move = p->value().c_str();
            valve_movement_data["valve6_position_move"] = valve6_position_move.toInt();
          }
          if (p->name() == VALVE6_DIRECTION) {
            valve6_direction = p->value().c_str();
            valve_movement_data["valve6_direction"] = valve6_direction;
          }
          if (p->name() == VALVE7_POSITION_MOVE) {
            valve7_position_move = p->value().c_str();
            valve_movement_data["valve7_position_move"] = valve7_position_move.toInt();
          }
          if (p->name() == VALVE7_DIRECTION) {
            valve7_direction = p->value().c_str();
            valve_movement_data["valve7_direction"] = valve7_direction;
          }
          if (p->name() == VALVE8_POSITION_MOVE) {
            valve8_position_move = p->value().c_str();
            valve_movement_data["valve8_position_move"] = valve8_position_move.toInt();
          }
          if (p->name() == VALVE8_DIRECTION) {
            valve8_direction = p->value().c_str();
            valve_movement_data["valve8_direction"] = valve8_direction;
          }
          if (p->name() == VALVE9_POSITION_MOVE) {
            valve9_position_move = p->value().c_str();
            valve_movement_data["valve9_position_move"] = valve9_position_move.toInt();
          }
          if (p->name() == VALVE9_DIRECTION) {
            valve9_direction = p->value().c_str();
            valve_movement_data["valve9_direction"] = valve9_direction;
          }
          if (p->name() == VALVE10_POSITION_MOVE) {
            valve10_position_move = p->value().c_str();
            valve_movement_data["valve10_position_move"] = valve10_position_move.toInt();
          }
          if (p->name() == VALVE10_DIRECTION) {
            valve10_direction = p->value().c_str();
            valve_movement_data["valve10_direction"] = valve10_direction;
          }
          if (p->name() == VALVE11_POSITION_MOVE) {
            valve11_position_move = p->value().c_str();
            valve_movement_data["valve11_position_move"] = valve11_position_move.toInt();
          }
          if (p->name() == VALVE11_DIRECTION) {
            valve11_direction = p->value().c_str();
            valve_movement_data["valve11_direction"] = valve11_direction;
          }
        }
      }
      //request->send(200, "text/plain", "Done.");
      request->send(LittleFS, "/html/valvecontrol.html", "text/html");

      //No need to check if within operating range
      enable_valve_position_check = false;

      serializeJson(valve_movement_data, output);
    
      //call function to move valve
      move_valve(output);
    });

    // Start server
    server.begin();
    vTaskDelete(NULL);
}

//JSON Structure
/*{
    "valve_control_data": [
        {
            "valve_number": 0,
            "valve_position_move": 0,
            "valve_direction": "Forward"
        },
        {
            "valve_number": 1,
            "valve_position_move": 4,
            "valve_direction": "Forward"
        },
        {
            "valve_number": 2,
            "valve_position_move": 4,
            "valve_direction": "Backwards"
        }
    ]
}*/
