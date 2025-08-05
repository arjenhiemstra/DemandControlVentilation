#include "notifyClients.h"

#include <Arduino.h>  //fix to prevent INADDR_NONE preprocessor issues
AsyncWebSocket ws("/ws");

SemaphoreHandle_t mutexWSsend;

unsigned long LastotaWsUpdate = 0;
size_t content_len = 0;

void notifyClients(const char* message)
{
    yield();
    // if (xSemaphoreTake(mutexWSsend, (TickType_t)100 / portTICK_PERIOD_MS) == pdTRUE)
    // {
    ws.textAll(message);
    //     xSemaphoreGive(mutexWSsend);
    // }
}

void notifyClients(JsonObject obj)
{
    size_t len = measureJson(obj);

    char* buffer = new char[len + 1];

    if (buffer)
    {
        serializeJson(obj, buffer, len + 1);
        obj.clear();
        notifyClients(buffer);
    }
    delete[] buffer;
}
