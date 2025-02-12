#include "rtc.h"

// RTC object for DS3231 is in globals
//RTC_DS3231 rtc;

void current_time(void) {

    char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    //String formattedTime;

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();

    if (date_time_mutex != NULL) {
        if(xSemaphoreTake(date_time_mutex, ( TickType_t ) 10 ) == pdTRUE) {

            yearStr = String(now.year(), DEC);
            monthStr = (now.month() < 10 ? "0" : "") + String(now.month(), DEC);
            dayStr = (now.day() < 10 ? "0" : "") + String(now.day(), DEC);
            hourStr = (now.hour() < 10 ? "0" : "") + String(now.hour(), DEC);
            minuteStr = (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
            secondStr = (now.second() < 10 ? "0" : "") + String(now.second(), DEC);
            dayOfWeek = daysOfTheWeek[now.dayOfTheWeek()];
            String formattedTime = dayOfWeek + ", " + yearStr + "-" + monthStr + "-" + dayStr + " " + hourStr + ":" + minuteStr + ":" + secondStr;
            Serial.println(formattedTime);
            xSemaphoreGive(date_time_mutex);
        }
    }
}

void sync_rtc_ntp(void) {

    struct tm timeinfo;
    
    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);  // Configure time with NTP server
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println("\n\nESP32 Time synchronized with NTP server.\n\n");
    Serial.print("\nCurrent time: ");
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    Serial.println("\n");

    // Sync the RTC with the NTP time
    rtc.adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));


}
