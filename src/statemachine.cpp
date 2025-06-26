/*
- Multiple sensors can be used to determine the CO2 value. This is set in the sensor config files
- Temperature is not used
- RH can only be used in bathroom(s) since in general RH cannot be influenced by ventilation, only when there is a big change such as showering
- CO2 can be measured for serveral rooms
    - If one room has high CO2 then it should be sufficinet to open a valve
    - If the fan inlet has high CO2 in daytime then fanspeed should go to high in day time
    - If the fan inlet has high CO2 in the night then fanspeed should remain low and all valves to bedrooms open
*/

#include "statemachine.h"

String new_state = "0";
float statemachine_sensor_data[2][8][3];
float statemachine_avg_sensor_data[2][8][3];

struct CO2_Sensors {
        String valve;
        float co2_reading;
};

//struct CO2_Sensors co2_sensors;

CO2_Sensors co2_sensors[8];
int co2_sensor_counter = 0;

void init_statemachine(void) {
    state = "init";
}

void run_statemachine(void) {

    Serial.print("\nRead sensor data from queue for statemachine.");
    if (xQueuePeek(sensor_queue, &statemachine_sensor_data, 0 ) == pdTRUE) {
        /*Serial.print("\n\nBus\tSensor\tTemperature (°C)\tHumidity (%)\tCO2 (ppm)");
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
        }*/
    }
    //Serial.print("\n");
    
    
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
    else if (state == "stopped") {
        stopped_transitions();
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

void stopped_transitions(void) {

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "stopped";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    //No further logic required because when start statemachine button is pushed the statemachine will go back to init state
    Serial.print("\nStatemachin in stopped state. Push start statemachine button on the Valve Control web page.");

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

    // Conditions to transit to other state, only evalaution based on time and day of week
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
    
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = new_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    } 
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

    float temp = co2_sensors[0].co2_reading;
    Serial.print("\nco2_sensors[0].co2_reading: ");
    Serial.print(temp);

    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions to transit to other state

    //Iterate through CO2 sensors to see if any of them has high CO2 reading
    select_sensors();
    int co2_sensor_high = 0;
    
    for (int i = 0; i < co2_sensor_counter; i++) {
        if (co2_sensors[i].co2_reading > 1000) {
            Serial.print("\nSensor" + String(i) + " which is located at " + String(co2_sensors[i].valve) + " has high CO2 reading. Transit to highco2day state");
            //Serial.print("\nIt's day and high CO2. Transit to highco2day state");
            co2_sensor_high++;
        }
    }

    if (co2_sensor_high > 0) {
        new_state = "highco2day";
    } 
    else if (temp_hour >= 21) {
        Serial.print("\nIt's night. Transit to night.");        
        new_state = "night";
    }
    else if (statemachine_sensor_data[0][0][1] > 85) {                      //Assuming RH is on slot 0 of bus 0          
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
    
    //Assuming that CO2 sensor is on slot 2 of bus 1. CO2 has priority over others
    //else if (statemachine_avg_sensor_data[1][2][2] > 1000) {
        //Serial.print("\nIt's day and high CO2. Transit to highco2day state");
        //new_state = "highco2day";
    //}

    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = new_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    } 
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
    
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = new_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
}

void high_co2_day_transitions(void) {

    String statemachine_state = "highco2day";
    String temp_fanspeed = "";
    int temp_hour = 0;
    bool valve_move_locked = 0;
    bool is_fan_inlet = 0;

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

        //Temp valve settings for individual valves starting with default settings for this state
        //Should read these from file and not hardcode them
        if (settings_state_temp_mutex != NULL) {
            if(xSemaphoreTake(settings_state_temp_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                settings_state_temp["enable_state_temp"] = "On";
                settings_state_temp["name_state_temp"] = "temp";
                settings_state_temp["valve0_position_temp_state"] = 4;
                settings_state_temp["valve1_position_temp_state"] = 4;
                settings_state_temp["valve2_position_temp_state"] = 4;
                settings_state_temp["valve3_position_temp_state"] = 0;
                settings_state_temp["valve4_position_temp_state"] = 0;
                settings_state_temp["valve5_position_temp_state"] = 4;
                settings_state_temp["valve6_position_temp_state"] = 24;
                settings_state_temp["valve7_position_temp_state"] = 0;
                settings_state_temp["valve8_position_temp_state"] = 4;
                settings_state_temp["valve9_position_temp_state"] = 4;
                settings_state_temp["valve10_position_temp_state"] = 4;
                settings_state_temp["valve11_position_temp_state"] = 4;
                xSemaphoreGive(settings_state_temp_mutex);
            }
        }
        
        // Iterate through CO2 sensors to see which one has high CO2 reading to see if all valves need to move (when high reading is at fan inlet) 
        // or only one valve needs to open (when high reading is in a room)
        for (int i = 0; i < co2_sensor_counter; i++) {
            if (co2_sensors[i].co2_reading >1000 && co2_sensors[i].valve != "Fan inlet") {
                //Set new valve settings for the room with high CO2 reading
                settings_state_temp["valve" + String(i) + "_position_temp_state"] = 20;
            }
            else {
                //State is high CO2 day and sensor is at fan inlet, so set to default valve settings
                is_fan_inlet = 1;
            }
        }
        
        if (is_fan_inlet == 1) {
            valve_position_statemachine(statemachine_state);
        }
        else {
            // If not fan inlet sensor than use temp state valve settings
            valve_position_statemachine("temp_state");
        }
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions for transition. 
    // If fan inlet is lower than 800 ppm then it is day, otherwise it is high CO2 day
    // Iterate through CO2 sensors to see if any of them has CO2 reading below 800 ppm and if so close that valve to default psoition
    int co2_sensors_low = 0;
    
    for (int i = 0; i < co2_sensor_counter; i++) {
        
        if (co2_sensors[i].co2_reading > 800 && co2_sensors[i].valve == "Fan inlet") {                 //No need to move valve
            co2_sensors_low++;
        }
        
        if (co2_sensors[i].co2_reading < 800 && co2_sensors[i].valve != "Fan inlet") {
            // Only close valve for the room with high CO2 reading by customizing the settings_state_temp JSON object. All other valves 
            // will remain in the same position
            settings_state_temp["valve" + String(i) + "_position_temp_state"] = 4;
            valve_position_statemachine("temp_state");
        }
        else {
            //Sensor is not below 800ppm
            co2_sensors_low++;
        }    
    }
    
    //Other transition conditions 
    if (co2_sensors_low > 0) {
        new_state = "highco2day";
        Serial.print("\nConditions have not changed, CO2 in one of the sensors is still high, so remain in high_co2_day state");
    }
    else if (temp_hour >= 21 && co2_sensors_low > 0) {
        new_state = "highco2night";
        Serial.print("\nIt's night but CO2 levels are still high. Transit to high_co2_night");        
    }
    else {
        new_state = "day";
        Serial.print("\nReturn to day state");
    }
    
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = new_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }    
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
    
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = new_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    } 
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
    
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = new_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    } 
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
    
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = new_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    } 
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
    
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = new_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    } 
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
    
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = new_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    } 
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
    
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = new_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
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

