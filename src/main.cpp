#include <Arduino.h>
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <LittleFS.h>

#include "main.h"
#include "task1.h"
#include "task2.h"
#include "task_web.h"
#include "valvecontrol.h"

//Variables
const char* ssid = "DIRK3"; //WIFI SSID
const char* password = "095679706460482465742852"; //WIFI password

//TaskHandle_t Task1;

void setup() {

  Serial.begin(115200);

  // First switch off all outputs which randomly come up at power on
  init_registers();

  // Begin LittleFS
  if (!LittleFS.begin())
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  vTaskStartScheduler();

  setup_wifi();
  startTask1code();
  //startTask2code();
  startTaskwebcode();
  startTaskvalvecontrol();

}

void loop() { }

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

}

void init_registers(void) {

  //Data pins for 74HC595
  int clockPin1 = 11; // IO11 on ESP32-S3 and D13 on ESP32, connected to SH_CP (11) of 74HC595
  int latchPin1 = 12; // IO12 on ESP32-S3 and D12 on ESP32, connected to ST_CP (12) of 74HC595
  int dataPin1 = 13;  // IO13 on ESP32-S3 and D14 on ESP32, connected to DS (14) of 74HC595

  //Data pins for 74HC595
  int clockPin2 = 14; // IO14 on ESP32-S3 and D26 on ESP32, connected to SH_CP (11) of 74HC595
  int latchPin2 = 15; // IO15 on ESP32-S3 and D25 on ESP32, connected to ST_CP (12) of 74HC595
  int dataPin2 = 16;  // IO16 on ESP32-S3 and D27 on ESP32, connected to DS (14) of 74HC595

  pinMode(latchPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);

  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  
  all_outputs_off(dataPin1, clockPin1, latchPin1);
  all_outputs_off(dataPin2, clockPin2, latchPin2);

}
