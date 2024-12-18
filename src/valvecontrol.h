#ifndef VALVECONTROL_H
#define VALVECONTROL_H

#include <LittleFS.h>
#include <ArduinoJson.h>

//Function definitions
void move_valve(char*);
void valvecontrol(int, int, int, int, int, int);
void write_valve_position_to_file(int, int);
void all_outputs_off(int, int, int);

void read_position_file(void);
void check_valve_position_file(void);
bool check_file_exist(void);

#endif


