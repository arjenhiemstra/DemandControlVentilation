#include <Arduino.h>
#include <WiFi.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "task1.h"
#include "task2.h"
#include "task_web.h"

// put function declarations here:
void setup_wifi();

//Variables
const char* ssid = "DIRKG"; //WIFI SSID
const char* password = "07537978646248256575"; //WIFI password

void setup() {
  // put your setup code here, to run once:
  //setup_wifi();
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  setup_wifi();
  startTask1code();
  startTask2code();
  startTaskwebcode();

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


