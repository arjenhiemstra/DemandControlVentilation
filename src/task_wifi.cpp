#include "task_wifi.h"

void start_task_wifi(void) {

    xTaskCreate(task_wifi_code, "taskWifi", 10000, NULL, 1, &task_wifi);

}

void task_wifi_code(void * pvParameters)
{
    for(;;) {
        
        Serial.print("\nAccess point mode active: ");
        Serial.print(ap_active);
        
        if (WiFi.status() != WL_CONNECTED && ap_active == 0) {
            Serial.print("\nNo Wifi connection. Trying to connect to Wifi.");
            config_wifi();
        }
        else if (ap_active == 1) {
            Serial.print("\nWifi Access Point is active. Configure wifi on http://192.168.4.1");
        }
        else {
            Serial.print("\nWifi connection ok. Nothing to do.");
        }
        
        vTaskDelay(30000);
    }
  
}


