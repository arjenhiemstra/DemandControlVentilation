#include "statemachine.h"

String new_state = "0";
float temp_sensor_data[2][8][3];

void init_statemachine(void) {
    state = "init";
}

void run_statemachine(void) {

    //Copy array to local array with active mutex an then run slow display function without mutex
    if (sensor_variable_mutex != NULL) {
        if(xSemaphoreTake(sensor_variable_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 8; j++) {
                    for (int k = 0; k < 3; k++) {
                        temp_sensor_data[i][j][k] = sensor_data[i][j][k];
                    }
                }
            }
            xSemaphoreGive(sensor_variable_mutex);
        }
    }
    
    if (state == "init") {
        init_transitions();
    }
    else if (state == "day") {
        day_transitions();
    }
    else if (state == "night") {
        night_transitions();
    }
    else if (state == "high_co2_day"){
        high_co2_day_transitions();
    }
    else if (state == "high_co2_night"){
        high_co2_night_transitions();
    }
    else if (state == "high_rh_day") {
        high_rh_day_transitions();
    }
    else if (state == "high_rh_night") {
        high_rh_night_transitions();
    }
    else if (state == "cooking") {
        cooking_transitions();
    }
    else if (state == "valve_cycle_day") {
        valve_cycle_day_transitions();
    }
    else if (state == "valve_cycle_night") {
        valve_cycle_night_transitions();
    }
    else if (state == "manual_high_speed") {
        manual_high_speed_transitions();
    }
    else {
         //This state should normally never be entered. Back to init of statemachine to keep it running
         init_transitions();
    }
}

void init_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "low";

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "init";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);

    // Conditions to transit to other state
     if (now.hour() >= 8 && now.hour() < 21 && now.dayOfTheWeek() != 0 && now.dayOfTheWeek() != 6)  {
        Serial.println("It is after 7, before 21 and a weekday. Transit to day.");
        new_state = "day";
    }
    else if (now.hour() >= 9 && now.hour() < 21 && (now.dayOfTheWeek() == 0 || now.dayOfTheWeek() == 6)) {
        Serial.println("It is after 8 and before 21 and weekend. Transit to day.");
        new_state = "day";
    }
    else {
        Serial.println("It's night. Transit to night.");
        new_state = "night";
    }
    state = new_state;
}

void day_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "medium";

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "day";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);
    // valves in default position

    // Condition to transit to other state
    if (now.hour() >= 21) {
        Serial.print("It's night. Transit to night.");        
        new_state = "night";
    }
    //Assuming that CO2 sensor is on slot 2 of bus 1. CO2 has priority over others
    else if (temp_sensor_data[1][2][2] > 1000) {
        Serial.print("It's day and high CO2. Transit to high_co2_day state");
        new_state = "high_co2_day";
    }
    //Assuming TH is on slot 0 of bus 0
    /*else if (temp_sensor_data[0][0][1] > 85) {
        Serial.print("It's day and high RH. Transit to high_rh_day state.");
        new_state = "high_rh_day";
    }
    /*else if (cooking_times() == true) {
        Serial.print("It's day and cooking time. Transit to cooking state.");
        new_state = "cooking";
    }
    /*else if (valve_cycle_times_day() == true) {
        Serial.print("It's day and valve_cycle_time_day. Transit to vavle_cycle_day state");
        new_state = "valve_cycle_day";
    }*/
    //Manual high speed mode is ignored for now
    else {
        Serial.print("Conditions have not changed, it's still day");
        new_state = "day";
    }
    state = new_state;
}

void night_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "low";

    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "night";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);
    // valves in default position

    // Conditions to transit to other state
    if (now.hour() >= 8 && now.hour() < 21 && now.dayOfTheWeek() > 0 && now.dayOfTheWeek() < 6)  {
        Serial.println("It is after 8, before 21 and a weekday. Transit to day.");
        new_state = "day";
    }
    else if (now.hour() >= 9 && now.hour() < 21 && (now.dayOfTheWeek() == 0 || now.dayOfTheWeek() == 6)) {
        Serial.println("It is after 9, before 21 and weekend. Transit to day");
        new_state = "day";
    }
    else if (temp_sensor_data[1][2][2] > 1000) {
        Serial.println("It is and CO2 level is high. Transit to high_co2_night");
        new_state = "high_co2_night";
    }
    //Assuming RH sensor is on slot 0 of bus 0
    /*else if (temp_sensor_data[0][0][1] > 85) {
        Serial.print("It's night and high RH. Transit to high high_rh_night.");
        new_state = "high_rh_day";
    }
    else if (valve_cycle_times_night() == true) {
        Serial.print("It's night and valve_cycle time. Transit to valve_cycle_night.");
        new_state = "valve_cycle_night";
    }*/
    //Manual high speed mode is ignored for now
    else {
        Serial.print("Conditions have not changed, it's still night.");
        new_state = "night";
    }
    state = new_state;
}

void high_co2_day_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "high";

    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "high_co2_day";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);
    // valves in default position

    // Conditions for transition
    if (temp_sensor_data[1][2][2] < 800) {
        Serial.println("It is day and CO2 level is low enough. Transit to day.");
        new_state = "day";
    }
    else if (now.hour() >= 21) {
        Serial.print("It's night but CO2 levels are still high. Transit to high_co2_night");        
        new_state = "high_co2_night";
    }
    else {
        Serial.println("Conditions have not changed, CO2 is still high, so remain in high_co2_day state");
        new_state = "high_co2_day";
    }
    state = new_state;
}

