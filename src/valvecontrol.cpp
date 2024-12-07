#include "valvecontrol.h"


void valvecontrol(void) {



}





void read_position_file(void) {

    // Web interface can also create default settings

}


void check_valve_position_file(void) {

    //littlefs should already be mounted (in main.cpp)

    //if json file exists then read the File

    //else create the file and put the default

}


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