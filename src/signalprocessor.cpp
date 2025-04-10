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

float sensor_fifo[2][8][3][10];
float temp = 0;
int fifoSize = 0;           // Current number of elements in the FIFO.
int fifoHead = 0;           // Index of the oldest element in the FIFO.

void fifo_average(void) {

    float sensor_data[2][8][3];
    
    if (xQueuePeek(sensor_queue, &sensor_data, 0 ) == pdTRUE) {
        //Fill new array with data until queque is full
        for(int bus=0;bus<2;bus++) {
            for(int slot=0;slot<8;slot++) {
                for(int measurement=0;measurement<3;measurement++) {
                    fifoPush(sensor_data[bus][slot][measurement]); 
                }
            }
        }


    }

}

void fifoPush(float value) {
    if (fifoSize < MAX_FIFO_SIZE) {
        // Add the value to the next available position.
        sensor_fifo[2][8][3][(fifoHead + fifoSize) % MAX_FIFO_SIZE] = value;
        fifoSize++;
    } else {
        // Overwrite the oldest value and move the head forward.
        sensor_fifo[2][8][3][fifoHead] = value;
        fifoHead = (fifoHead + 1) % MAX_FIFO_SIZE;
    }
}

float fifoAverage() {
    float sum = 0.0;
    for (int i = 0; i < fifoSize; i++) {
        sum += sensor_fifo[2][8][3][(fifoHead + i) % MAX_FIFO_SIZE];
    }
    return fifoSize > 0 ? sum / fifoSize : 0.0;
}