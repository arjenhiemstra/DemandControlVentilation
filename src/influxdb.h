#ifndef INFLUXDB_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define INFLUXDB_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <InfluxDbClient.h>

#include "globals.h"

#define INFLUXDB_URL "http://192.168.0.14:8086"
#define INFLUXDB_TOKEN "UwvnvfsMZ-MBYauMj0tPdRG1AdJXcRSV3N-JWjnBvhXXs2sEejVoQYqzNQbLXDrgeDDbnpisumDzSVWGZ5c_QA=="
#define INFLUXDB_ORG "Lourens"
#define INFLUXDB_BUCKET "OSVentilationC"

// function declarations
void write_sensor_data(void);


#endif