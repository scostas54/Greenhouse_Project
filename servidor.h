#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <analogWrite.h>

void InitServer();
void ConnectWiFi_STA();
void ConnectWiFi_AP(bool useStaticIP);
void WifiCheckConnection();
void handleRoot();
void handleNotFound();
void HandleCliente();
void ghSetLED_Day();
void ghSetLED_Dark();
void ghSetLED_Last(int R, int G, int B);
int R_value();
int G_value();
int B_value();
