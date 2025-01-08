#include "task1.h"

TaskHandle_t Task1;

void startTask1code(void) {

    xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);

}

void Task1code(void * pvParameters)
{
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  Serial.print("\n\nTask1 running on core: ");
  Serial.print(xPortGetCoreID());
  //vTaskDelay(500);
  
  
  vTaskDelete(NULL);
}



