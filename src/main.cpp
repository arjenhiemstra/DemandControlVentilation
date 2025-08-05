#include "main.h"

// Variables
// const char* ssid = ""; //WIFI SSID
// const char* password = ""; //WIFI password

void setup() {
    Serial.begin(115200);
    Serial.println("Starting...");

    pinMode(latchPin1, OUTPUT);
    pinMode(clockPin1, OUTPUT);
    pinMode(dataPin1, OUTPUT);

    pinMode(latchPin2, OUTPUT);
    pinMode(clockPin2, OUTPUT);
    pinMode(dataPin2, OUTPUT);

    sensor_config_file_mutex = xSemaphoreCreateMutex();
    valve_position_file_mutex = xSemaphoreCreateMutex();
    date_time_mutex = xSemaphoreCreateMutex();
    settings_network_mutex = xSemaphoreCreateMutex();
    settings_mqtt_mutex = xSemaphoreCreateMutex();
    settings_i2c_mutex = xSemaphoreCreateMutex();
    settings_fan_mutex = xSemaphoreCreateMutex();
    settings_statemachine_mutex = xSemaphoreCreateMutex();
    settings_influxdb_mutex = xSemaphoreCreateMutex();
    settings_rtc_mutex = xSemaphoreCreateMutex();

    statemachine_state_mutex = xSemaphoreCreateMutex();
    valve_control_data_mutex = xSemaphoreCreateMutex();
    fanspeed_mutex = xSemaphoreCreateMutex();
    lock_valve_move_mutex = xSemaphoreCreateMutex();
    ap_active_mutex = xSemaphoreCreateMutex();

    settings_state_day_mutex = xSemaphoreCreateMutex();
    settings_state_night_mutex = xSemaphoreCreateMutex();
    settings_state_highco2day_mutex = xSemaphoreCreateMutex();
    settings_state_highco2night_mutex = xSemaphoreCreateMutex();
    settings_state_highrhday_mutex = xSemaphoreCreateMutex();
    settings_state_highrhnight_mutex = xSemaphoreCreateMutex();
    settings_state_cooking_mutex = xSemaphoreCreateMutex();
    settings_state_cyclingday_mutex = xSemaphoreCreateMutex();
    settings_state_cyclingnight_mutex = xSemaphoreCreateMutex();

    // Init queues for sensors
    float temp[2][8][3];
    char txBuffer[400];
    sensor_queue = xQueueCreate(1, sizeof(temp));
    sensor_avg_queue = xQueueCreate(1, sizeof(temp));
    webserial_queue = xQueueCreate(30, sizeof(txBuffer));

    if (webserial_queue == 0 || sensor_queue == 0 || sensor_avg_queue == 0) {
        Serial.print("\nFailed to create queues");
    }
    // First switch off all outputs which may have come randomly at power on
    init_registers();

    // Begin LittleFS
    if (!LittleFS.begin()) {
        Serial.println("\nAn Error has occurred while mounting LittleFS");
        return;
    }

    // setup_wifi();
    start_task_wifi();
    read_mqtt_config();
    read_influxdb_config();
    read_i2c_config();
    read_time_settings();
    read_fan_config();
    sensor_config_data_read();
    valve_settings_config_read();

    // Wait a little after reading config
    vTaskDelay(100);

    // Start tasks
    startTaskwebcode();
    start_task_valvecontrol();
    start_task_i2c();
    start_task_statemachine();
    start_task_mqtt();
    start_task_neopixel();
    // start_task_system();
    start_task_wserial();

    vTaskDelay(60000);  // Only write to influxDB when all tasks are running
    // start_task_espnow();
    start_task_influxdb();
}

void loop() {}

void init_registers(void) {
    all_outputs_off(dataPin1, clockPin1, latchPin1);
    all_outputs_off(dataPin2, clockPin2, latchPin2);
}

/*
void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }

  Serial.print("\nIP Address: ");
  Serial.print(WiFi.localIP());
  vTaskDelay(1000);
  sync_rtc_ntp();
  vTaskDelay(1000);
}*/
