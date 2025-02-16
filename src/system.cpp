#include "system.h"

void task_list(void) {
    
    char ptrTaskList[250];

    vTaskList(ptrTaskList);
    
    Serial.println(F("**********************************"));
    Serial.println(F("Task  State   Prio    Stack    Num")); 
    Serial.println(F("**********************************"));
    Serial.print(ptrTaskList);
    Serial.println(F("**********************************"));

}