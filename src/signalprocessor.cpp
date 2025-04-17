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

float sensor_fifo[2][8][3][20];
float sum[48] = {0.0};
float avg[48] = {0.0};
int fifoSize[48] = {0};           // Current number of elements in the FIFO.
int fifoHead[48] = {0};           // Index of the oldest element in the FIFO.

void sensor_data_average(void) {

    float sensor_data[2][8][3];         //actual sensor data from queque
    float sensor_avg_data[2][8][3];     //Average sensor data to queque
    int pos;
    
    if (xQueuePeek(sensor_queue, &sensor_data, 0 ) == pdTRUE) {
        pos=0;
        for(int bus=0;bus<2;bus++) {
            for(int slot=0;slot<8;slot++) {
                for(int measurement=0;measurement<3;measurement++) {                   
                    fifoPush(bus, slot, measurement, sensor_data[bus][slot][measurement], pos);
                    //sensor_avg_data[bus][slot][measurement] = fifoAverage(bus, slot, measurement, pos);
                    sensor_avg_data[bus][slot][measurement] = avg[pos];
                    pos++;      //counter for fifoSize and fifoHead
                }
            }
        }
        if(sensor_avg_queue !=NULL) {
            xQueueOverwrite(sensor_avg_queue, &sensor_avg_data);
        }
        else {
            Serial.print("Send - Average sensor data queue handle is NULL");
        }
    }
}

void fifoPush(int bus, int slot, int measurement, float value, int pos) {

    if (fifoSize[pos] < MAX_FIFO_SIZE) {
        // Add the value to the next available position.
        sensor_fifo[bus][slot][measurement][(fifoHead[pos] + fifoSize[pos]) % MAX_FIFO_SIZE] = value;
        sum[pos] += value;
        fifoSize[pos] = fifoSize[pos] + 1;
    } 
    else {
        // Overwrite the oldest value and move the head forward.
        sum[pos] -= sensor_fifo[bus][slot][measurement][fifoHead[pos]];
        sensor_fifo[bus][slot][measurement][fifoHead[pos]] = value;
        sum[pos] += value;
        fifoHead[pos] = (fifoHead[pos] + 1) % MAX_FIFO_SIZE;
    }

    avg[pos] = sum[pos] / fifoSize[pos];

    /*Serial.print("\n");
    Serial.print(fifoHead[pos]);
    Serial.print("\t\t");
    Serial.print(fifoSize[pos]);
    Serial.print("\t\t");
    Serial.print(value);
    Serial.print("\t\t");
    Serial.print(sum[pos]);
    Serial.print("\t\t");
    Serial.print(avg[pos]);*/

}

