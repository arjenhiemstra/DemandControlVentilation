#include "statemachine.h"

String new_state = "0";
float statemachine_sensor_data[2][8][3];
float statemachine_avg_sensor_data[2][8][3];

void init_statemachine(void) {
    state = "init";
}

void run_statemachine(void) {

    Serial.print("\nRead sensor data from queue for statemachine.");
    if (xQueuePeek(sensor_queue, &statemachine_sensor_data, 0 ) == pdTRUE) {
        Serial.print("\n\nBus\tSensor\tTemperature (°C)\tHumidity (%)\tCO2 (ppm)");
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                Serial.print("\n");
                Serial.print(i);
                Serial.print("\t\t");
                Serial.print(j);
                Serial.print("\t");
                for (int k = 0; k < 3; k++) {
                    Serial.print(statemachine_sensor_data[i][j][k]);
                    Serial.print("\t\t");
                }
            }
        }
    }
    Serial.print("\n");
    
    
    Serial.print("\nRead average sensor data from queue for statemachine.");
    if (xQueuePeek(sensor_avg_queue, &statemachine_avg_sensor_data, 0 ) == pdTRUE) {
        Serial.print("\n\nBus\tSensor\tTemperature (°C)\tHumidity (%)\tCO2 (ppm)");
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                Serial.print("\n");
                Serial.print(i);
                Serial.print("\t\t");
                Serial.print(j);
                Serial.print("\t");
                for (int k = 0; k < 3; k++) {
                    Serial.print(statemachine_avg_sensor_data[i][j][k]);
                    Serial.print("\t\t");
                }
            }
        }
    }
    Serial.print("\n");
    
    
    if (state == "init") {
        init_transitions();
    }
    else if (state == "day") {
        day_transitions();
    }
    else if (state == "night") {
        night_transitions();
    }
    else if (state == "highco2day"){
        high_co2_day_transitions();
    }
    else if (state == "highco2night"){
        high_co2_night_transitions();
    }
    else if (state == "highrhday") {
        high_rh_day_transitions();
    }
    else if (state == "highrhnight") {
        high_rh_night_transitions();
    }
    else if (state == "cooking") {
        cooking_transitions();
    }
    else if (state == "cyclingday") {
        valve_cycle_day_transitions();
    }
    else if (state == "cyclingnight") {
        valve_cycle_night_transitions();
    }
    else if (state == "fanhighspeed") {
        manual_high_speed_transitions();
    }
    else {
         //This state should normally never be entered. Back to init of statemachine to keep it running
         init_transitions();
    }
}

void init_transitions(void) {

    String temp_day_of_week = "";
    String temp_fanspeed = "";
    int temp_hour = 0;

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "init";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            temp_day_of_week = dayOfWeek;
            xSemaphoreGive(date_time_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "low";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    set_fanspeed(temp_fanspeed);

    // Conditions to transit to other state
    if (temp_hour >= 8 && temp_hour < 21 && temp_day_of_week != "Saturday" && temp_day_of_week != "Sunday")  {
        Serial.print("\nIt is after 8, before 21 and a weekday. Transit to day.");
        new_state = "day";
    }
    else if (temp_hour >= 9 && temp_hour < 21 && (temp_day_of_week == "Saturday" || temp_day_of_week == "Sunday")) {
        Serial.print("\nIt is after 9 and before 21 and weekend. Transit to day.");
        new_state = "day";
    }
    else {
        Serial.print("\nIt's night. Transit to night.");
        new_state = "night";
    }
    state = new_state;
}

void day_transitions(void) {

    String temp_fanspeed = "";
    String statemachine_state = "day";
    int temp_hour = 0;
    bool valve_move_locked = 0;

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            xSemaphoreGive(date_time_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "medium";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            valve_move_locked = lock_valve_move;
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }

    set_fanspeed(temp_fanspeed);

    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Condition to transit to other state
    if (temp_hour >= 21) {
        Serial.print("\nIt's night. Transit to night.");        
        new_state = "night";
    }
    //Assuming that CO2 sensor is on slot 2 of bus 1. CO2 has priority over others
    else if (statemachine_avg_sensor_data[1][2][2] > 1000) {
        Serial.print("\nIt's day and high CO2. Transit to highco2day state");
        new_state = "highco2day";
    }
    //Assuming RH is on slot 0 of bus 0
    else if (statemachine_sensor_data[0][0][1] > 85) {
        Serial.print("It's day and high RH. Transit to highrhday state.");
        new_state = "highrhday";
    }
    else if (cooking_times() == true) {
        Serial.print("It's day and cooking time. Transit to cooking state.");
        new_state = "cooking";
    }
    else if (valve_cycle_times_day() == true) {
        Serial.print("It's day and valve_cycle_time_day. Transit to valvecycleday state");
        new_state = "cyclingday";
    }
    //Manual high speed mode is ignored for now
    else {
        Serial.print("\nConditions have not changed, it's still day");
        new_state = "day";
    }
    state = new_state;
}

void night_transitions(void) {

    String statemachine_state = "night";
    String temp_fanspeed = "";
    String temp_day_of_week = "";
    int temp_hour = 0;
    bool valve_move_locked = 0;
    
    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            temp_day_of_week = dayOfWeek.toInt();
            xSemaphoreGive(date_time_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "low";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            valve_move_locked = lock_valve_move;
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }

    set_fanspeed(temp_fanspeed);

    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }
    
    // Conditions to transit to other state
    if (temp_hour >= 8 && temp_hour < 21 && temp_day_of_week != "Saturday" && temp_day_of_week != "Sunday")  {
        Serial.print("\nIt is after 8, before 21 and a weekday. Transit to day.");
        new_state = "day";
    }
    else if (temp_hour >= 9 && temp_hour < 21 && (temp_day_of_week == "Saturday" || temp_day_of_week == "Sunday")) {
        Serial.print("\nIt is after 9, before 21 and weekend. Transit to day");
        new_state = "day";
    }
    else if (statemachine_sensor_data[1][2][2] > 1000) {
        Serial.print("\nIt is and CO2 level is high. Transit to high_co2_night");
        new_state = "highco2night";
    }
    //Assuming RH sensor is on slot 0 of bus 0
    else if (statemachine_sensor_data[0][0][1] > 85) {
        Serial.print("It's night and high RH. Transit to high high_rh_night.");
        new_state = "highrhday";
    }
    else if (valve_cycle_times_night() == true) {
        Serial.print("It's night and valve_cycle time. Transit to valve_cycle_night.");
        new_state = "cyclingnight";
    }
    //Manual high speed mode is ignored for now
    else {
        Serial.print("\nConditions have not changed, it's still night.");
        new_state = "night";
    }
    state = new_state;
}

