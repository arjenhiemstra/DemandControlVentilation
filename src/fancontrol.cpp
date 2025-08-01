#include "fancontrol.h"

void set_fanspeed(String speed) {
    
    int httpResponseCode = 0;
    bool settings_file_present = 0;
    const char* path = "/json/settings_fan.json";
    
    String fan_control_settings_str = "";
    String fanspeed_temp = "";
    String message = "";
    String http_payload = "";

    HTTPClient http;
    JsonDocument doc;  

    if (fanspeed_mutex != NULL) {
        if(xSemaphoreTake(fanspeed_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            fanspeed_temp = fanspeed;
            xSemaphoreGive(fanspeed_mutex);
        }
    }

    if (settings_fan_mutex != NULL) {
        if(xSemaphoreTake(settings_fan_mutex, ( TickType_t ) 100 ) == pdTRUE) {
            settings_file_present = check_file_exists(path);
            if (settings_file_present == 1) {
                fan_control_settings_str = read_config_file(path);
                deserializeJson(doc, fan_control_settings_str);
            }
            xSemaphoreGive(settings_fan_mutex);
        }
    }
    
    String fan_control_mode = doc[String("fan_control_mode")];
    message = "Fanspeed: " + String(fanspeed_temp);
    print_message(message);
        
    if (fan_control_mode == "MQTT publish") {
        message = "Using MQTT to set fan speed";
        print_message(message);
        String fan_control_mqtt_topic = doc[String("fan_control_mqtt_topic")];
        //Not yet implmented, subscribe to MQTT topic, Create callback function
    }
    else if (fan_control_mode == "HTTP API") {
        message = "Using HTTP API to set fan speed";
        print_message(message);
        String fan_control_url_high_speed = doc[("fan_control_url_high_speed")];
        String fan_control_url_medium_speed = doc[("fan_control_url_medium_speed")];
        String fan_control_url_low_speed = doc[("fan_control_url_low_speed")];
        if (fanspeed_temp == "Low") {
            message = "Low speed selected";
            print_message(message);
            http.begin(fan_control_url_low_speed.c_str());
            httpResponseCode = http.GET();
            if (httpResponseCode>0) {
                http_payload = http.getString();
                message = "HTTP Response code: " + String(httpResponseCode) + ", HTTP payload: " + String(http_payload);
                print_message(message);
            }

        }
        else if (fanspeed_temp == "Medium") {
            message = "Medium speed selected";
            print_message(message);
            http.begin(fan_control_url_medium_speed.c_str());
            httpResponseCode = http.GET();
            if (httpResponseCode>0) {
                http_payload = http.getString();
                message = "HTTP Response code: " + String(httpResponseCode) + ", HTTP payload: " + String(http_payload);
                print_message(message);
            }
        }
        else if (fanspeed_temp == "High") {
            message = "High speed selected";
            print_message(message);
            http.begin(fan_control_url_high_speed.c_str());
            httpResponseCode = http.GET();
            if (httpResponseCode>0) {
                http_payload = http.getString();
                message = "HTTP Response code: " + String(httpResponseCode) + ", HTTP payload: " + String(http_payload);
                print_message(message);
            }
        }
    }
    else {
        message = "No method to set fan speed.";
        print_message(message);
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
