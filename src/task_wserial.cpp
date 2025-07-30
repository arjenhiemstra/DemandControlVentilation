#include "task_wserial.h"

AsyncWebServer ws_server(8080);
WebSerial webSerial;
//WebSerial *webSerial = nullptr;

void start_task_wserial(void) {

    xTaskCreate(task_wserial_code, "taskWserial", 10000, NULL, 1, &task_wserial);
}

void task_wserial_code(void * pvParameters) {

    char rxBuffer[400];
    String datetime = "";
    String rxString = "";
    String message = "";
    
    webSerial.onMessage([](const std::string& msg) { Serial.println(msg.c_str()); });
    webSerial.begin(&ws_server);
    webSerial.setBuffer(100);
    ws_server.begin();  

    //webSerial = new WebSerial();
    //webSerial->onMessage([](const std::string& msg) { Serial.println(msg.c_str()); });
    //webSerial->begin(&ws_server);
        
    //Loop code for the task
    for(;;) { 
        if (xQueueReceive(webserial_queue, rxBuffer, 50) == pdPASS) {
            rxString = String(rxBuffer);
            datetime = formatted_datetime();
            message = datetime + " - " + rxString;
            Serial.print("\n" + message);
            webSerial.print("\n" + message);
        }
        vTaskDelay(500);
    }   
}