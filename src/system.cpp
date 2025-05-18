#include "system.h"

void task_list(void) {
    
    /*char ptrTaskList[250];

    vTaskList(ptrTaskList);
    
    Serial.println(F("**********************************"));
    Serial.println(F("Task  State   Prio    Stack    Num")); 
    Serial.println(F("**********************************"));
    Serial.print(ptrTaskList);
    Serial.println(F("**********************************"));*/
    
    
    char buffer1[2048] = {0};
    vTaskList(buffer1);
    Serial.println("\nTasklist: ");
    Serial.println(buffer1);
    Serial.println("\n");
    vTaskDelay(10000);

}