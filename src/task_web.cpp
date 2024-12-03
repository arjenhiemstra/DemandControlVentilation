#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>


#include "task_web.h"


TaskHandle_t Task_web;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void startTaskwebcode(void) {

    xTaskCreatePinnedToCore(Taskwebcode, "Task1", 10000, NULL, 1, &Task_web, 0);

}

void Taskwebcode(void * pvParameters)
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
    });

    // Start server
    server.begin();
    vTaskDelete(NULL);
}