void high_co2_day_transitions(void) {

    String statemachine_state = "highco2day";
    String temp_fanspeed = "";
    int temp_hour = 0;
    bool valve_move_locked = 0;

    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            xSemaphoreGive(date_time_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "high";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            valve_move_locked = lock_valve_move;
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }

    set_fanspeed(temp_fanspeed);

    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions for transition
    if (statemachine_sensor_data[0][0][2] < 800) {
        Serial.print("\nIt is day and CO2 level is low enough. Transit to day.");
        new_state = "day";
    }
    else if (temp_hour >= 21) {
        Serial.print("\nIt's night but CO2 levels are still high. Transit to high_co2_night");        
        new_state = "highco2night";
    }
    else {
        Serial.print("\nConditions have not changed, CO2 is still high, so remain in high_co2_day state");
        new_state = "highco2day";
    }
    state = new_state;
}

void high_co2_night_transitions(void) {

    String statemachine_state = "highco2night";
    String temp_fanspeed = "";
    String temp_day_of_week = "";
    int temp_hour = 0;
    bool valve_move_locked = 0;
    
    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            temp_day_of_week = dayOfWeek.toInt();
            xSemaphoreGive(date_time_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "low";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            valve_move_locked = lock_valve_move;
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }

    set_fanspeed(temp_fanspeed);
    
    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions for transition
    if (temp_hour >= 8 && temp_hour < 21 && temp_day_of_week != "Saturday" && temp_day_of_week != "Sunday")  {
        Serial.print("\nIt is after 8, before 21 and a weekday. Transit to high_co2_day.");
        new_state = "highco2day";
    }
    else if (temp_hour >= 9 && temp_hour < 21 && (temp_day_of_week == "Saturday" || temp_day_of_week == "Sunday")) {
        Serial.print("\nIt is after 9, before 21 and weekend. Transit to high_co2_day.");
        new_state = "highco2day";
    }
    else if (statemachine_sensor_data[1][2][2] < 800) {
        Serial.print("\nIt is night and CO2 level is low enough. Transit to night.");
        new_state = "night";
    }
    else {
        Serial.print("\nConditions have not changed, CO2 is still high, so remain in high_co2_night state");
        new_state = "highco2night";
    }
    state = new_state;
}

void high_rh_day_transitions(void) {

    String statemachine_state = "highrhday";
    String temp_fanspeed = "high";
    int temp_hour = 0;
    bool valve_move_locked = 0;

    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            xSemaphoreGive(date_time_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "high";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            valve_move_locked = lock_valve_move;
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }

    set_fanspeed(temp_fanspeed);
    
    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions for transition
    if (statemachine_sensor_data[0][0][1] < 70) {
        Serial.print("\nIt's night and high RH. Transit to day");
        new_state = "day";
    }
    else if (temp_hour >= 21) {
        Serial.print("\nIt's night but rh levels are still high. Transit to high_rh_night");        
        new_state = "highrhnight";
    }
    else {
        Serial.print("\nConditions have not changed, RH is still high, so remain in high_rh_day state");
        new_state = "highrhday";
    }
    state = new_state;
}

