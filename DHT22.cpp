#include <Arduino.h>
#include "DHT.h"

//Pin values and Settings
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
const byte DHTPin = 5;  
DHT dht(DHTPin, DHTTYPE);

void DHT22_init(){
    dht.begin();
}

float read_DHT22_humidity(){
    float humidity = dht.readHumidity();
    if (isnan(humidity)) {
        Serial.println("Failed to read humidity from DHT sensor!");
        delay(1000);        
    }
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %\t");

    return humidity;
}

float read_DHT22_temperature(){
    float temperature = dht.readTemperature();
    if (isnan(temperature)) {
        Serial.println("Failed to read temperature from DHT sensor!");
        delay(1000);       
    }
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C ");
    
    return temperature;
}