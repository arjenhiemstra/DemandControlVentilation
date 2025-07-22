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
    String temp_year = "";
    String temp_month = "";
    String temp_day = "";
    String temp_hour = "";
    String temp_minute = "";
    String temp_second = "";
    
    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_year = yearStr;
            temp_month = monthStr;
            temp_day = dayStr;
            temp_hour = hourStr;
            temp_minute = minuteStr;
            temp_second = secondStr;
            xSemaphoreGive(date_time_mutex);
        }
    }
    //temp_datetime =  + "/" + monthStr + "/" + dayStr + " - " + hourStr + ":" + minuteStr + ":" + secondStr;
    temp_datetime = temp_year + "/" + temp_month + "/" + temp_day + " - " + temp_hour + ":" + temp_minute + ":" + temp_second;
    return temp_datetime;
}

