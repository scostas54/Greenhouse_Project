#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <analogWrite.h>

void ghSetLED();
void HandleCliente();
void WifiCheckConnection();
void ConnectWiFi_AP(bool useStaticIP);
void ConnectWiFi_STA();
void InitServer();
void handleNotFound();
void handleRoot();
void ghSetLED();
int R_value();
int G_value();
int B_value();
