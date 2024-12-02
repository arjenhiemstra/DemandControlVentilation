#include "task2.h"

TaskHandle_t Task2;

void startTask2code(void) {

    xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, &Task2, 1);
}

void Task2code(void * pvParameters) {

    for( int i = 0;i<10;i++ ) {
        Serial.print("\n\nTask2 running on core: ");
        Serial.print(xPortGetCoreID());
        vTaskDelay(800);
    }
    Serial.print("\nTask2 completed");
    vTaskDelete(NULL);
}