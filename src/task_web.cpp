#include "task_web.h"

TaskHandle_t Task_web;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char* VALVE0_POSITION_MOVE = "valve0_position_move";
const char* VALVE0_DIRECTION = "valve0_direction";
const char* VALVE1_POSITION_MOVE = "valve1_position_move";
const char* VALVE1_DIRECTION = "valve1_direction";

char output[256];

String valve0_position_move = "0";
String valve0_direction = "0";
String valve1_position_move = "0";
String valve1_direction = "0";

JsonDocument valve_movement_data;

bool enable_valve_position_check;   //True when check is required if valve moves within operating range

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
            Serial.print("Valve0 position move with: ");
            Serial.println(valve0_position_move);
          }
          if (p->name() == VALVE0_DIRECTION) {
            valve0_direction = p->value().c_str();
            Serial.print("Valve0 direction is: ");
            Serial.println(valve0_direction);
          }
          if (p->name() == VALVE1_POSITION_MOVE) {
            valve1_position_move = p->value().c_str();
            Serial.print("Valve1 position move with:: ");
            Serial.println(valve1_position_move);
          }
          if (p->name() == VALVE1_DIRECTION) {
            valve1_direction = p->value().c_str();
            Serial.print("Valve1 direction is: ");
            Serial.println(valve1_direction);
          }
        }
      }
      //request->send(200, "text/plain", "Done.");
      request->send(LittleFS, "/html/valvecontrol.html", "text/html");

      //No need to check if within operating range
      enable_valve_position_check = false;

      //assemble JSON from form input
      valve_movement_data["enable_valve_position_change"] = enable_valve_position_check;
      valve_movement_data["valve0_position_change"] = valve0_position_move;
      valve_movement_data["valve0_move_direction"] = valve0_direction;
      valve_movement_data["valve1_position_change"] = valve1_position_move;
      valve_movement_data["valve1_move_direction"] = valve1_direction;

      serializeJson(valve_movement_data, output);
    
      //call function to move valve
      move_valve(output);
    });

    // Start server
    server.begin();
    vTaskDelete(NULL);
}



