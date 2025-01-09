#include "task_valvecontrol.h"

TaskHandle_t task_valvectrl;

void start_task_valvecontrol(void) {

    xTaskCreatePinnedToCore(task_valvecontrol_code, "task_valvectrl", 10000, NULL, 1, &task_valvectrl, 1);

}

void task_valvecontrol_code(void * pvParameters)
{
  for (;;) { 
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    Serial.print("\n\nTask1 running on core: ");
    Serial.print(xPortGetCoreID());
  }
  
}



