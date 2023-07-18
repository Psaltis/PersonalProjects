#include <ESP32Servo.h>
#include <WiFi.h>
#include "time.h"

const char* ssid     = "COSMOTE-099347";
const char* password = "btt92td48gupmg4u";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7200;
const int   daylightOffset_sec = 3600;
char hour[3];
char minute[3];
char second[3];
bool fedmorn = false;
bool fednoon = false;
int ihour, isecond, iminute;
Servo feeder;
int servo_pin = 18;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
 
  feeder.attach(servo_pin);
  feeder.write(0);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  strftime(hour,3, "%H", &timeinfo);
  strftime(second,3, "%S", &timeinfo);
  strftime(minute,3, "%M", &timeinfo);
  ihour = atoi(hour);
  isecond = atoi(second);
  iminute = atoi(minute);

  if((ihour== 9) && (fedmorn == false)){
    feeder.write(80);
    delay(1000);
    feeder.write(0);
    fedmorn = true;
    }
  if((ihour== 20) && (fednoon == false)){
    feeder.write(80);
    delay(1000);
    feeder.write(0);
    fednoon = true;
    }

  if(ihour== 1){
    fedmorn = false;
    fednoon = false;
    }
}
