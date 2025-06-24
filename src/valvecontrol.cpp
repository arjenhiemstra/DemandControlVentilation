#include "valvecontrol.h"

//Control valves from web interface
void move_valve(void) {

    //Temporary variables used after selection of I/O
    int clockPin = 0;
    int latchPin = 0;
    int dataPin = 0;

    const char* path = "/json/valvepositions.json";
    
    bool status_file_present = 0;
    
    int valve_number = 0;
    int direction = 0;
    int valve_pos = 0;
    int valve_position_change = 0;
    int new_valve_position_change = 0;
    int new_valve_position = 0;
    int store_valve_position = 0;
    int check_valve_position = 0;
    
    String json = "";
    String new_valve_positions = "";

    JsonDocument doc;
    
    File file;

    if (valve_control_data_mutex != NULL) {
        if(xSemaphoreTake(valve_control_data_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            store_valve_position = valve_control_data["checks"][0];
            check_valve_position = valve_control_data["checks"][1];
            xSemaphoreGive(valve_control_data_mutex);
        }
    }

    // Read valve status file
    status_file_present = check_file_exists(path);

    if (status_file_present == 1) {
        if (valve_position_file_mutex != NULL) {
            if(xSemaphoreTake(valve_position_file_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
                json = read_config_file(path);
                xSemaphoreGive(valve_position_file_mutex);
            }
        }

        deserializeJson(doc, json);
  
        String valve0_pos = doc[String("valve0")];
        String valve1_pos = doc[String("valve1")];
        String valve2_pos = doc[String("valve2")];
        String valve3_pos = doc[String("valve3")];
        String valve4_pos = doc[String("valve4")];
        String valve5_pos = doc[String("valve5")];
        String valve6_pos = doc[String("valve6")];
        String valve7_pos = doc[String("valve7")];
        String valve8_pos = doc[String("valve8")];
        String valve9_pos = doc[String("valve9")];
        String valve10_pos = doc[String("valve10")];
        String valve11_pos = doc[String("valve11")];
    }

    // Debug
    Serial.print("\nStore new valve Position: " + String(store_valve_position) + ", Check valve position: " + String(check_valve_position));

    for(int i=0;i<12;i++) {

        if (valve_control_data_mutex != NULL) {
            if(xSemaphoreTake(valve_control_data_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                valve_number = valve_control_data["valve"+String(i)+"_data"][0];
                valve_position_change = valve_control_data["valve"+String(i)+"_data"][1];
                direction = valve_control_data["valve"+String(i)+"_data"][2];
                xSemaphoreGive(valve_control_data_mutex);
            }
        }
        
        valve_pos = doc["valve"+String(i)];

        Serial.print("\nvalve_number: " + String(valve_number) + ", position_change: " + String(valve_position_change) + ", direction: " + direction);

        // Assign the correct IO based on valve number
        if (valve_number < 6) {
            latchPin = latchPin1;
            clockPin = clockPin1;
            dataPin = dataPin1;
        }
        else {
            latchPin = latchPin2;
            clockPin = clockPin2;
            dataPin = dataPin2;
        }
      
        if (check_valve_position == 1) {
            //Direction 0 is close
            //Direction 1 is open valve
            //Position 0 is fully closed
            //Position 24 is fully open
            if(direction == 0 && (valve_pos - valve_position_change) <= 0) {
                new_valve_position_change = valve_pos;
                Serial.print ("\nCondition 1. Request move is: " + String(valve_position_change) + ". Current_position is: " + String(valve_pos) + ". Valve will move: " + String(new_valve_position_change) + ". Direction: " + String(direction));
                valvecontrol(direction, new_valve_position_change, valve_number, dataPin, clockPin, latchPin);
                new_valve_position = valve_pos - new_valve_position_change;
            }
            else if (direction == 0 && (valve_pos - valve_position_change) > 0) {
                new_valve_position_change = valve_position_change;
                Serial.print ("\nCondition 2. Request move is: " + String(valve_position_change) + ". Current_position is: " + String(valve_pos) + ". Valve will move: " + String(new_valve_position_change) + ". Direction: " + String(direction));
                valvecontrol(direction, new_valve_position_change, valve_number, dataPin, clockPin, latchPin);
                new_valve_position = valve_pos - new_valve_position_change;
            }
            else if (direction == 1 && (valve_pos + valve_position_change) > 24) {
                new_valve_position_change = 24 - valve_pos;
                Serial.print ("\nCondition 3. Request move is: " + String(valve_position_change) + ". Current_position is: " + String(valve_pos) + ". Valve will move: " + String(new_valve_position_change) + ". Direction: " + String(direction));
                valvecontrol(direction, new_valve_position_change, valve_number, dataPin, clockPin, latchPin);
                new_valve_position = valve_pos + valve_position_change;
            }
            else if (direction == 1 && (valve_pos + valve_position_change) <= 24) {
                new_valve_position_change = valve_position_change;
                Serial.print ("\nCondition 4. Request move is: " + String(valve_position_change) + ". Current_position is: " + String(valve_pos) + ". Valve will move: " + String(new_valve_position_change) + ". Direction: " + String(direction));
                valvecontrol(direction, new_valve_position_change, valve_number, dataPin, clockPin, latchPin);
                new_valve_position = valve_pos + new_valve_position_change;
            }
        }
        else {
            valvecontrol(direction, valve_position_change, valve_number, dataPin, clockPin, latchPin);
        }

        //Storing new valve positions only makes sense in combination with new calculated positions
        if (store_valve_position == 1 && check_valve_position == 1) {
            doc["valve"+String(i)] = new_valve_position;
        }
    }

    //Convert from JsonDocument to String
    serializeJson(doc, new_valve_positions);

    Serial.print("\n");
    //Serial.print(new_valve_positions);

    //Write status file only if required
    if (store_valve_position == 1) {
        if (valve_position_file_mutex != NULL) {
            if(xSemaphoreTake(valve_position_file_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
                write_config_file(path, new_valve_positions);
                xSemaphoreGive(valve_position_file_mutex);
            }
        }
    }
}

void valvecontrol(int direction, int position_change, int valve_number, int dataPin, int clockPin, int latchPin ) {

    // This function moves one valve based on 3 inputs. If multiple valves need to move, this function is called multiple 
    // times. This function does not check if the valves are controlled outside their operating window so all requests for 
    // valve movement should be checked by another function before calling this function. The reason why not to put the 
    // operating window check in this functions is that the user must be able to calibrated the valves, i.e. line up up 
    // the valves with the registered positions. The requested move is relative to the current position and not the new absolute
    // position of the valve.

    // Local variables
    int output[3][4] = { 0 };       // Output array with switching pattern, initialise at 0;
    int i;                          // Counter for creating output array
    int j;                          // Counter for
    int k;                          // Counter to iterate through output array

    // Variables which are application settings
    int cycles = 24;        //the number if cycles to complete one rotation of the shaft

    //switching pattern for steppermotor in 8 bits.
    int pattern1[4] = { 0b00000101, 0b00001001, 0b00001010, 0b00000110 };
    int pattern2[4] = { 0b01010000, 0b10010000, 0b10100000, 0b01100000 };

    // Disable valve moving when valves are already moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            lock_valve_move = 1;
            Serial.print("\nValves are locked for moving");
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }
    
    //Valve 0 - 5 has the same output as valves 6-11
    if (valve_number >= 6) {
        valve_number = valve_number - 6;
    }

    switch (valve_number) {
        case 0:
            for (i=0; i<4; i++) {
                output[0][i] = pattern1[i];
                output[1][i] = 0;
                output[2][i] = 0;
            }
            break;  
        case 1:
            for (i=0; i<4; i++) {
                output[0][i] = pattern2[i];
                output[1][i] = 0;
                output[2][i] = 0;
            }
            break;
        case 2:
            for (i=0; i<4; i++) {
                output[0][i] = 0;
                output[1][i] = pattern1[i];
                output[2][i] = 0;
            }
            break;
        case 3:
            for (i=0; i<4; i++) {
                output[0][i] = 0;
                output[1][i] = pattern2[i];
                output[2][i] = 0;
            }
            break;
        case 4:
            for (i=0; i<4; i++) {
                output[0][i] = 0;
                output[1][i] = 0;
                output[2][i] = pattern1[i];
            }
            break;
        case 5:
            for (i=0; i<4; i++) {
                output[0][i] = 0;
                output[1][i] = 0;
                output[2][i] = pattern2[i];
            }
            break;
    }

    //Direction is 0 (forwards or close)
    if (direction == 1) {
        //Loop to run the number of cycles to make one turn * the number of turns to make requested_position_change
        for (j=0; j < (cycles * position_change); j++) {
            //Loop to make one cycle of the four coils in the motor
            for (k = 0; k < 4; k++) {
                digitalWrite(latchPin, 0);                                //ground latchPin and hold low for as long as you are transmitting
                shiftOut(dataPin, clockPin, MSBFIRST, output[2][k]);
                shiftOut(dataPin, clockPin, MSBFIRST, output[1][k]);
                shiftOut(dataPin, clockPin, MSBFIRST, output[0][k]);
                digitalWrite(latchPin, HIGH);
                vTaskDelay(10);
            }
        }
        //after running all outputs should be off
        all_outputs_off(dataPin, clockPin, latchPin);
    }

    //Direction is 1 (backwards or open)
    else {
        //Loop to run the number of cycles to make one turn * the number of turns to make requested_position_change
        for (j=0; j < (cycles*position_change); j++) {
            //Loop to make one cycle of the four coils in the motor
            for (k = 3; k > -1; k--) {
                digitalWrite(latchPin, 0);
                shiftOut(dataPin, clockPin, MSBFIRST, output[2][k]);
                shiftOut(dataPin, clockPin, MSBFIRST, output[1][k]);
                shiftOut(dataPin, clockPin, MSBFIRST, output[0][k]);
                digitalWrite(latchPin, HIGH);
                vTaskDelay(10);
            }
        }
        all_outputs_off(dataPin, clockPin, latchPin);
    }

    // Enable valve moving
    if (lock_valve_move_mutex != NULL) {
        if(xSemaphoreTake(lock_valve_move_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            lock_valve_move = 0;
            Serial.print("\nValves are unlocked for moving");
            xSemaphoreGive(lock_valve_move_mutex);
        }
    }
}

void all_outputs_off(int dataPin, int clockPin, int latchPin) {

    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
}

void valve_position_statemachine(String statemachine_state) {

/*
The move_valve function works with requested position move value and is not with absolute positions of the valves.  
1. Select valve position file based on global variable state (with Mutex!)
2. Read file with valve settings for state (e.g. day or high_co2_) of statemachine.
3. Read file with existing positions (with mutex!)
4. Calculate how much the valve should move and calculate direction. 
5. Set valve check and update position file to active
6. Update valve_control_data global variable with data from step 4 (with Mutex!
7. Call the move valve function.

Data structure for each JSON valve_control_data Structure
{
    "valve0_data": [valve_vumber,valve move,valvemove_direction],
    "valve1_data": [valve_vumber,valve move,valvemove_direction],
    ......
    "valve11_data": [valve_vumber,valve move,valvemove_direction]
}
*/
    
    String state_valve_pos_path;            //Must be String and not const char* because it is changed by the statemechine!!!
    String state_valve_pos_str;
    String actual_valve_pos_json;

    JsonDocument state_valve_pos_doc;
    JsonDocument actual_valve_pos_doc;

    //Actual valve positions
    const char* actual_valve_pos_path = "/json/valvepositions.json";
    bool status_file_present;
    bool state_valve_pos_file_present;
    int move;
    int direction;
    int valve_number;
    int i;
    int sum_move = 0;          //temp variable for decision on writing config file (sum>0) or not (sum=0)

    //Requested valve positions based on valve position settings files
    if (statemachine_state == "temp_state") {
        serializeJson(settings_state_temp,state_valve_pos_str);
    }
    else {
        state_valve_pos_path = ("/json/settings_state_" + statemachine_state + ".json");
        if (settings_state_day_mutex != NULL) {
            if(xSemaphoreTake(settings_state_day_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                state_valve_pos_file_present = check_file_exists(state_valve_pos_path.c_str());
                if (state_valve_pos_file_present == 1) {
            
                    File file = LittleFS.open(state_valve_pos_path, "r");
            
                    while(file.available()) {
                        state_valve_pos_str = file.readString();
                    }
                    file.close();
                }        
                xSemaphoreGive(settings_state_day_mutex);
            }
        }
    }
    deserializeJson(state_valve_pos_doc, state_valve_pos_str);   
    
    status_file_present = check_file_exists(actual_valve_pos_path);

    if (valve_position_file_mutex != NULL) {
        if(xSemaphoreTake(valve_position_file_mutex, ( TickType_t ) 10 ) == pdTRUE) { 
            if (status_file_present == 1) {
                actual_valve_pos_json = read_config_file(actual_valve_pos_path);
            }
            xSemaphoreGive(valve_position_file_mutex);
        }
    }
    
    deserializeJson(actual_valve_pos_doc, actual_valve_pos_json);

    for (i=0;i<12;i++) {
        
        valve_number = i;     

        int actual_valve_pos = actual_valve_pos_doc["valve" + String(i)]; 
        int state_valve_pos = state_valve_pos_doc["valve" + String(i) + "_position_" + statemachine_state];

        if (actual_valve_pos > state_valve_pos) {
            
            //valve needs to close with difference. Check if within movements limits is done in move_valve function
            move = actual_valve_pos - state_valve_pos;
            sum_move = sum_move + move;
            direction = 0;
        }
        else {
            //valve needs to open with difference. Check if within movement limits is done in move_valve function
            move = state_valve_pos - actual_valve_pos;
            sum_move = sum_move + move;
            direction = 1;
        }
        
        if (valve_control_data_mutex != NULL) {
            if(xSemaphoreTake(valve_control_data_mutex, ( TickType_t ) 10 ) == pdTRUE) {
                valve_control_data["valve"+String(i)+"_data"][0] = valve_number;
                valve_control_data["valve"+String(i)+"_data"][1] = move;
                valve_control_data["valve"+String(i)+"_data"][2] = direction;
                xSemaphoreGive(valve_control_data_mutex);
            }
        }
    }
    
    if (valve_control_data_mutex != NULL) {
        if(xSemaphoreTake(valve_control_data_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            if (sum_move == 0) {
                valve_control_data["checks"][0] = 0;        //store not required
                valve_control_data["checks"][1] = 1;        //check required
            }
            else {
                valve_control_data["checks"][0] = 1;        //store required
                valve_control_data["checks"][1] = 1;        //check required
            }
            Serial.print("\nValve control data: ");
            serializeJson(valve_control_data, Serial);
            xSemaphoreGive(valve_control_data_mutex);
        }
    }

    //finally the valves can be moved but function move_valve() should only be called if sum_move > 0
    if (sum_move > 0 ) {
        Serial.print("\nValve move sum is > 0 (");
        Serial.print(sum_move);
        Serial.print("). Call function to move valves");
        move_valve();
    }
    else if (sum_move < 0) {
        Serial.print("\nValve move sum is < 0 (");
        Serial.print(sum_move);
        Serial.print("). Error. Don't call function to move valves");
    }
    else {
        Serial.print("\nValve move sum is ");
        Serial.print(sum_move);
        Serial.print(". Don't call function to move valves");
    }
}








        