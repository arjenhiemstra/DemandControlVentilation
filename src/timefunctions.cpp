#include "timefunctions.h"

bool cooking_times(void) {

    int temp_hour = 0;
    int temp_minute = 0;
    int start_hour_state_cooking = 0;
    int start_min_state_cooking = 0;
    int stop_hour_state_cooking = 0;
    int stop_min_state_cooking = 0;

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            temp_minute = minuteStr.toInt();
            xSemaphoreGive(date_time_mutex);
        }
    }

    //Read RH levels for transition to highrhday state from global jsonDocument
    if (settings_state_cooking_mutex != NULL) {
        if(xSemaphoreTake(settings_state_cooking_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            start_hour_state_cooking = settings_state_cooking["start_hour_state_cooking"];
            start_min_state_cooking = settings_state_cooking["start_min_state_cooking"];
            stop_hour_state_cooking = settings_state_cooking["stop_hour_state_cooking"];
            stop_min_state_cooking = settings_state_cooking["stop_min_state_cooking"];
            xSemaphoreGive(settings_state_cooking_mutex);
        }
    }
    if (temp_hour==start_hour_state_cooking && temp_minute > start_min_state_cooking)
        return true;
    if (temp_hour==stop_hour_state_cooking && temp_minute >= stop_min_state_cooking)
        return false;
    else
        return false;
}

bool valve_cycle_times_day(void) {

    int temp_hour = 0;
    int temp_minute = 0;

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

    int temp_hour = 0;
    int temp_minute = 0;

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