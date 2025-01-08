#include "task_valvecontrol.h"

TaskHandle_t h_task_valvecontrol;

void startTaskvalvecontrol(void) {

    xTaskCreatePinnedToCore(Taskvalvecontrolcode, "Valve control task", 10000, NULL, 1, &h_task_valvecontrol, 1);
}

void Taskvalvecontrolcode(void * pvParameters) {

  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  Serial.print("\n\nTask valvecontrol running on core: ");
  Serial.print(xPortGetCoreID());
  
  vTaskDelete(NULL);
}



