#include "task_statemachine.h"

void start_task_statemachine(void) {

    xTaskCreate(task_statemachine_code, "task_statemach", 10000, NULL, 9, &task_statemach);

}

void task_statemachine_code(void * pvParameters) {
  
    init_statemachine();
    
    for (;;) {
        vTaskDelay(30000);
        if (ap_active == 0) {
            run_statemachine();
        }
    }
}