void high_rh_night_transitions(void) {

    String statemachine_state = "highrhnight";
    String temp_fanspeed = "";
    String temp_day_of_week = "";
    int temp_hour = 0;
    bool valve_move_locked = 0;

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            temp_hour = hourStr.toInt();
            temp_day_of_week = dayOfWeek.toInt();
            xSemaphoreGive(date_time_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "low";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            valve_move_locked = lock_valve_move;
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }

    set_fanspeed(temp_fanspeed);

    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions for transition
    if (statemachine_sensor_data[0][0][1] < 70) {
        Serial.print("\nIt's night and RH is low enough. Transit to night.");
        new_state = "night";
    }
    else if (temp_hour >= 8 && temp_hour < 21 && temp_day_of_week != "Saturday" && temp_day_of_week != "Sunday")  {
        Serial.print("\nIt is after 8, before 21 and a weekday but RH is still high. Transit to high_rh_day.");
        new_state = "highrhday";
    }
    else if (temp_hour >= 9 && temp_hour < 21 && (temp_day_of_week == "Saturday" || temp_day_of_week == "Sunday")) {
        Serial.print("\nIt is after 9, before 21 and weekend but RH is still high. Transit to high_rh_day ");
        new_state = "highrhday";
    }
    else {
        Serial.print("\nConditions have not changed, RH is still high, so remain in high_rh_night state");
        new_state = "highrhnight";
    }
    state = new_state;
}

void cooking_transitions(void) {

    String statemachine_state = "cooking";
    String temp_fanspeed = "";
    bool valve_move_locked = 0;

    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "high";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            valve_move_locked = lock_valve_move;
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }
   
    set_fanspeed(temp_fanspeed);
    
    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions for transition
    if (cooking_times() == false) {
        Serial.print("\nIt's day and not cooking time. Transit to day");
        new_state = "day";
    }
    else {
        Serial.print("\nConditions have not changed, cooking time is not over so remain in cooking state");
        new_state = "cooking";
    }
    state = new_state;
}

void valve_cycle_day_transitions(void) {

    String statemachine_state = "cyclingday";
    String temp_fanspeed = "";
    bool valve_move_locked = 0;

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "medium";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            valve_move_locked = lock_valve_move;
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }

    set_fanspeed(temp_fanspeed);
    
    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions for transition
    if (valve_cycle_times_day() == false) {
        Serial.print("\nIt's not valve cycle time. Transit to day");
        new_state = "day";
    }
    else if (statemachine_sensor_data[0][0][1] > 85) {
        Serial.print("\nIt's day and high RH. Transit to high_rh_day state.");
        new_state = "highrhday";
    }
    else if (statemachine_sensor_data[1][2][2] > 1000) {
        Serial.print("\nIt is valve_cycle_day and CO2 level is high. Transit to high_co2_day");
        new_state = "highco2day";
    }
    else {
        Serial.print("\nConditions have not changed, valve_cycle_day is still active, so remain in valve_cycle_day state");
        new_state = "cyclingday";
    }
    state = new_state;
}

void valve_cycle_night_transitions(void) {

    String statemachine_state = "cyclingnight";
    String temp_fanspeed = "";
    bool valve_move_locked = 0;

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "low";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            valve_move_locked = lock_valve_move;
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }

    set_fanspeed(temp_fanspeed);
    
    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions for transition
    if (valve_cycle_times_night() == false) {
        Serial.print("\nIt's not valve_cycle time. Transit to night");
        new_state = "night";
    }
    else if (statemachine_sensor_data[0][0][1] > 85) {
        Serial.print("\nIt's valve_cycle_day and high RH. Transit to high_rh_day state.");
        new_state = "highrhnight";
    }
    else if (statemachine_sensor_data[1][2][2] > 1000) {
        Serial.print("\nIt is valve_cycle_night and CO2 level is high. Transit to high_co2_night");
        new_state = "highco2night";
    }
    else {
        Serial.print("\nConditions have not changed, valve_cycle_day is still active, so remain in valve_cycle_night state");
        new_state = "cyclingnight";
    }
    state = new_state;
}

//This state is for later
void manual_high_speed_transitions(void) {

    String statemachine_state = "manual_high_speed";
    String fanspeed = "high";
    bool valve_move_locked = 0;

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            valve_move_locked = lock_valve_move;
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }

    set_fanspeed(fanspeed);
    
    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }
}

