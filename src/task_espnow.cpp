#include "task_espnow.h"

//BLECharacteristic *pCharacteristic;

void start_task_bluetooth(void) {

    xTaskCreate(task_espnow_code, "task_espnow", 10000, NULL, 8, &task_espnow);

}

void task_espnow_code(void * pvParameters) {
	
}
