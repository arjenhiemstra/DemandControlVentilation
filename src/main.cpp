#include <Arduino.h>
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <LittleFS.h>

#include "task1.h"
#include "task2.h"
#include "task_web.h"

// put function declarations here:
void setup_wifi();

//Variables
const char* ssid = "DIRK3"; //WIFI SSID
const char* password = "095679706460482465742852"; //WIFI password

void setup() {

  Serial.begin(115200);

  // Begin LittleFS
  if (!LittleFS.begin())
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  setup_wifi();
  //startTask1code();
  //startTask2code();
  startTaskwebcode();

  //create position fil with all positions set to zero
  //
  // { valve0:0, valve1:0, valve2:0, valve3:0, valve4:0, valve5:0, valve6:0, valve7:0, valve8:0, valve9:0, valve10:0, valve11:0 }

  

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