void select_sensors(void) {
    //Read config files
    //Make new array with sensors which are active for statemachine
    //Need to read config file at every iteration of statemachine, otherwise changes will not happen until reboot
    //Then statemachine needs to re-iterate through small array

    const char* path1 = "/json/sensor_config1.json";
    const char* path2 = "/json/sensor_config2.json";
    
    String sensor_config1_string = "";
    String sensor_config2_string = "";
    //String co2_sensor_wire;
    //String co2_sensor_wire1;
    //String rh_sensor_wire;
    //String rh_sensor_wire1;

    bool sensor_config1_file_present = 0;
    bool sensor_config2_file_present = 0;

    int rh_sensor_counter = 0;

    float sensor_data[2][8][3];
    
    if (sensor_config_file_mutex != NULL) {
        if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            sensor_config1_file_present = check_file_exists(path1);
            if (sensor_config1_file_present == 1) {
                File file = LittleFS.open(path1, "r");
                while(file.available()) {
                    sensor_config1_string = file.readString();
                }
                file.close();
                deserializeJson(wire_sensor_data, sensor_config1_string);
            }
            xSemaphoreGive(sensor_config_file_mutex);
        }
    }

    if (sensor_config_file_mutex != NULL) {
        if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            sensor_config2_file_present = check_file_exists(path2);
            if (sensor_config2_file_present == 1) {
                File file = LittleFS.open(path2, "r");
                while(file.available()) {
                    sensor_config2_string = file.readString();
                }
                file.close();
                deserializeJson(wire1_sensor_data, sensor_config2_string);
            }
            xSemaphoreGive(sensor_config_file_mutex);
        }
    }

    //Copy sensor readings from global
    if (xQueuePeek(sensor_queue, &sensor_data, 0 ) == pdTRUE) {
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

    //Count how many CO2 sensors are enabled for CO2 control so can determine the array size

    co2_sensor_counter = 0;

    for (int i = 0; i < 8; i++) {
        String co2_sensor_wire = wire_sensor_data["wire_sensor"+String(i)]["co2"];
        if (co2_sensor_wire == "On") {
            co2_sensor_counter++;
        }
        String co2_sensor_wire1 = wire1_sensor_data["wire1_sensor"+String(i)]["co2"];
        if (co2_sensor_wire1 == "On") {
            co2_sensor_counter++;
        }
        String rh_sensor_wire = wire_sensor_data["wire_sensor"+String(i)]["rh"];
        if (rh_sensor_wire == "On") {
            rh_sensor_counter++;
        }
        String rh_sensor_wire1 = wire1_sensor_data["wire1_sensor"+String(i)]["rh"];
        if (rh_sensor_wire1 == "On") {
            rh_sensor_counter++;
        }
    }

    Serial.print("\nco2_sensor_counter: ");
    Serial.print(co2_sensor_counter);

    Serial.print("\nrh_sensor_counter: ");
    Serial.print(rh_sensor_counter);
    
    //struct CO2_Sensors {
        //String valve;
        //float co2_reading;
    //};

    //CO2_Sensors co2_sensors[co2_sensor_counter];

    //initialise struct empty
    //for (int i=0; i<co2_sensor_counter; i++) {
        //co2_sensors[i].valve = "";
        //co2_sensors[i].co2_reading = 0;
    //}

    int j=0;        //counter for struct

    for (int i = 0; i < 8; i++) {
        String co2_sensor_wire = wire_sensor_data["wire_sensor"+String(i)]["co2"];
        if (co2_sensor_wire == "On") {
            String valve_temp = wire_sensor_data["wire_sensor"+String(i)]["valve"];
            co2_sensors[j].valve = valve_temp;
            co2_sensors[j].co2_reading = sensor_data[0][i][2];
            
            Serial.print("\nvalve: ");
            Serial.print(co2_sensors[j].valve);
            Serial.print("\t\tCO2 reading: ");
            Serial.print(co2_sensors[j].co2_reading);
            j++;
        }
        String co2_sensor_wire1 = wire1_sensor_data["wire1_sensor"+String(i)]["co2"];
        if (co2_sensor_wire1 == "On") {
            String valve_temp = wire1_sensor_data["wire1_sensor"+String(i)]["valve"];
            co2_sensors[j].valve = valve_temp;
            co2_sensors[j].co2_reading = sensor_data[1][i][2];
            
            Serial.print("\nvalve: ");
            Serial.print(co2_sensors[j].valve);
            Serial.print("\t\tCO2 reading: ");
            Serial.print(co2_sensors[j].co2_reading);
            j++;
        }
        
    }
    co2_sensor_counter = j;

    








}