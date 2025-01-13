#ifndef VALVECONTROL_H
#define VALVECONTROL_H

#include <LittleFS.h>
#include <ArduinoJson.h>

#include "config_files.h"

// function declarations
void move_valve(void);
void valvecontrol(int, int, int, int, int, int);
void all_outputs_off(int, int, int);

#endif


