#include "system.h"

void task_list(void) {
    
    /*char ptrTaskList[250];

    vTaskList(ptrTaskList);
    
    Serial.println(F("**********************************"));
    Serial.println(F("Task  State   Prio    Stack    Num")); 
    Serial.println(F("**********************************"));
    Serial.print(ptrTaskList);
    Serial.println(F("**********************************"));*/
    
    /*
    char buffer1[2048] = {0};
    vTaskList(buffer1);
    Serial.println("\nTasklist: ");
    Serial.println(buffer1);
    Serial.println("\n");
    vTaskDelay(10000);*/

    //Highwatermark
    UBaseType_t influxdb_hwm;
    UBaseType_t i2c_hwm;
    UBaseType_t mqtt_hwm;
    UBaseType_t np_hwm;
    UBaseType_t statemach_hwm;
    UBaseType_t sys_hwm;
    UBaseType_t valvectrl_hwm;
    UBaseType_t web_hwm;
    UBaseType_t wifi_hwm;

    size_t free_heap_size;
    size_t minimum_ever_free_heap_size;
    size_t available_heap_space_bytes
    
    influxdb_hwm = uxTaskGetStackHighWaterMark(task_influxdb);
    i2c_hwm = uxTaskGetStackHighWaterMark(task_i2c);
    mqtt_hwm = uxTaskGetStackHighWaterMark(task_mqtt);
    np_hwm = uxTaskGetStackHighWaterMark(task_np);
    statemach_hwm = uxTaskGetStackHighWaterMark(task_statemach);
    sys_hwm = uxTaskGetStackHighWaterMark(task_sys);
    valvectrl_hwm = uxTaskGetStackHighWaterMark(task_valvectrl);
    web_hwm = uxTaskGetStackHighWaterMark(h_Task_web);
    wifi_hwm = uxTaskGetStackHighWaterMark(task_wifi);

    Serial.print("\nTask\t\tHigh water mark");
    Serial.print("\ntask_influxdb\t\t"); Serial.print(influxdb_hwm);
    Serial.print("\ntask_i2c\t\t"); Serial.print(i2c_hwm);
    Serial.print("\ntask_mqtt\t\t"); Serial.print(mqtt_hwm);
    Serial.print("\ntask_np\t\t"); Serial.print(np_hwm);
    Serial.print("\ntask_statemach\t\t"); Serial.print(statemach_hwm);
    Serial.print("\ntask_sys\t\t"); Serial.print(sys_hwm);
    Serial.print("\ntask_valvectrl\t\t"); Serial.print(valvectrl_hwm);
    Serial.print("\ntask_web\t\t"); Serial.print(web_hwm);
    Serial.print("\ntask_wifi\t\t"); Serial.print(wifi_hwm);
    Serial.print("\n");

    available_heap_space_bytes = xAvailableHeapSpaceInBytes();
    Serial.print("\nAvailble heap space (bytes): ");
    Serial.print(available_heap_space_bytes);

    free_heap_size = xPortGetFreeHeapSize();
    Serial.print("\nFree heap size: ");
    Serial.print(free_heap_size);

    minimum_ever_free_heap_size = xPortGetMinimumEverFreeHeapSize();
    Serial.print("\nMinimum ever free heap size: ");
    Serial.print(minimum_ever_free_heap_size);

    //HeapStats_t xHeapStats;
    //vPortGetHeapStats(&xHeapStats);

    //printf("Available heap space: %u\n", xHeapStats.xAvailableHeapSpaceInBytes);
    //printf("Number of allocations: %u\n", xHeapStats.xNumberOfSuccessfulAllocations);
    //printf("Number of frees: %u\n", xHeapStats.xNumberOfSuccessfulFrees);

}