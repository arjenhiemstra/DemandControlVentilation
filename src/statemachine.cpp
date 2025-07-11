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

struct RH_Sensors {
    String valve;
    float rh_reading;
};

//Although 16 sensors can be used
CO2_Sensors co2_sensors[16];
RH_Sensors rh_sensors[16];
int co2_sensor_counter = 0;
int rh_sensors_counter = 0;

void init_statemachine(void) {
    
    String temp_fanspeed = "";

    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = "init";
            xSemaphoreGive(statemachine_state_mutex);
        }
    }
    
    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = "Low";
            temp_fanspeed = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }
    set_fanspeed(temp_fanspeed);
}

void run_statemachine(void) {

    Serial.print("\nRead sensor data from queue for statemachine.");
    if (xQueuePeek(sensor_queue, &statemachine_sensor_data, 0 ) == pdTRUE) {
        
    }
    
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
            fanspeed = "Low";
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

    String fanspeed_tmp = "";
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

    //read fanspeed from config of this state
    if (settings_state_day_mutex != NULL) {
        if(xSemaphoreTake(settings_state_day_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            String temp_fanspeed = settings_state_day[String("state_day_fanspeed")];
            fanspeed_tmp = temp_fanspeed;
            xSemaphoreGive(settings_state_day_mutex);
        }
    }

    //Write fanspeed to global variable
    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = fanspeed_tmp;
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

    set_fanspeed(fanspeed_tmp);

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
        Serial.print("\nIt's day and high RH. Transit to highrhday state.");
        new_state = "highrhday";
    }
    else if (cooking_times() == true) {
        Serial.print("\nIt's day and cooking time. Transit to cooking state.");
        new_state = "cooking";
    }
    else if (valve_cycle_times_day() == true) {
        Serial.print("\nIt's day and valve_cycle_time_day. Transit to valvecycleday state");
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
    String fanspeed_tmp = "";
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

    //read fanspeed from config of this state
    if (settings_state_night_mutex != NULL) {
        if(xSemaphoreTake(settings_state_night_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            String temp_fanspeed = settings_state_night[String("state_night_fanspeed")];
            fanspeed_tmp = temp_fanspeed;
            xSemaphoreGive(settings_state_night_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = fanspeed_tmp;
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

    set_fanspeed(fanspeed_tmp);

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
        Serial.print("\nIt's night and high RH. Transit to high high_rh_night.");
        new_state = "highrhday";
    }
    else if (valve_cycle_times_night() == true) {
        Serial.print("\nIt's night and valve_cycle time. Transit to valve_cycle_night.");
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
    String fanspeed_tmp = "";
    String state_valve_pos_path = "";
    String state_valve_pos_str = "";
    int temp_hour = 0;
    int co2_sensors_high = 0;
    bool valve_move_locked = 0;
    bool state_valve_pos_file_present = 0;

    //Local JSON object to hold the state settings
    JsonDocument state_valve_pos_doc;

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

    //read fanspeed from config of this state
    if (settings_state_highco2day_mutex != NULL) {
        if(xSemaphoreTake(settings_state_highco2day_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            String temp_fanspeed = settings_state_highco2day[String("state_highco2day_fanspeed")];
            fanspeed_tmp = temp_fanspeed;
            xSemaphoreGive(settings_state_highco2day_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = fanspeed_tmp;
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

    set_fanspeed(fanspeed_tmp);
    select_sensors();

    //Temp valve settings for individual valves starting with default settings for this state. Should read these from file and not hardcode them
    state_valve_pos_path = ("/json/settings_state_" + statemachine_state + ".json");
    state_valve_pos_file_present = check_file_exists(state_valve_pos_path.c_str());
    
    if (settings_state_highco2day_mutex != NULL) {
        if(xSemaphoreTake(settings_state_highco2day_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            if (state_valve_pos_file_present == 1) {
                
                File file = LittleFS.open(state_valve_pos_path, "r");
                while(file.available()) {
                    state_valve_pos_str = file.readString();
                }
                file.close();    
            }
            xSemaphoreGive(settings_state_highco2day_mutex);
        }
    }

    deserializeJson(state_valve_pos_doc, state_valve_pos_str);

    settings_state_temp["valve0_position_state_temp"] = state_valve_pos_doc["valve0_position_highco2day"].as<int>();
    settings_state_temp["valve1_position_state_temp"] = state_valve_pos_doc["valve1_position_highco2day"].as<int>();
    settings_state_temp["valve2_position_state_temp"] = state_valve_pos_doc["valve2_position_highco2day"].as<int>();
    settings_state_temp["valve3_position_state_temp"] = state_valve_pos_doc["valve3_position_highco2day"].as<int>();
    settings_state_temp["valve4_position_state_temp"] = state_valve_pos_doc["valve4_position_highco2day"].as<int>();
    settings_state_temp["valve5_position_state_temp"] = state_valve_pos_doc["valve5_position_highco2day"].as<int>();
    settings_state_temp["valve6_position_state_temp"] = state_valve_pos_doc["valve6_position_highco2day"].as<int>();
    settings_state_temp["valve7_position_state_temp"] = state_valve_pos_doc["valve7_position_highco2day"].as<int>();
    settings_state_temp["valve8_position_state_temp"] = state_valve_pos_doc["valve8_position_highco2day"].as<int>();
    settings_state_temp["valve9_position_state_temp"] = state_valve_pos_doc["valve9_position_highco2day"].as<int>();
    settings_state_temp["valve10_position_state_temp"] = state_valve_pos_doc["valve10_position_highco2day"].as<int>();
    settings_state_temp["valve11_position_state_temp"] = state_valve_pos_doc["valve11_position_highco2day"].as<int>();

    // Iterate through CO2 sensors to see which one has high CO2 reading to see if default settings apply when high reading is at fan inlet
    // or only one valve needs to open (when high reading is in a room)
    for (int i = 0; i < co2_sensor_counter; i++) {
        if (co2_sensors[i].co2_reading > 1000 && co2_sensors[i].valve != "Fan inlet") {
            //Set new valve settings for the room with high CO2 reading
            settings_state_temp[co2_sensors[i].valve + "_position_state_temp"] = 20;
        }
    }

    if (valve_move_locked == 0) {    
        valve_position_statemachine("state_temp");
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions for transition. If fan inlet is lower than 800 ppm then it is day, otherwise it is high CO2 day
    // Iterate through CO2 sensors to see if any of them has CO2 reading below 800 ppm and if so close that valve to default psoition
    for (int i = 0; i < co2_sensor_counter; i++) {
        if (co2_sensors[i].co2_reading > 800 && co2_sensors[i].valve == "Fan inlet") {
            co2_sensors_high++;              //No need to move valve but remains in highco2day
        }
        else if (co2_sensors[i].co2_reading > 800 && co2_sensors[i].valve != "Fan inlet") {
            co2_sensors_high++;              //Sensor is not below 800ppm
        }
        else if (co2_sensors[i].co2_reading < 800 && co2_sensors[i].valve != "Fan inlet") {
            // Only close valve for the room with high CO2 reading by customizing the settings_state_temp JSON object. All other valves will remain in the same position
            settings_state_temp[co2_sensors[i].valve + "_position_state_temp"] = 4;
            if (valve_move_locked == 0) {
                valve_position_statemachine("state_temp");
            }
        }
    }
    
    Serial.print("\nNumber of sensors measure high CO2: " + String(co2_sensors_high) );
    
    //Other transition conditions 
    if (co2_sensors_high > 0) {
        new_state = "highco2day";
        Serial.print("\nConditions have not changed, CO2 in one of the sensors is still high, so remain in high_co2_day state");
    }
    else if (temp_hour >= 21 && co2_sensors_high > 0) {
        new_state = "highco2night";
        Serial.print("\nIt's night but CO2 levels are still high. Transit to high_co2_night");        
    }
    else if (temp_hour >= 21 && co2_sensors_high == 0) {
        new_state = "night";
        Serial.print("\nIt's night with no sensors having hi CO2. Transit to night");        
    }
    else {
        new_state = "day";
        Serial.print("\nNo sensor has high CO2 reading. Return to day state");
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
    String fanspeed_tmp = "";
    String temp_day_of_week = "";
    String state_valve_pos_path = "";
    String state_valve_pos_str = "";
    int temp_hour = 0;
    int co2_sensors_high = 0;
    bool valve_move_locked = 0;
    bool state_valve_pos_file_present = 0;

    //Local JSON object to hold the state settings
    JsonDocument state_valve_pos_doc;
    
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

    //read fanspeed from config of this state
    if (settings_state_highco2night_mutex != NULL) {
        if(xSemaphoreTake(settings_state_highco2night_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            String temp_fanspeed = settings_state_highco2night[String("state_highco2night_fanspeed")];
            fanspeed_tmp = temp_fanspeed;
            xSemaphoreGive(settings_state_highco2night_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = fanspeed_tmp;
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

    set_fanspeed(fanspeed_tmp);           //Set in conditions below
    select_sensors();

    //Temp valve settings for individual valves starting with default settings for this state. Should read these from file and not hardcode them
    state_valve_pos_path = ("/json/settings_state_" + statemachine_state + ".json");
    state_valve_pos_file_present = check_file_exists(state_valve_pos_path.c_str());
    
    if (settings_state_highco2night_mutex != NULL) {
        if(xSemaphoreTake(settings_state_highco2night_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            if (state_valve_pos_file_present == 1) {
                
                File file = LittleFS.open(state_valve_pos_path, "r");
                while(file.available()) {
                    state_valve_pos_str = file.readString();
                }
                file.close();    
            }
            xSemaphoreGive(settings_state_highco2night_mutex);
        }
    }

    deserializeJson(state_valve_pos_doc, state_valve_pos_str);

    settings_state_temp["valve0_position_state_temp"] = state_valve_pos_doc["valve0_position_highco2night"].as<int>();
    settings_state_temp["valve1_position_state_temp"] = state_valve_pos_doc["valve1_position_highco2night"].as<int>();
    settings_state_temp["valve2_position_state_temp"] = state_valve_pos_doc["valve2_position_highco2night"].as<int>();
    settings_state_temp["valve3_position_state_temp"] = state_valve_pos_doc["valve3_position_highco2night"].as<int>();
    settings_state_temp["valve4_position_state_temp"] = state_valve_pos_doc["valve4_position_highco2night"].as<int>();
    settings_state_temp["valve5_position_state_temp"] = state_valve_pos_doc["valve5_position_highco2night"].as<int>();
    settings_state_temp["valve6_position_state_temp"] = state_valve_pos_doc["valve6_position_highco2night"].as<int>();
    settings_state_temp["valve7_position_state_temp"] = state_valve_pos_doc["valve7_position_highco2night"].as<int>();
    settings_state_temp["valve8_position_state_temp"] = state_valve_pos_doc["valve8_position_highco2night"].as<int>();
    settings_state_temp["valve9_position_state_temp"] = state_valve_pos_doc["valve9_position_highco2night"].as<int>();
    settings_state_temp["valve10_position_state_temp"] = state_valve_pos_doc["valve10_position_highco2night"].as<int>();
    settings_state_temp["valve11_position_state_temp"] = state_valve_pos_doc["valve11_position_highco2night"].as<int>();

    // High CO2 has been detected to come into this state. Iterate through CO2 sensors to see which sensor detects high CO2.
    // Valves with CO2 sensors are default set to 20 for this state so every valve with a co2 value lower than 1000 ppm will be closed to 4
    for (int i = 0; i < co2_sensor_counter; i++) {
        if (co2_sensors[i].co2_reading < 1000 && co2_sensors[i].valve != "Fan inlet") {
            settings_state_temp[co2_sensors[i].valve + "_position_state_temp"] = 4;         //Set new valve settings for the room without high CO2 reading
        }
    }

    if (valve_move_locked == 0) {    
        valve_position_statemachine("state_temp");
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }
    
    if (valve_move_locked == 0) {
        valve_position_statemachine(statemachine_state);
    }
    else {
        Serial.print("\nValves are locked for moving, will try again later");
    }

    // Conditions for transition. Iterate through CO2 sensors to see if any of them has CO2 reading below 800 ppm and if so open that valve to default psoition
    for (int i = 0; i < co2_sensor_counter; i++) {
        if (co2_sensors[i].co2_reading > 800 && co2_sensors[i].valve == "Fan inlet") {
            co2_sensors_high++;              //No need to move valve but remains in highco2night
        }
        else if (co2_sensors[i].co2_reading > 800 && co2_sensors[i].valve != "Fan inlet") {
            co2_sensors_high++;             //Sensor at a valve is not below 800ppm    
        }
        else if (co2_sensors[i].co2_reading < 800 && co2_sensors[i].valve != "Fan inlet") {
            // Only close valve for the room with high CO2 reading by customizing the settings_state_temp JSON object. All other valves will remain in the same position
            settings_state_temp[co2_sensors[i].valve + "_position_state_temp"] = 20;
            if (valve_move_locked == 0) {
                valve_position_statemachine("state_temp");
            }
        }
    }

    // Other transition conditions
    if (co2_sensors_high > 0) {
        new_state = "highco2night";
        //fanspeed_tmp = "Medium";            //Set fanspeed to medium when in high CO2 night state
        //set_fanspeed(fanspeed_tmp);
        Serial.print("\nConditions have not changed, one of the sensors still detects high CO2, so remain in high_co2_night state");
    }
    else if (co2_sensors_high > 0 && temp_hour >= 8 && temp_hour < 21 && temp_day_of_week != "Saturday" && temp_day_of_week != "Sunday")  {
        Serial.print("\nIt is after 8, before 21 and a weekday. Transit to high_co2_day.");
        new_state = "highco2day";
    }
    else if (co2_sensors_high > 0 && temp_hour >= 9 && temp_hour < 21 && (temp_day_of_week == "Saturday" || temp_day_of_week == "Sunday")) {
        Serial.print("\nIt is after 9, before 21 and weekend. Transit to high_co2_day.");
        new_state = "highco2day";
    }
    /*else if (statemachine_sensor_data[1][2][2] < 800) {
        Serial.print("\nIt is night and CO2 level is low enough. Transit to night.");
        new_state = "night";
    }*/
    else {
        Serial.print("\nNo sensor has high CO2 reading. Return to night state");
        new_state = "night";
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
    String fanspeed_tmp = "high";
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

    //read fanspeed from config of this state
    if (settings_state_highrhday_mutex != NULL) {
        if(xSemaphoreTake(settings_state_highrhday_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            String temp_fanspeed = settings_state_highrhday[String("state_highrhday_fanspeed")];
            fanspeed_tmp = temp_fanspeed;
            xSemaphoreGive(settings_state_highrhday_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = fanspeed_tmp;
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

    set_fanspeed(fanspeed_tmp);
    
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
    String fanspeed_tmp = "";
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

    //read fanspeed from config of this state
    if (settings_state_highrhnight_mutex != NULL) {
        if(xSemaphoreTake(settings_state_highrhnight_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            String temp_fanspeed = settings_state_highrhnight[String("state_highrhnight_fanspeed")];
            fanspeed_tmp = temp_fanspeed;
            xSemaphoreGive(settings_state_highrhnight_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = fanspeed_tmp;
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

    set_fanspeed(fanspeed_tmp);

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
    String fanspeed_tmp = "";
    bool valve_move_locked = 0;

    // Actions for this sate
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    //read fanspeed from config of this state
    if (settings_state_cooking_mutex != NULL) {
        if(xSemaphoreTake(settings_state_cooking_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            String temp_fanspeed = settings_state_cooking[String("state_cooking_fanspeed")];
            fanspeed_tmp = temp_fanspeed;
            xSemaphoreGive(settings_state_cooking_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = fanspeed_tmp;
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
   
    set_fanspeed(fanspeed_tmp);
    
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
    String fanspeed_tmp = "";
    bool valve_move_locked = 0;

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    //read fanspeed from config of this state
    if (settings_state_cyclingday_mutex != NULL) {
        if(xSemaphoreTake(settings_state_cyclingday_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            String temp_fanspeed = settings_state_cyclingday[String("state_cyclingday_fanspeed")];
            fanspeed_tmp = temp_fanspeed;
            xSemaphoreGive(settings_state_cyclingday_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = fanspeed_tmp;
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

    set_fanspeed(fanspeed_tmp);
    
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
    String fanspeed_tmp = "";
    bool valve_move_locked = 0;

    // Actions for this state
    if (statemachine_state_mutex != NULL) {
        if(xSemaphoreTake(statemachine_state_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            state = statemachine_state;
            xSemaphoreGive(statemachine_state_mutex);
        }
    }

    //read fanspeed from config of this state
    if (settings_state_cyclingnight_mutex != NULL) {
        if(xSemaphoreTake(settings_state_cyclingnight_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            String temp_fanspeed = settings_state_cyclingnight[String("state_cyclingnight_fanspeed")];
            fanspeed_tmp = temp_fanspeed;
            xSemaphoreGive(settings_state_cyclingnight_mutex);
        }
    }

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed = fanspeed_tmp;
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

    set_fanspeed(fanspeed_tmp);
    
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

    const char* path1 = "/json/sensor_config1.json";
    const char* path2 = "/json/sensor_config2.json";
    
    String sensor_config1_string = "";
    String sensor_config2_string = "";
    String co2_sensor_wire = "";
    String co2_sensor_wire1 = "";
    String rh_sensor_wire = "";
    String rh_sensor_wire1 = "";
    String valve = "";

    bool sensor_config1_file_present = 0;
    bool sensor_config2_file_present = 0;

    int co2_sensor_counter = 0;
    int rh_sensor_counter = 0;

    int j=0;        //counter for struct
    int k=0;        //counter for struct

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
    xQueuePeek(sensor_queue, &sensor_data, 0 );

    //Count how many CO2 and RH sensors are enabled for CO2 control
    for (int i = 0; i < 8; i++) {
        if (sensor_config_file_mutex != NULL) {
            if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                String co2_sensor_wire = wire_sensor_data["wire_sensor"+String(i)]["co2"];
                String co2_sensor_wire1 = wire1_sensor_data["wire1_sensor"+String(i)]["co2"];
                String rh_sensor_wire = wire_sensor_data["wire_sensor"+String(i)]["rh"];
                String rh_sensor_wire1 = wire1_sensor_data["wire1_sensor"+String(i)]["rh"];
                if (co2_sensor_wire == "On") {
                    co2_sensor_counter++;
                }
                if (co2_sensor_wire1 == "On") {
                    co2_sensor_counter++;
                }
                if (rh_sensor_wire == "On") {
                    rh_sensor_counter++;
                }
                if (rh_sensor_wire1 == "On") {
                    rh_sensor_counter++;
                }
                xSemaphoreGive(sensor_config_file_mutex);
            }
        }
    }

    Serial.print("\nco2_sensor_counter: " + String(co2_sensor_counter));
    Serial.print("\t\t\trh_sensor_counter: " + String(rh_sensor_counter));

    for (int i = 0; i < 8; i++) {
        if (sensor_config_file_mutex != NULL) {
            if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                String co2_sensor_wire_temp = wire_sensor_data["wire_sensor"+String(i)]["co2"];
                String co2_sensor_wire1_temp = wire1_sensor_data["wire1_sensor"+String(i)]["co2"];
                String rh_sensor_wire_temp = wire_sensor_data["wire_sensor"+String(i)]["rh"];
                String rh_sensor_wire1_temp = wire1_sensor_data["wire1_sensor"+String(i)]["rh"];
                co2_sensor_wire = co2_sensor_wire_temp;
                co2_sensor_wire1 = co2_sensor_wire1_temp;
                rh_sensor_wire = rh_sensor_wire_temp;
                rh_sensor_wire1 = rh_sensor_wire1_temp;
                xSemaphoreGive(sensor_config_file_mutex);

            }
        }
        if (co2_sensor_wire == "On") {
            if (sensor_config_file_mutex != NULL) {
                if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                    String valve_temp = wire_sensor_data["wire_sensor"+String(i)]["valve"];
                    valve = valve_temp;
                    xSemaphoreGive(sensor_config_file_mutex);
                }
            }
                    
            co2_sensors[j].valve = valve;
            co2_sensors[j].co2_reading = sensor_data[0][i][2];
            
            Serial.print("\nvalve: ");
            Serial.print(co2_sensors[j].valve);
            Serial.print("\t\t\tCO2 reading: ");
            Serial.print(co2_sensors[j].co2_reading);
            j++;
        }
        
        if (co2_sensor_wire1 == "On") {
            if (sensor_config_file_mutex != NULL) {
                if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                    String valve_temp = wire1_sensor_data["wire1_sensor"+String(i)]["valve"];
                    valve = valve_temp;
                    xSemaphoreGive(sensor_config_file_mutex);
                }
            }
            co2_sensors[j].valve = valve;
            co2_sensors[j].co2_reading = sensor_data[1][i][2];
            
            Serial.print("\nvalve: ");
            Serial.print(co2_sensors[j].valve);
            Serial.print("\t\t\tCO2 reading: ");
            Serial.print(co2_sensors[j].co2_reading);
            j++;
        }
        String rh_sensor_wire = wire_sensor_data["wire_sensor"+String(i)]["rh"];
        if (rh_sensor_wire == "On") {
            if (sensor_config_file_mutex != NULL) {
                if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                    String valve_temp = wire_sensor_data["wire_sensor"+String(i)]["valve"];
                    valve = valve_temp;
                    xSemaphoreGive(sensor_config_file_mutex);
                }
            }
            rh_sensors[k].valve = valve;
            rh_sensors[k].rh_reading = sensor_data[0][i][1];
            
            Serial.print("\nvalve: ");
            Serial.print(rh_sensors[k].valve);
            Serial.print("\t\t\tRH reading: ");
            Serial.print(rh_sensors[k].rh_reading);
            j++;
        }
        String rh_sensor_wire1 = wire1_sensor_data["wire1_sensor"+String(i)]["rh"];
        if (rh_sensor_wire1 == "On") {
            if (sensor_config_file_mutex != NULL) {
                if(xSemaphoreTake(sensor_config_file_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                    String valve_temp = wire1_sensor_data["wire1_sensor"+String(i)]["valve"];
                    valve = valve_temp;
                    xSemaphoreGive(sensor_config_file_mutex);
                }
            }
            rh_sensors[k].valve = valve;
            rh_sensors[k].rh_reading = sensor_data[1][i][1];
            
            Serial.print("\nvalve: ");
            Serial.print(rh_sensors[k].valve);
            Serial.print("\t\t\tRH reading: ");
            Serial.print(rh_sensors[k].rh_reading);
            j++;
        }
    }
    co2_sensor_counter = j;
    rh_sensor_counter = k;
}