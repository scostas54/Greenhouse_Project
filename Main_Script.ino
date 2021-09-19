#include <Arduino.h>
#include <analogWrite.h>
#include <WiFi.h>
#include <WebServer.h>
#include "servidor.h"
#include "CO2_Sensor.h"
#include "HTTP.h"
#include "DHT22.h"
#include "RelayControl.h"

unsigned long startTime = millis();
unsigned long previousMillis = 0;
unsigned long interval = 50000; // interval to register data into Database

// Domain name and URL path where database data can be checked
const char* serverName = "http://192.168.1.204/post-esp-greenhouse-data.php";
// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";
String location_id = "MShS_111";

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  //Wifi connection
  ConnectWiFi_STA();   
  InitServer();
  //CO2 sensor connection
  InitCO2();
  //DHT sensor connection
  DHT22_init();
  // Relays Set Up
  relay_init(); 
}

void loop() {
  unsigned long currentMillis = millis(); 
  //Waits for an HTTP request to set Light values  
  HandleClient();  
  WifiCheckConnection();
  // Reading temperature or humidity takes about 250 milliseconds!
  float h = read_DHT22_humidity();
  float t = read_DHT22_temperature();  
  // Reading CO2 values in ppm
  int ppm_uart = readCO2UART(); 
  //--------------------------------------//
  //Check WiFi connection status to send values through HTTP
  if((WiFi.status()== WL_CONNECTED) && (currentMillis - previousMillis >= interval)){
    Serial.println("------------------------------");
    Serial.print("Time from start: ");
    Serial.print((millis() - startTime) / 1000);
    Serial.println(" s");
    //Send sensors values
    HHTP_send_value(serverName, apiKeyValue, location_id, "CO2", ppm_uart); // add Fans, humidifier, RGB, Pump_On_Off, CO2_ext
    HHTP_send_value(serverName, apiKeyValue, location_id, "Humidity", h);
    HHTP_send_value(serverName, apiKeyValue, location_id, "Temperature", t);
    previousMillis = currentMillis;
  }
  else {
    Serial.println("Interval not reached yet");
    Serial.println("------------------------------");
  }
  //--------------------------------------// 
  relay_control(h,t,ppm_uart); 
}
//Add functionallity to change pump times and also humidity, temperature and CO2 setpoints