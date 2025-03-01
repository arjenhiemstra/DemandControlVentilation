#include "wifi.h"

//open config file and check if SSID and password are not empty
//if empty start WIFI as access point
//else connect to access point defined in SSID with either DHCP or fixed 

void config_wifi(void) {

    const char* path = "/json/settings_network.json";
    
    bool network_config_file_present = 0;
    
    String network_config_string;
    String ssid;
    String wifi_password;
    String ip_address;
    String subnet_mask;
    String gateway;
    String primary_dns;
    String secondary_dns;

    JsonDocument network_config;

    network_config_file_present = check_file_exists(path);

    if (network_config_file_present = 1) {
        File file = LittleFS.open(path, "r");

        while(file.available()) {
            network_config_string = file.readString();
        }
        file.close();
        
        deserializeJson(network_config, network_config_string);

        String ssid = network_config[String("ssid")];
        
        /*wifi_password = network_config[String("wifi_password")];
        ip_address = network_config[String("ip_address")];
        subnet_mask = network_config[String("subnet_mask")];
        gateway = network_config[String("gateway")];
        primary_dns = network_config[String("primary_dns")];
        secondary_dns = network_config[String("secondary_dns")];*/
        
    }

    //Print JsonDocument
    serializeJson(network_config, Serial);
    Serial.print("\n\n");

    if (ssid != "" && wifi_password != "") {
        //Connect to access point
        WiFi.mode(WIFI_STA);

        if (ip_address != "" && subnet_mask != "" && gateway != "" && (primary_dns != "" || secondary_dns != "")) {
            //WiFi.config(ip_address,subnet_mask, gateway);
            //WiFi.setDNS(primary_dns, secondary_dns);
        }

        WiFi.begin(ssid, wifi_password);

        if (WiFi.waitForConnectResult() != WL_CONNECTED) {
            Serial.println("WiFi Failed!");
            return;
        }

        Serial.print("\n\nIP Address: ");
        Serial.print(WiFi.localIP());
        Serial.print("\n\n");
    }
    else {
        //No connection info so setup as access point
        WiFi.mode(WIFI_AP);
    }

}