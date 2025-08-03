#include "task_espnow.h"

void start_task_espnow(void) {

    xTaskCreate(task_espnow_code, "task_espnow", 10000, NULL, 8, &task_espnow);

}

void task_espnow_code(void * pvParameters) {

    uint8_t receiverMAC[] = {0x88, 0x13, 0xbf, 0x07, 0xb1, 0xec};  // Replace with receiver's MAC address
    String fanspeed_tmp;
    
    char fanspeed_char[20];

    esp_now_init();
    esp_now_register_send_cb(onSent);

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, receiverMAC, 6);
    peerInfo.channel = 8;
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);

    for (;;) {
        
        if (fanspeed_mutex != NULL) {
            if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                fanspeed_tmp = fanspeed;
                xSemaphoreGive(fanspeed_mutex);
            }
        }

        if (fanspeed_tmp == "Low") {
            fanspeed_tmp = 10;
        }
        else if (fanspeed_tmp == "Medium") {
            fanspeed_tmp = 40;
        }
        else if (fanspeed_tmp == "High") {
            fanspeed_tmp = 80;
        }
        else {
            fanspeed_tmp = 110;
        }

        fanspeed_tmp.toCharArray(fanspeed_char,20);
        
        esp_now_send(receiverMAC, (uint8_t *)fanspeed_char, sizeof(fanspeed_char));
        Serial.printf("\nSent Fanspeed: %s", fanspeed_char);

        vTaskDelay(20000);
    }
	
}

void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {

    //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "\tDelivery success" : "\tDelivery failed");

}