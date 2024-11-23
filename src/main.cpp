#include <Arduino.h>
#include <WiFi.h>

// put function declarations here:
void setup_wifi();


//Variables
const char* ssid = "DIRKG"; //WIFI SSID
const char* password = "07537978646248256575"; //WIFI password



void setup() {
  // put your setup code here, to run once:
  //setup_wifi();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Anybody there??????");
}

// put function definitions here:
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