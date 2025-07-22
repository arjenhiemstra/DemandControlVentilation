#include "general.h"

void print_message(String message) {
    
    char txBuffer[200];

    if (debug_mode == true) {
        //Serial.print("\n" + message);
        strcpy(txBuffer, message.c_str());            
        if(webserial_queue != 0) {
            if (xQueueSend(webserial_queue, txBuffer, 50)) {
                //Serial.print("Message sent to webserial queue: ");
                //Serial.println(txBuffer);
            } else {
                Serial.println("Failed to send message to webserial queue.");
            }
        }
    }
}

String formatted_datetime(void) {
    
    String temp_datetime = "";
    
    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_datetime = yearStr + "/" + monthStr + "/" + dayStr + " - " + hourStr + ":" + minuteStr + ":" + secondStr;
            xSemaphoreGive(date_time_mutex);
        }
    }
    return temp_datetime;
}

