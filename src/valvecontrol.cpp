#include "valvecontrol.h"

//Global varaible defined in task_web
extern JsonDocument valve_control_data;

//void move_valve(char* output) {
void move_valve(void) {

    //Data pins for 74HC595
    int clockPin1 = 11; // IO11 on ESP32-S3 and D13 on ESP32, connected to SH_CP (11) of 74HC595
    int latchPin1 = 12; // IO12 on ESP32-S3 and D12 on ESP32, connected to ST_CP (12) of 74HC595
    int dataPin1 = 13;  // IO13 on ESP32-S3 and D14 on ESP32, connected to DS (14) of 74HC595

    //Data pins for 74HC595
    int clockPin2 = 14; // IO14 on ESP32-S3 and D26 on ESP32, connected to SH_CP (11) of 74HC595
    int latchPin2 = 15; // IO15 on ESP32-S3 and D25 on ESP32, connected to ST_CP (12) of 74HC595
    int dataPin2 = 16;  // IO16 on ESP32-S3 and D27 on ESP32, connected to DS (14) of 74HC595

    int clockPin;
    int latchPin;
    int dataPin;

    //Still required? already happens at init. Try if can be removed if outputs work
    pinMode(latchPin1, OUTPUT);
    pinMode(clockPin1, OUTPUT);
    pinMode(dataPin1, OUTPUT);

    pinMode(latchPin2, OUTPUT);
    pinMode(clockPin2, OUTPUT);
    pinMode(dataPin2, OUTPUT);

    const char* path = "/valvepositions.json";
    bool status_file_present;
    int valve_number;
    int valve_position_change;
    int new_valve_position_change;
    int new_valve_position;
    int direction;
    int store_valve_position;
    int check_valve_position;
    int valve_pos;

    String json;
    JsonDocument doc;

    store_valve_position = valve_control_data["checks"][0];
    check_valve_position = valve_control_data["checks"][1];

    // Read valve status file
    status_file_present = check_file_exists(path);

    if (status_file_present == 1) {

        json = read_config_file(path);
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
    Serial.print("\n\n");
    Serial.print("Store new valve Position: " + String(store_valve_position) + ", Check valve position: " + String(check_valve_position));
    Serial.print("\n");

    for(int i=0;i<12;i++) {

        valve_number = valve_control_data["valve"+String(i)+"_data"][0];
        valve_position_change = valve_control_data["valve"+String(i)+"_data"][1];
        direction = valve_control_data["valve"+String(i)+"_data"][2];
        valve_pos = doc["valve"+String(i)];

        Serial.print("\n");
        Serial.print("valve_number: " + String(valve_number) + ", position_change: " + String(valve_position_change) + ", direction: " + direction);

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
            //put check position code here
            if(direction == 0 && (valve_position_change + valve_pos)>24) {
                new_valve_position_change = 24 - valve_pos;
                Serial.print("\n");
                Serial.print ("Request move is: " + String(valve_position_change) + ". Current_position is: " + String(valve_pos) + ". Valve will move: " + String(new_valve_position_change));
                valvecontrol(direction, new_valve_position_change, valve_number, dataPin, clockPin, latchPin);
                new_valve_position = 24;
            }
            else {
                new_valve_position_change = valve_position_change;
                Serial.print("\n");
                Serial.print ("Request move is: " + String(valve_position_change) + ". Current_position is: " + String(valve_pos) + ". Valve will move: " + String(new_valve_position_change));
                valvecontrol(direction, new_valve_position_change, valve_number, dataPin, clockPin, latchPin);
                new_valve_position = valve_pos + new_valve_position_change;
            }
            if (direction == 1 && (valve_pos - valve_position_change) < 0) {
                new_valve_position_change = valve_pos;
                Serial.print("\n");
                Serial.print ("Request move is: " + String(valve_position_change) + ". Current_position is: " + String(valve_pos) + ". Valve will move: " + String(new_valve_position_change));
                valvecontrol(direction, new_valve_position_change, valve_number, dataPin, clockPin, latchPin);
                new_valve_position = 0;
            }
            else {
                new_valve_position_change = valve_position_change;
                Serial.print("\n");
                Serial.print ("Request move is: " + String(valve_position_change) + ". Current_position is: " + String(valve_pos) + ". Valve will move: " + String(new_valve_position_change));
                valvecontrol(direction, new_valve_position_change, valve_number, dataPin, clockPin, latchPin);
                new_valve_position = valve_pos - new_valve_position_change;
            }
        }
        else {
            //no check required so just proceed with calling move valves function if movement is > 0
            valvecontrol(direction, valve_position_change, valve_number, dataPin, clockPin, latchPin);
        }

        //Storing new valve positions only makes sense in combination with new calculated positions
        if (store_valve_position == 1 && check_valve_position == 1) {
            //code to write new positions to file
            doc["valve"+String(i)] = new_valve_position;
        }
    }
    Serial.print("\n\n");

    //write doc to file
    String new_valve_positions;
    File file;

    //Convert from JsonDocument to String
    serializeJson(doc, new_valve_positions);

    Serial.print(new_valve_positions);
    Serial.print("\n\n");

    write_config_file(path, new_valve_positions);

}

