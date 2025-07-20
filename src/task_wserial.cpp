#include "task_wserial.h"

AsyncWebServer ws_server(8080);
WebSerial webSerial;

void start_task_wserial(void) {

    xTaskCreate(task_wserial_code, "taskWserial", 10000, NULL, 1, &task_wserial);
}

void task_wserial_code(void * pvParameters) {

    webSerial.onMessage([](const std::string& msg) { Serial.println(msg.c_str()); });
    webSerial.begin(&ws_server);
    webSerial.setBuffer(100);
    ws_server.begin();
    
    //Loop code for the task
    for(;;) { 
        Serial.print("\nWebSerial task running...");
        webSerial.println("Message from task_wserial!");
        vTaskDelay(10000);
    }   
}