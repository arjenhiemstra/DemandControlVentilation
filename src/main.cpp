#include "main.h"

//Variables
const char* ssid = "DIRK3"; //WIFI SSID
const char* password = "095679706460482465742852"; //WIFI password

void setup() {

  Serial.begin(115200);

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
  statemachine_state_mutex = xSemaphoreCreateMutex();
  valve_control_data_mutex = xSemaphoreCreateMutex();
  fanspeed_mutex = xSemaphoreCreateMutex();
  lock_valve_move_mutex = xSemaphoreCreateMutex();

  settings_state_day_mutex = xSemaphoreCreateMutex();
  settings_state_night_mutex = xSemaphoreCreateMutex();
  settings_state_highco2day_mutex = xSemaphoreCreateMutex();
  settings_state_highco2night_mutex = xSemaphoreCreateMutex();
  settings_state_highrhday_mutex = xSemaphoreCreateMutex();
  settings_state_highrhnight_mutex = xSemaphoreCreateMutex();
  settings_state_cooking_mutex = xSemaphoreCreateMutex();
  settings_state_cyclingday_mutex = xSemaphoreCreateMutex();
  settings_state_cyclingnight_mutex = xSemaphoreCreateMutex();

  float temp[2][8][3];

  sensor_queue = xQueueCreate(1, sizeof(temp));
  sensor_avg_queue = xQueueCreate(1, sizeof(temp));

  // First switch off all outputs which randomly come up at power on
  init_registers();

  // Begin LittleFS
  if (!LittleFS.begin())
  {
    Serial.println("\nAn Error has occurred while mounting LittleFS");
    return;
  }

  setup_wifi();
  sensor_config_data_read();
  valve_settings_config_read();
  startTaskwebcode();
  start_task_valvecontrol();
  start_task_i2c();
  start_task_statemachine();
  start_task_mqtt();
  start_task_influxdb();
  start_task_neopixel();
}

void loop() { }


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
}

void init_registers(void) {
  
  all_outputs_off(dataPin1, clockPin1, latchPin1);
  all_outputs_off(dataPin2, clockPin2, latchPin2);

}
