#include "task_bluetooth.h"

void start_task_bluetooth(void) {

    xTaskCreate(task_bluetooth_code, "task_bluetooth", 10000, NULL, 8, &task_bluetooth);

}

void task_bluetooth_code(void * pvParameters)
{
	for (;;) { 
		

	}
	vTaskDelete(NULL);
  
}



