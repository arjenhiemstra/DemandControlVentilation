#ifndef VALVECONTROL_H
#define VALVECONTROL_H

#include <LittleFS.h>
#include <ArduinoJson.h>

#include "config_files.h"
#include "globals.h"
#include "general.h"

// function declarations
void move_valve(void);
void valvecontrol(int, int, int, int, int, int);
void all_outputs_off(int, int, int);
void valve_position_statemachine(String);

#endif


