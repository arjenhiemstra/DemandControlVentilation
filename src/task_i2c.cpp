#include "task_i2c.h"

TaskHandle_t task_i2c;

void start_task_i2c(void) {

    xTaskCreate(task_i2c_code, "taski2c", 30000, NULL, 6, &task_i2c);

}

void task_i2c_code(void * pvParameters)
{
    int display_time_multiplier = 0;
    int rtc_time_multiplier = 0;
    
    for(;;) {
        read_sensors();
        display_time_multiplier++;
        rtc_time_multiplier++;

        vTaskDelay(5000);
        
        if (display_time_multiplier == 6) {     //6 * 5 seconds
            display_time_and_date();
            display_sensors();
            display_valve_positions();
            display_time_multiplier = 0;
        }

        if (rtc_time_multiplier == 4) {         //4 * 5 seconds
            Serial.print("\n\nLocal time is: ");
            current_time();
        }
        
    }
  
}



