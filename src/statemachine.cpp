#include "statemachine.h"

/*
States:

init
day
night
high_co2_day
high_co2_night
high_rh_day
high_rh_night
cooking
valve_cycle_day
valve_cycle_day

*/

//String state = "0";
String new_state = "0";

void init_statemachine(void) {

    state = "init";

}

void run_statemachine(void) {

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

    //now.dayOfTheWeek start with Sunday (0) and ends at Saturday 6

    if (now.hour() > 7 && now.hour() < 22 && now.dayOfTheWeek() != 0 && now.dayOfTheWeek() != 6)  {
        Serial.print("It is after 7 and before 21 and a weekday");
        new_state = "day";
    }
    
    else if (now.hour() > 8 && now.hour() < 22 && now.dayOfTheWeek() == 0 && now.dayOfTheWeek() == 6) {
        Serial.print("It is after 8 and before 21 and weekend");
        new_state = "day";
    }
    
    else {
        Serial.print("It's night");
        new_state = "night";
    }

    state = new_state;
}

void day_transitions(void){

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();

    if (sensor_variable_mutex != NULL) {
        if(xSemaphoreTake(sensor_variable_mutex, ( TickType_t ) 10 ) == pdTRUE) {
    
            if (now.hour() > 21) {
                Serial.print("It's night");
                // low fan speed
                // valves in default position
                new_state = "night";
            }
            //Assuming that CO2 sensor is on slot 2 of bus 1. CO2 has priority over others
            else if (sensor_data[1][2][2] > 1000) {
                Serial.print("It's day and high CO2");
                //fan high speed
                //valves in default position
                new_state = "high_co2_day";
            }
            //Assuming TH is on slot 0 of bus 0
            else if (sensor_data[0][0][1] > 85) {
                Serial.print("It's day and high RH");
                //Set fan speed to high
                //valves in default position
                new_state = "high_rh_day";
            }
            //Manual high speed control
            //else if () {
            //
            //}
            xSemaphoreGive(sensor_variable_mutex);
        }
    }
    state = new_state;
}

void night_transitions(void) {

}

void high_co2_day_transitions(void) {

}

void high_co2_night_transitions(void) {

}

void high_rh_day_transitions(void) {

}

void high_rh_night_transitions(void) {

}

void cooking_transitions(void) {

}

void valve_cycle_day_transistions(void) {

}

void valve_cycle_day_transitions(void) {

}

void manual_high_speed_transitions(void) {

}