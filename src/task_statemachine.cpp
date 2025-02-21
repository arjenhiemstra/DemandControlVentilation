#include "task_statemachine.h"

TaskHandle_t task_statemach;

void start_task_statemachine(void) {

    xTaskCreatePinnedToCore(task_statemachine_code, "task_statemach", 10000, NULL, 9, &task_statemach, 1);

}

void task_statemachine_code(void * pvParameters)
{
  init_statemachine();
  for (;;) { 
    vTaskDelay(30000);
    Serial.print("\n\nLocal time is: ");
    current_time();
    run_statemachine();
  }
}
