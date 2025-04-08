/*

Rolling  average for sensor

- This function is called after sensor is read. 
- The oldest value is removed from the array
- All other values are moved one position up
- The new value is moved into the first position
- The new average value of the array is calculated
- The new average function is stored globally (similar structure to sensor readings)

*/

#include "signalprocessor.h"

float average(int bus, int slot, int measurement, float value) {

    float temp[2][8][3][SENSOR_SAMPLES] = {0};
    float avg;
    int i;

    if(i==10) {
        //1st reading is position 0
        //2nd reading is position 1
        //..
        //8th reading

        temp[bus][slot][measurement][i] = value;
        i=0;
    }
    i++;

    return avg;

}
