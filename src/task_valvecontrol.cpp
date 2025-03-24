#include "task_valvecontrol.h"

TaskHandle_t task_valvectrl;

void start_task_valvecontrol(void) {

    xTaskCreate(task_valvecontrol_code, "task_valvectrl", 10000, NULL, 8, &task_valvectrl);

}

void task_valvecontrol_code(void * pvParameters)
{
  for (;;) { 
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    move_valve();
  }
  
}



