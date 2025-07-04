#include "fancontrol.h"

void set_fanspeed(String speed) {
    
    HTTPClient http;
    JsonDocument doc;
    String fan_control_settings_str = "";
    String fanspeed_temp = "";
    bool settings_file_present = 0;
    const char* path = "/json/settings_fan.json";

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            fanspeed_temp = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    if (settings_fan_mutex != NULL) {
        if(xSemaphoreTake(settings_fan_mutex, ( TickType_t ) 10 ) == pdTRUE) {
            settings_file_present = check_file_exists(path);
            if (settings_file_present == 1) {
                fan_control_settings_str = read_config_file(path);
                deserializeJson(doc, fan_control_settings_str);
            }
            xSemaphoreGive(settings_fan_mutex);
        }
    }

    String fan_control_mode = doc[String("fan_control_mode")];
    Serial.print("Fanspeed: " + String(fanspeed_temp));
    
    if (fan_control_mode == "MQTT publish") {
        Serial.print("\nUsing MQTT to set fan speed");
        String fan_control_mqtt_topic = doc[String("fan_control_mqtt_topic")];
        //subscribe to MQTT topic
        //Create callback function
    }
    else if (fan_control_mode == "HTTP API") {
        Serial.print("\nUsing HTTP API to set fan speed");
        String fan_control_url_high_speed = doc[("fan_control_url_high_speed")];
        String fan_control_url_medium_speed = doc[("fan_control_url_medium_speed")];
        String fan_control_url_low_speed = doc[("fan_control_url_low_speed")];

        if (fanspeed_temp = "Low") {
            http.begin(fan_control_url_low_speed.c_str());
        }
        else if (fanspeed_temp == "Medium") {
            http.begin(fan_control_url_medium_speed.c_str());
        }
        else if (fanspeed_temp == "High") {
            http.begin(fan_control_url_high_speed.c_str());
        }
        
        int httpResponseCode = http.GET();
      
        if (httpResponseCode>0) {
            Serial.print("\nHTTP Response code: ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            Serial.print("\t\t" + payload);
        }
    }
    else {
        Serial.print("No method to set fan speed.");
    }



    /*
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

    */
}
