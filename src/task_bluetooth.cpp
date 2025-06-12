#include "task_bluetooth.h"

//BluetoothSerial SerialBT;

void start_task_bluetooth(void) {

    xTaskCreate(task_bluetooth_code, "task_bluetooth", 10000, NULL, 8, &task_bluetooth);

}

void task_bluetooth_code(void * pvParameters)
{
	
	String fanspeed_str;
	int fanspeed_int = 0;

	//SerialBT.begin("VentilationController"); //Bluetooth device name
	//SerialBT.setPin("1234"); //PIN for pairing
	/*Serial.println("The device started, now you can pair it with Bluetooth!");

	for (;;) { 
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		
		if (fanspeed_mutex != NULL) {
			if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
				fanspeed_str = fanspeed;
				xSemaphoreGive(fanspeed_mutex);
			}
		}

		if (fanspeed_str == "low") {
			fanspeed_int = 10;
		}
		else if(fanspeed_str == "medium") {
			fanspeed_int = 50;
		}
		else if(fanspeed_str == "high") {
			fanspeed_int = 80;
		}
		
		if (Serial.available()) {
			SerialBT.write(fanspeed_int);
		}
	}*/
	vTaskDelete(NULL);
  
}



