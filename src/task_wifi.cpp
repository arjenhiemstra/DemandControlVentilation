#include "task_wifi.h"

void start_task_wifi(void) {

    xTaskCreate(task_wifi_code, "taskWifi", 10000, NULL, 1, &task_wifi);

}

void task_wifi_code(void * pvParameters) {
    
    String message = "";

    for(;;) {
        
        //Serial.print("\nAccess point mode active: " + ap_active);
        
        if (WiFi.status() != WL_CONNECTED && ap_active == 0) {
            message = "No Wifi connection. Trying to connect to Wifi.";
            print_message(message);
            config_wifi();     
        }
        else if (ap_active == 1) {
            message = "Wifi Access Point is active. Configure wifi on http://192.168.4.1";
            print_message(message);
        }
        else {
            message = "Wifi connection ok. Nothing to do.";
            print_message(message);
        }

        message = "Wifi status: " + String(WiFi.status()) + ", Wifi SSID: " + WiFi.SSID() + ", Wifi BSSID: " + WiFi.BSSIDstr() + ", Wifi RSSI: " + String(WiFi.RSSI());
        print_message(message);

        message = "IP Address: " + String(WiFi.localIP().toString()) + ", Subnetmask: " + String(WiFi.subnetMask().toString()) + ", Gateway IP: " + String(WiFi.gatewayIP().toString());
        print_message(message);
        
        message = "Primary DNS: " + String(WiFi.dnsIP(0).toString()) + ", Secondary DNS: " + String(WiFi.dnsIP(1).toString());
        print_message(message);

        uint8_t baseMac[6];
        esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
        
        if (ret == ESP_OK) {
            message = "MAC: " + String(baseMac[0], HEX) + ":" + String(baseMac[1], HEX) + ":" + String(baseMac[2], HEX) + ":" + String(baseMac[3], HEX) + ":" + String(baseMac[4], HEX) + ":" + String(baseMac[5], HEX);
            print_message(message);
            //Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
        } 
        else {
            message = "Failed to read MAC address";
            print_message(message);
        }
                
        vTaskDelay(30000);
    }
  
}


