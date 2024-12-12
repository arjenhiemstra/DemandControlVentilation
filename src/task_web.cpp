#include "task_web.h"

const char* PARAM_INPUT_1 = "ssid";



TaskHandle_t Task_web;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char* VALVE0_POSITION_MOVE = "valve0_position_move";
const char* VALVE0_DIRECTION = "valve0_direction";
const char* VALVE1_POSITION_MOVE = "valve1_position_move";
const char* VALVE1_DIRECTION = "valve1_direction";

String valve0_position_move;
String valve0_direction;
String valve1_position_move;
String valve1_direction;


/* void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
} */

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
            Serial.print(i);
            Serial.print("Valve0 position move with: ");
            Serial.println(valve0_position_move);
          }
          if (p->name() == VALVE0_DIRECTION) {
            valve0_direction = p->value().c_str();
            Serial.print(i);
            Serial.print("Valve0 direction is: ");
            Serial.println(valve0_direction);
          }
          if (p->name() == VALVE1_POSITION_MOVE) {
            valve1_position_move = p->value().c_str();
            Serial.print(i);
            Serial.print("Valve1 position move with:: ");
            Serial.println(valve1_position_move);
          }
          if (p->name() == VALVE1_DIRECTION) {
            valve1_direction = p->value().c_str();
            Serial.print(i);
            Serial.print("Valve1 direction is: ");
            Serial.println(valve1_direction);
          }
        }
      }
      request->send(200, "text/plain", "Done.");
      Serial.println(valve1_direction);
    });

    // Start server
    server.begin();
    vTaskDelete(NULL);
}



