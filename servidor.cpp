//https://www.luisllamas.es/como-emplear-el-esp8266-como-servidor/
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <analogWrite.h>
#include "servidor.h"

int rLed = 0;
int gLed = 0;
int bLed = 0;

int rLedPin = 14; 
int gLedPin = 26; 
int bLedPin = 27;

int rLedPin1 = 25; //No 23
int gLedPin1 = 4; //No 35
int bLedPin1 = 2; 

const char *ssid ="MIWIFI_2G_GA3v";
const char *password = "reycostas69";
IPAddress ip(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80); //instanciamos un objeto de la clase Webserver y abrimos el puerto 80 para escuchar comunicaciones HTTP

//ejemplo leds invernadero 192.168.1.200/led?rLed=50&gLed=50&bLed=50
//ejemplo setpoints invernadero 192.168.1.200/setpoints?deactpump_interval=50&actpump_interval=50&tempThreshold=50&CO2Threshold=50&humiThreshold=50  

// Funcion que se ejecutara en la URI '/'
void handleRoot() 
{
   server.send(200, "text/plain", "Lights Server Working Correctly"); //envia respuesta a cliente en caso de funcionar correctamente ==> code = 200
}

void handleNotFound() 
{
   server.send(404, "text/plain", "Not found"); //envia respuesta a cliente en caso de funcionar incorrectamente ==> code = 404
}

void InitServer()
{
  //Lights pins 
   analogWriteResolution(rLedPin, 8);
   analogWriteResolution(gLedPin, 8);
   analogWriteResolution(bLedPin, 8);
   analogWriteResolution(rLedPin1, 8);
   analogWriteResolution(gLedPin1, 8);
   analogWriteResolution(bLedPin1, 8);

   // Ruteo para '/'
   server.on("/", handleRoot);
 
   // Definimos dos routeos, la asociacion entre la URI de la peticion y la accion de callback que se ejecutara. 
   server.on("/led", HTTP_GET, ghSetLED);
   server.on("/led", HTTP_POST, ghSetLED);
   
   //Definimos dos nuevos routeos para fijar los setpoints
   server.on("/setpoints", HTTP_GET, ghSetSetpoints);
   server.on("/setpoints", HTTP_POST, ghSetSetpoints);
 
   server.onNotFound(handleNotFound);
 
   server.begin();
   Serial.println("HTTP server started");
}

void ConnectWiFi_STA()
{
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   WiFi.config(ip, gateway, subnet);
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
  
   Serial.println("");
   Serial.print("Iniciado STA:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());
}

void ConnectWiFi_AP(bool useStaticIP)
{ 
   Serial.println("");
   WiFi.mode(WIFI_AP);
   while(!WiFi.softAP(ssid, password))
   {
     Serial.println(".");
     delay(100);
   }
   if(useStaticIP) WiFi.softAPConfig(ip, gateway, subnet);

   Serial.println("");
   Serial.print("Iniciado AP:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.softAPIP());
}

void WifiCheckConnection(){   
   // if WiFi is down, try reconnecting
   if (WiFi.status() != WL_CONNECTED) {
     Serial.print(millis());
     Serial.println("Reconnecting to WiFi...");
     WiFi.disconnect();
     WiFi.reconnect();
   }
}
// handleClient() se encarga de recibir las peticiones de los clientes y lanzar las funciones de callback asociadas en el ruteo
void HandleClient(){

    server.handleClient();
}

// Funcion al recibir petición /led POST
void ghSetLED() 
{
   // mostrar por puerto serie   
   rLed = server.arg(String("rLed")).toInt();
   gLed = server.arg(String("gLed")).toInt();
   bLed = server.arg(String("bLed")).toInt();
   Serial.println("rLed: " + String(rLed) + "; " + "gLed:" +  String(gLed) + "; " + "bLed: " +  String(bLed));
   //Enviamos valores a los LED
   analogWrite(rLedPin, rLed);
   analogWrite(gLedPin, gLed);
   analogWrite(bLedPin, bLed);

   analogWrite(rLedPin1, rLed);
   analogWrite(gLedPin1, gLed);
   analogWrite(bLedPin1, bLed);

   // devolver respuesta al cliente
   server.send(200, "text/plain", String("PARAMETROS: ") + String("rLed: ") + server.arg(String("rLed")) + String(", gLed: ") + server.arg(String("gLed")) + String(", bLed: ") + server.arg(String("bLed")));
}

// Funcion al recibir petición /setpoints POST
void ghSetSetpoints() 
{

   // devolver respuesta al cliente
   server.send(200, "text/plain", String("PARAMETROS: ") + String("rLed: ") + server.arg(String("rLed")) + String(", gLed: ") + server.arg(String("gLed")) + String(", bLed: ") + server.arg(String("bLed")));
}
