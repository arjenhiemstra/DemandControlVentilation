#include "valvecontrol.h"

void move_valve(char* output) {

    //this function calls all other functions to control the valves. These are the steps:
    //  1. receive input data:
    //      a. JSON file with valve control data which includes valve number, requested valve move and direction
    //      b. enable valve position check, yes or no
    //  2.  Iterate through the JSON file. Valve number decides which dataPin, clockpin and latchPin to use
    //      if 
    //        position check is required:
    //              a. Open position file
    //              b. Calculate new valve move positions (either as requested or max/min)
    //              c. Call valve move function to make actual move
    //              d. Write new positions to file
    //      else
    //        call valve movement function

    //Data pins for 74HC595
    int clockPin1 = 16; // D13 Pin connected to SH_CP (11) of 74HC595
    int latchPin1 = 17; // D12 Pin connected to ST_CP (12) of 74HC595
    int dataPin1 = 18;  // D14 Pin connected to DS (14) of 74HC595

    //Data pins for 74HC595
    int clockPin2 = 5; // D26 Pin connected to SH_CP (11) of 74HC595
    int latchPin2 = 6; // D25 Pin connected to ST_CP (12) of 74HC595
    int dataPin2 = 7;  // D27 Pin connected to DS (14) of 74HC595

    int clockPin;
    int latchPin;
    int dataPin;

    int i;

    pinMode(latchPin1, OUTPUT);
    pinMode(clockPin1, OUTPUT);
    pinMode(dataPin1, OUTPUT);

    pinMode(latchPin2, OUTPUT);
    pinMode(clockPin2, OUTPUT);
    pinMode(dataPin2, OUTPUT);

    all_outputs_off(dataPin1, clockPin1, latchPin1);
    all_outputs_off(dataPin2, clockPin2, latchPin2);

    Serial.print(output);
    
    JsonDocument input;
    deserializeJson(input, output);

    for(i=0;i<12;i++) {

        if (input["valve"+String(i)+"_data"][0] < 6) {
            latchPin = latchPin1;
            clockPin = clockPin1;
            dataPin = dataPin1;
        }
        else {
            latchPin = latchPin2;
            clockPin = clockPin2;
            dataPin = dataPin2;
        }

        //Only call function if actual move requested is >0
        if(input["valve"+String(i)+"_data"][1] > 0) {
            valvecontrol(input["valve"+String(i)+"_data"][2], input["valve"+String(i)+"_data"][1], input["valve"+String(i)+"_data"][0] , latchPin, clockPin, dataPin);
        }
    }
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

    //Valve 0 - 5 has the same output as valves 6-11 so new variable 'valve' required to select output
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
          delay(10); // This delay decides the speed of turning in ms
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
          delay(10);
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

void read_position_file(fs::FS &fs, const char *path) {

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
}



void write_valve_position_to_file(int valve_number, int moved_positions) { }



bool check_file_exist(void) {

    if (LittleFS.exists("/valvepositions.txt")) {
        Serial.println("File exists");
        return true;
    } 
    else {
        Serial.println("File does not exist");
        return false;
    }
}



void check_valve_position_file(void) { }


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



        