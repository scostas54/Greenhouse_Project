#include "time.h"

const char *ssid = "MIWIFI_2G_GA3v";
const char *password = "reycostas69";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 46800; // When you extract just the hour it is delayed 12h, I dont know why
const int   daylightOffset_sec = 3600;

void time_setup() {  
  //check WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print("Wifi not connected for time");
  }
  Serial.println("Set up time request");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

int current_hour() {
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  int my_hours = timeinfo->tm_hour;  
  return my_hours; // the current hours is returned as a integer
}