void valvecontrol(int direction, int position_change, int valve_number, int dataPin, int clockPin, int latchPin ) {

    //This function moves one valve based on 3 inputs. If multiple valves need to move, this function is called multiple 
    //times. This function does not check if the valves are controlled
    //outside their operating window so all requests for valve movement should be checked by another function
    //before calling this function. The reason why not to put the operating window check in this functions is that the 
    //user must be able to calibrated the valves, i.e. line up up the valves with the registered positions.

    // Local variables
    int output[3][4] = { 0 };       // Output array with switching pattern, initialise at 0;
    int i;                          // Counter for creating output array
    int j;                          // Counter for
    int k;                          // Counter to iterate through output array

    // Variables which are application settings
    int cycles = 24;        //the number if cycles to complete one rotation of thre shaft

    //switching pattern for steppermotor in 8 bits.
    int pattern[4] = { B00000101, B00001001, B00001010, B00000110 };

    //Valve 0 - 5 has the same output as valves 6-11
    if (valve_number >= 6) {
        valve_number = valve_number - 6;
    }

    switch (valve_number) {
        case 0:
            for (i=0; i<4; i++) {
                output[0][i] = pattern[i];
                output[1][i] = 0;
                output[2][i] = 0;
            }
            break;  
        case 1:
            for (i=0; i<4; i++) {
                output[0][i] = pattern[i];
                output[0][i] = output[0][i] << 4; //shift four positions
                output[1][i] = 0;
                output[2][i] = 0;
            }
            break;
        case 2:
            for (i=0; i<4; i++) {
                output[0][i] = 0;
                output[1][i] = pattern[i];
                output[2][i] = 0;
            }
            break;
        case 3:
            for (i=0; i<4; i++) {
                output[0][i] = 0;
                output[1][i] = pattern[i];
                output[1][i] = output[1][i] << 4; //shift four positions
                output[2][i] = 0;
            }
            break;
        case 4:
            for (i=0; i<4; i++) {
                output[0][i] = 0;
                output[1][i] = 0;
                output[2][i] = pattern[i];
            }
            break;
        case 5:
            for (i=0; i<4; i++) {
                output[0][i] = 0;
                output[1][i] = 0;
                output[2][i] = pattern[i];
                output[2][i] = output[2][i] << 4; //shift four positions
            }
            break;
    }

  //Direction is 0 (forwards)
  if (direction == 0) {
    //Loop to run the number of cycles to make one turn * the number of turns to make requested_position_change
      for (j=0; j < (cycles * position_change); j++) {
        //Loop to make one cycle of the four coils in the motor
        for (k = 0; k < 4; k++) {
          //ground latchPin and hold low for as long as you are transmitting
          digitalWrite(latchPin, 0);
          shiftOut(dataPin, clockPin, MSBFIRST, output[2][k]);
          shiftOut(dataPin, clockPin, MSBFIRST, output[1][k]);
          shiftOut(dataPin, clockPin, MSBFIRST, output[0][k]);
          //take the latch pin high so the LEDs will light up:
          digitalWrite(latchPin, HIGH);
          //delay(10); // This delay decides the speed of turning in ms
          vTaskDelay(10);      
        }
      }
    //after running all outputs should be off
    all_outputs_off(dataPin, clockPin, latchPin);
  }

  //Direction is 1 (backwards)
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
          //delay(10);
          vTaskDelay(10);
        }
      }
    all_outputs_off(dataPin, clockPin, latchPin);
  }
}

void all_outputs_off(int dataPin, int clockPin, int latchPin) {

    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
}








/*void read_position_file(fs::FS &fs, const char *path) {

  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return;
  }

  Serial.println("- read from file:");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}*/

/* Python example

def checkValvePositionFile():
    # Check is valvePositions.json exists and if not write the default positions
    filename="valvePositions.json"
    if filename in uos.listdir():
        print("\nValve status file found.")
        if uos.stat(filename)[6] < 100:
            print("\nValve status file found, but too small. Creating new default file")
            defaultValvePositions()
        else:
            print("Everything ok with valve status file")
    else:
        print("\nValve status file not found. Creating new default one")
        defaultValvePositions() */



        