void high_co2_night_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "low";

    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "high_co2_night";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);
    // valves in default position

    // Conditions for transition
    if (now.hour() >= 8 && now.hour() < 21 && now.dayOfTheWeek() > 0 && now.dayOfTheWeek() < 6)  {
        Serial.println("It is after 7, before 21 and a weekday. Transit to high_co2_day.");
        new_state = "high_co2_day";
    }
    else if (now.hour() >= 9 && now.hour() < 21 && (now.dayOfTheWeek() == 0 || now.dayOfTheWeek() == 6)) {
        Serial.println("It is after 8, before 21 and weekend. Transit to high_co2_day.");
        new_state = "high_co2_day";
    }
    else if (temp_sensor_data[1][2][2] < 800) {
        Serial.println("It is night and CO2 level is low enough. Transit to night.");
        new_state = "night";
    }
    else {
        Serial.println("Conditions have not changed, CO2 is still high, so remain in high_co2_night state");
        new_state = "high_co2_night";
    }
    state = new_state;
}

void high_rh_day_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "high";

    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "high_rh_day";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);
    // valves in default position

    // Conditions for transition
    if (temp_sensor_data[0][0][1] < 70) {
        Serial.print("It's night and high RH. Transit to day");
        new_state = "day";
    }
    else if (now.hour() >= 21) {
        Serial.print("It's night but rh levels are still high. Transit to high_rh_night");        
        new_state = "high_rh_night";
    }
    else {
        Serial.println("Conditions have not changed, RH is still high, so remain in high_rh_day state");
        new_state = "high_rh_day";
    }
    state = new_state;
}

void high_rh_night_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "low";

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "high_rh_night";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);
    // valves in default position

    // Conditions for transition
    if (temp_sensor_data[0][0][1] < 70) {
        Serial.print("It's night and RH is low enough. Transit to night.");
        new_state = "night";
    }
    else if (now.hour() >= 8 && now.hour() < 21 && now.dayOfTheWeek() > 0 && now.dayOfTheWeek() < 6)  {
        Serial.println("It is after 7, before 21 and a weekday but RH is still high. Transit to high_rh_day.");
        new_state = "high_rh_day";
    }
    else if (now.hour() >= 9 && now.hour() < 21 && (now.dayOfTheWeek() == 0 || now.dayOfTheWeek() == 6)) {
        Serial.println("It is after 8, before 21 and weekend but RH is still high. Transit to high_rh_day ");
        new_state = "high_rh_day";
    }
    else {
        Serial.println("Conditions have not changed, RH is still high, so remain in high_rh_night state");
        new_state = "high_rh_night";
    }
    state = new_state;
}

void cooking_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "high";

    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "cooking";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);
    // valves in default position

    // Conditions for transition
    if (cooking_times() == false) {
        Serial.print("It's day and not cooking time. Transit to day");
        new_state = "day";
    }
    else {
        Serial.println("Conditions have not changed, cooking time is not over so remain in cooking state");
        new_state = "cooking";
    }
    state = new_state;
}

void valve_cycle_day_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "medium";

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "valve_cycle_day";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);
    // valves in default position

    // Conditions for transition
    if (valve_cycle_times_day() == false) {
        Serial.print("It's not valve cycle time. Transit to day");
        new_state = "day";
    }
    else if (temp_sensor_data[0][0][1] > 85) {
        Serial.print("It's day and high RH. Transit to high_rh_day state.");
        new_state = "high_rh_day";
    }
    else if (temp_sensor_data[1][2][2] > 1000) {
        Serial.println("It is valve_cycle_day and CO2 level is high. Transit to high_co2_day");
        new_state = "high_co2_day";
    }
    else {
        Serial.println("Conditions have not changed, valve_cycle_day is still active, so remain in valve_cycle_day state");
        new_state = "valve_cycle_day";
    }
    state = new_state;
}

void valve_cycle_night_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "low";

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "valve_cycle_night";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);
    // valves in default position

    // Conditions for transition
    if (valve_cycle_times_night() == false) {
        Serial.print("It's not valve_cycle time. Transit to night");
        new_state = "night";
    }
    else if (temp_sensor_data[0][0][1] > 85) {
        Serial.print("It's valve_cycle_day and high RH. Transit to high_rh_day state.");
        new_state = "high_rh_night";
    }
    else if (temp_sensor_data[1][2][2] > 1000) {
        Serial.println("It is valve_cycle_night and CO2 level is high. Transit to high_co2_night");
        new_state = "high_co2_night";
    }
    else {
        Serial.println("Conditions have not changed, valve_cycle_day is still active, so remain in valve_cycle_night state");
        new_state = "valve_cycle_night";
    }
    state = new_state;
}

//This state is for later
void manual_high_speed_transitions(void) {

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();
    String fanspeed = "high";

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "manual_high_speed";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    publish_state();
    set_fanspeed(fanspeed);
    publish_fanspeed(fanspeed);
    // valves in default position
}