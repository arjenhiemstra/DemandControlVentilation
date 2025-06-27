#include "fancontrol.h"

void set_fanspeed(String speed) {

    
    HTTPClient http;

    String server_name = "http://192.168.40.74/api.html?vremotecmd=";
    String server_path = server_name + speed;

    http.begin(server_path.c_str());

    //int httpResponseCode = 0;
    int httpResponseCode = http.GET();
      
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.print("\t\t" + payload);
    }
}
