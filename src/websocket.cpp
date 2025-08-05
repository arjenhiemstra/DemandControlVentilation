#include "websocket.h"

static std::unordered_map<uint32_t, std::string> g_wsBuffers;
AsyncWebServer wsserver(8000);
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

void websocketInit() {
    // attach AsyncWebSocket
    ws.onEvent(onWsEvent);
    wsserver.addHandler(&ws);
    wsserver.begin();
}

void jsonWsSend(const char *rootName) {
    JsonDocument root;

    if (strcmp(rootName, "wifisettings") == 0) {
        JsonObject nested = root[rootName].to<JsonObject>();
    } else if (strcmp(rootName, "wifistat") == 0) {
        JsonObject wifiinfo = root[rootName].to<JsonObject>();
    }
    notifyClients(root.as<JsonObject>());
}

void handle_ws_message(JsonObject root) {
    const char *settings_network_path = "/json/settings_network.json";
    const char *settings_mqtt_path = "/json/settings_mqtt.json";
    const char *settings_i2c_path = "/json/settings_i2c.json";
    const char *settings_fan_path = "/json/settings_fan.json";
    const char *settings_statemachine_path = "/json/settings_statemachine.json";
    const char *settings_influxdb_path = "/json/settings_influxdb.json";
    const char *settings_rtc_path = "/json/settings_rtc.json";

    JsonDocument rootdoc;
    if (root["settings_network"].is<bool>() && root["settings_network"].as<bool>()) {
        bool settings_network_file_present = 0;
        String settings_network_json = "{\"enable_dhcp\":\"Off\",\"ssid\":\"\",\"wifi_password\":\"\",\"ip_address\":\"\",\"subnet_mask\":\"\",\"gateway\":\"\",\"primary_dns\":\"\",\"secondary_dns\":\"\"}";
        deserializeJson(rootdoc, settings_network_json);
    } else if (root["settings_mqtt"].is<bool>() && root["settings_mqtt"].as<bool>()) {
        Serial.println("settings_mqtt");
        bool settings_mqtt_file_present = false;
        String settings_mqtt_json = "{\"enable_mqtt\":\"On\",\"mqtt_server\":\"\",\"mqtt_port\":\"1883\",\"mqtt_base_topic\":\"OSVentilation\"}";
        deserializeJson(rootdoc, settings_mqtt_json);
    } else if (root["settings_i2c"].is<bool>() && root["settings_i2c"].as<bool>()) {
        bool settings_i2c_file_present = false;
        String settings_i2c_json = "{\"bus0_multiplexer_address\":\"112\",\"bus1_multiplexer_address\":\"112\",\"enable_lcd\":\"On\",\"display_i2c_address\":\"39\"}";
        deserializeJson(rootdoc, settings_i2c_json);
    } else if (root["settings_fan"].is<bool>() && root["settings_fan"].as<bool>()) {
        bool settings_fan_file_present = false;
        String settings_fan_json = "{\"fan_control_mode\":\"HTTPAPI\",\"fan_control_mqtt_server\":\"\",\"fan_control_mqtt_port\":\"\",\"fan_control_mqtt_topic\":\"\",\"fan_control_url_high_speed\":\"\",\"fan_control_url_medium_speed\":\"\",\"fan_control_url_low_speed\":\"\"}";
        deserializeJson(rootdoc, settings_fan_json);
    } else if (root["settings_influxdb"].is<bool>() && root["settings_influxdb"].as<bool>()) {
        bool settings_influxdb_file_present = false;
        String settings_influxdb_json = "{\"enable_influxdb\":\"Off\",\"influxdb_url\":\"\",\"influxdb_org\":\"\",\"influxdb_bucket\":\"OSVentilationC\",\"influxdb_token\":\"\"}";
        deserializeJson(rootdoc, settings_influxdb_json);
    } else if (root["settings_rtc"].is<bool>() && root["settings_rtc"].as<bool>()) {
        bool settings_rtc_file_present = false;
        String settings_rtc_json = "{\"ntp_server\":\"pool.ntp.org\",\"timezone\":\"CET-1CEST,M3.5.0,M10.5.0/3\"}";
        deserializeJson(rootdoc, settings_rtc_json);
    }
    notifyClients(rootdoc.as<JsonObject>());
}
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (!client->id())
        return;

    if (type == WS_EVT_CONNECT) {
        client->setCloseClientOnQueueFull(false);
        return;
    } else if (type == WS_EVT_DISCONNECT) {
        g_wsBuffers[client->id()].clear();
        // Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id(), client->id());
    } else if (type == WS_EVT_ERROR) {
        g_wsBuffers[client->id()].clear();
        // Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
    } else if (type == WS_EVT_PONG) {
        // Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
    }

    else if (type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;

        // info->index == 0 => this is the beginning of a new message
        if (info->index == 0) {
            // Clear (or create) the buffer for this client
            g_wsBuffers[client->id()].clear();
        }

        // Append this frame’s data if opcode == WS_TEXT
        if (info->opcode == WS_TEXT) {
            auto &msgBuffer = g_wsBuffers[client->id()];
            msgBuffer.append(reinterpret_cast<char *>(data), len);

            size_t currentSize = info->index + len;

            // If this is the final frame, we parse the entire message
            if (currentSize >= info->len) {
                JsonDocument wsDoc;

                auto error = deserializeJson(wsDoc, msgBuffer);
                if (error) {
                    if (msgBuffer == "ping") {
                        client->text("pong");
                    } else {
                        // E_LOG("[WS] JSON parse error: %s", error.c_str());
                        Serial.println(msgBuffer.c_str());
                    }
                }
                // buffer no longer needed
                g_wsBuffers[client->id()].clear();

                // if there was an error, we can now safely return (buffer is cleared)
                if (error)
                    return;

                // Convert doc to a JsonObject
                JsonObject wsObj = wsDoc.as<JsonObject>();
                if (wsObj.isNull()) {
                    return;
                }
                handle_ws_message(wsObj);
            } else {
                // WS_TEXT partial frame handled, return to process the next message
                return;
            }

            // at this point the message is either handled or can be discarded, clear the buffer before return of function
            g_wsBuffers[client->id()].clear();
        }
    }
}
