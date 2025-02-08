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

String state = "0";

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

    String new_state;

    //functions to set fan speed or to set valve positions

    //if time is day -> day
    //if time is night -> night

    state == new_state;
}

void day_transitions(void){

    //if time is night -> night
    //if time is day, co2 >1000 pppm -> high CO2 day, high fan speed


    //otherwise state is unchanged
    

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