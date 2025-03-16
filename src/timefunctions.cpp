#include "timefunctions.h"

bool cooking_times(void) {

    int temp_hour;
    int temp_minute;

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            temp_minute = minuteStr.toInt();
            xSemaphoreGive(date_time_mutex);
        }
    }

    if (temp_hour==17 && temp_minute > 20)
        return true;
    if (temp_hour==17 && temp_minute >= 58)
        return false;
    else
        return false;
}

bool valve_cycle_times_day(void) {

    int temp_hour;
    int temp_minute;

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            temp_minute = minuteStr.toInt();
            xSemaphoreGive(date_time_mutex);
        }
    }
    
    if (temp_hour==10 && temp_minute < 30)
        return true;
    else if (temp_hour==10 && temp_minute >= 30)
        return false;
    else if (temp_hour==12 && temp_minute < 30)
        return true;
    else if (temp_hour==12 && temp_minute >= 30)
        return false;
    else if (temp_hour==14 && temp_minute < 30)
        return true;
    else if (temp_hour==14 && temp_minute >= 30)
        return false;
    else if (temp_hour==16 && temp_minute < 30)
        return true;
    else if (temp_hour==16 && temp_minute >= 30)
        return false;
    else if (temp_hour==18 && temp_minute > 30)
        return true;
    else if (temp_hour==18 && temp_minute >= 58)
        return false;
    else if (temp_hour==20 && temp_minute < 30)
        return true;
    else if (temp_hour==20 && temp_minute >= 30)
        return false;
    else
        return false;
}

bool valve_cycle_times_night(void) {

    int temp_hour;
    int temp_minute;

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            temp_minute = minuteStr.toInt();
            xSemaphoreGive(date_time_mutex);
        }
    }

    if (temp_hour==23 && temp_minute < 30)
        return true;
    else if (temp_hour==23 && temp_minute >= 30)
        return false;
    else if (temp_hour==1 && temp_minute < 30)
        return true;
    else if (temp_hour==1 && temp_minute >= 30)
        return false;
    else if (temp_hour==3 && temp_minute < 30)
        return true;
    else if (temp_hour==3 && temp_minute >= 30)
        return false;
    else if (temp_hour==5 && temp_minute < 30)
        return true;
    else if (temp_hour==5 && temp_minute >= 30)
        return false;
    else
        return false;
}