#include "task_wserial.h"

//AsyncWebServer ws_server(8080);
//WebSerial WebSerial;

void start_task_wserial(void) {

    xTaskCreate(task_wserial_code, "taskWserial", 10000, NULL, 1, &task_wserial);

}

void task_wserial_code(void * pvParameters) {

    //webSerial.onMessage([](const std::string& msg) { Serial.println(msg.c_str()); });
    //WebSerial.begin(&server);
    //webSerial.setBuffer(100);
    
    //Loop code for the task
    for(;;) { 
        //Serial.print("\nWebSerial task running...");
        //WebSerial.println("Message from task_wserial!");
        vTaskDelay(10000);
    }   
}