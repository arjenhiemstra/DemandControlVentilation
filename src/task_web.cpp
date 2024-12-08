#include "task_web.h"

const char* PARAM_INPUT_1 = "ssid";



TaskHandle_t Task_web;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

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

    //server.onNotFound(notFound);

    // Start server
    server.begin();
    vTaskDelete(NULL);
}



