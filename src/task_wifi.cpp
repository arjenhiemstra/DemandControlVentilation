#include "task_wifi.h"

void start_task_wifi(void) {

    xTaskCreate(task_wifi_code, "taskWifi", 10000, NULL, 1, &task_wifi);

}

void task_wifi_code(void * pvParameters) {
    
    for(;;) {
        
        //Serial.print("\nAccess point mode active: " + ap_active);
        
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

        Serial.print("\nIP Address: ");
        Serial.print(WiFi.localIP());
        Serial.print(", Subnetmask: ");
        Serial.print(WiFi.subnetMask());
        Serial.print(", Gateway IP: ");
        Serial.print(WiFi.gatewayIP());
        Serial.print(", Primary DNS: ");
        Serial.print(WiFi.dnsIP(0));
        Serial.print(", Secondary DNS: ");
        Serial.print(WiFi.dnsIP(1));

        uint8_t baseMac[6];
        esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
        
        if (ret == ESP_OK) {
            Serial.print(", MAC: ");
            Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
        } 
        else {
            Serial.println("\nFailed to read MAC address");
        }
                
        vTaskDelay(30000);
    }
  
}


