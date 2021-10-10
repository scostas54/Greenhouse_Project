#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <analogWrite.h>

void ghSetLED_Day();
void ghSetLED_Dark();
void ghSetLED_Last(int R, int G, int B);
void HandleClient();
void InitServer();
void ConnectWiFi_STA();
void ConnectWiFi_AP(bool useStaticIP);
void WifiCheckConnection();
void handleRoot();
void handleNotFound();
int R_value();
int G_value();
int B_value();
