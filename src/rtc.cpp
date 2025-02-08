#include "rtc.h"

// RTC object for DS3231
RTC_DS3231 rtc;

void current_time(void) {

    char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    Wire.begin(I2C_SDA1, I2C_SCL1, 100000);
    rtc.begin(&Wire);

    DateTime now = rtc.now();

    // Getting each time field in individual variables
    String yearStr = String(now.year(), DEC);
    String monthStr = (now.month() < 10 ? "0" : "") + String(now.month(), DEC);
    String dayStr = (now.day() < 10 ? "0" : "") + String(now.day(), DEC);
    String hourStr = (now.hour() < 10 ? "0" : "") + String(now.hour(), DEC);
    String minuteStr = (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
    String secondStr = (now.second() < 10 ? "0" : "") + String(now.second(), DEC);
    String dayOfWeek = daysOfTheWeek[now.dayOfTheWeek()];

    // Complete time string
    String formattedTime = dayOfWeek + ", " + yearStr + "-" + monthStr + "-" + dayStr + " " + hourStr + ":" + minuteStr + ":" + secondStr;

    // Print the complete formatted time
    Serial.println(formattedTime);
    Serial.println();
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
    Serial.println("\nESP32 Time synchronized with NTP server.");
    Serial.print("Current time: ");
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    // Sync the RTC with the NTP time
    rtc.adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));


}
