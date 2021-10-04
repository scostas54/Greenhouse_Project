#include <Arduino.h>
#include <analogWrite.h>
#include <WiFi.h>
#include <WebServer.h>
#include "servidor.h"
#include "CO2_Sensor.h"
#include "HTTP.h"
#include "DHT22.h"
#include "RelayControl.h"
#include "TimeInfo.h"

unsigned long startTime = millis();
unsigned long previousMillis = 0;
unsigned long interval = 50000; //Interval to register data into Database

//Parameter to set up relays (future set up through wifi)
unsigned long deactpump_interval = 60000;
unsigned long actpump_interval = 73000; //Pump activation time is actpump_interval - deactpump_interval
unsigned long pumpInterval = actpump_interval - deactpump_interval;
int tempThreshold = 30; 
int CO2Threshold = 800;
int humiThreshold = 60;

//Parameter to set up day and night cycles (future set up through wifi)
int threshold_hour = 21; 

//Domain name and URL path where database data can be checked
const char* serverName = "http://192.168.1.204/post-esp-greenhouse-data.php";
//Keep this API Key value to be compatible with the PHP code provided in the project page. 
//If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";
String location_id = "MShS_111";

void setup() {
  Serial.begin(115200);
  delay(1000);  
  //Wifi connection
  ConnectWiFi_STA();  
  //Server Starts
  InitServer();
  //CO2 sensor connection
  InitCO2();
  //DHT sensor connection
  DHT22_init();
  //Relays Set Up
  relay_init(); 
  //Time Set Up
  time_setup();  
}

void loop() {
  unsigned long currentMillis = millis();
  int current_hour = current_hour(); //returns the current hour as integer
  
  //The next if has to be on the servidor.cpp file not here
  if ((current_hour <= threshold_hour) && (current_hour >= (threshold_hour-12))){ //12h day cycle and 12h dark cycle
    //Enter this part for day hours so parameters received through HTTP are accepted 
    //Waits for an HTTP request to set Light values  
    HandleClient();      
    //Checks that the Wifi Connections is working, if not --> recconect 
    WifiCheckConnection();
    //Returns the values RGB for the lamp
    int R = R_value();
    int G = G_value();
    int B = B_value();
    String RGB = String(String(R) + "; " +  String(G) + "; " + String(G));
  }
  else {
    //Enter this part for dark hours so parameters are setted to 0
    ghSetLED_Dark()
    String RGB = String(String(0) + "; " +  String(0) + "; " + String(0));
  }    
  //--------------------------------------//
  //Reading temperature or humidity takes about 250 milliseconds!
  float HumiInternal = read_DHT22_humidity();
  float TempInternal = read_DHT22_temperature();  
  // Reading CO2 values in ppm
  int CO2Internal = readCO2UART(); 
  //--------------------------------------//
  //Function to control relays also returns a value of 0 if fans are deactivated and 1 if they are activated
  int fans = relay_control(HumiInternal, TempInternal, CO2Internal, deactpump_interval, actpump_interval, tempThreshold, CO2Threshold, humiThreshold); 
  
  //Check WiFi connection status to send values through HTTP
  if((WiFi.status()== WL_CONNECTED) && (currentMillis - previousMillis >= interval)){
    Serial.println("------------------------------");
    //Send sensors values
    HHTP_send_value(serverName, apiKeyValue, location_id, fans, RGB, pumpInterval, tempThreshold, humiThreshold, CO2Threshold, *WaterPH, CO2Internal, HumiInternal,
                    , TempInternal, *CO2External, *HumiExternal, *TempExternal);
    previousMillis = currentMillis;
  }
  else {
    Serial.println("Interval not reached yet");
    Serial.println("------------------------------");
  }
}
