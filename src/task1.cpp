#include "task1.h"

TaskHandle_t Task1;

void startTask1code(void) {

    xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);

}

void Task1code(void * pvParameters)
{
  for( int i = 0;i<1000;i++ ) {
    Serial.print("\n\nTask1 running on core: ");
    Serial.print(xPortGetCoreID());
    vTaskDelay(500);
  }
  Serial.print("\nTask1 completed");
  vTaskDelete(NULL);
}



