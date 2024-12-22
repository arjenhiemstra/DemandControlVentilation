#ifndef VALVECONTROL_H
#define VALVECONTROL_H

#include <LittleFS.h>
#include <ArduinoJson.h>

#include "config_files.h"

//Function definitions
void move_valve(char*);
void valvecontrol(int, int, int, int, int, int);
void all_outputs_off(int, int, int);
//bool check_valve_position_file_exists(void);
bool verify_valve_position_file_contents(void);
void write_new_valve_positions_to_file(void);

#endif


