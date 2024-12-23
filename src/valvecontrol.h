#ifndef VALVECONTROL_H
#define VALVECONTROL_H

#include <LittleFS.h>
#include <ArduinoJson.h>

#include "config_files.h"

//Function definitions
void move_valve(char*);
void valvecontrol(int, int, int, int, int, int);
void all_outputs_off(int, int, int);

#endif


