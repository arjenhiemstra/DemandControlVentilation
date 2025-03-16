#include "task_i2c.h"

TaskHandle_t task_i2c;

void start_task_i2c(void) {

    xTaskCreate(task_i2c_code, "taski2c", 30000, NULL, 6, &task_i2c);

}

void task_i2c_code(void * pvParameters)
{  
    int display_time_multiplier = 0;
    int rtc_time_multiplier = 0;
    int sync_time_multiplier = 0;

    for(;;) {
        read_sensors();
        current_time();
        display_time_multiplier++;
        rtc_time_multiplier++;
        sync_time_multiplier++;
      
        if (display_time_multiplier == 6) {         //Every 30 seconds (6*5)
            Serial.print("\nStart task display....");
            display_time_and_date();
            display_sensors();
            display_valve_positions();
            Serial.print("\nSystem uptime: ");
            Serial.print(esp_timer_get_time()/1000000/60);
            Serial.print(" min\n");
            display_time_multiplier = 0;
        }

        if (rtc_time_multiplier == 4) {             //Every 20 seconds (4*5)
            Serial.print("\nUpdate time....");
            Serial.print("\nLocal time is: ");
            String temp_time = current_time();
            Serial.print(temp_time);
            rtc_time_multiplier = 0;
        }

        if (sync_time_multiplier == 720) {         //Every hour (3600/5)
            Serial.print("\nSync RTC with NTP server...");
            sync_rtc_ntp();
            sync_time_multiplier = 0;
        }

        vTaskDelay(5000);
    }
  
}



