#include "general.h"

void print_message(String message) {
    
    char txBuffer[200];

    if (debug_mode == true) {
        Serial.print("\n" + message);
        strcpy(txBuffer, message.c_str());            
        if(webserial_queue != 0) {
            xQueueSend(webserial_queue, txBuffer, 10);
        }
    }
}