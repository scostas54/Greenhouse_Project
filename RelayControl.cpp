#include <Arduino.h>

byte RELAY_humid = 19; // pin relay controls Humidity 
byte RELAY_fans = 18;  // pin relay controls fans
byte RELAY_pump = 21;  // pin relay controls pump

byte s = 0; //to alternate pump switch

unsigned long previousMillis_1 = 0;
unsigned long deactpump_interval =60000;
unsigned long actpump_interval = 73000;

void relay_config(byte pin_relay){
  pinMode(pin_relay, OUTPUT);
  digitalWrite(pin_relay, HIGH);
} 

void relay_activate(byte pin_relay){  
  digitalWrite(pin_relay, LOW);
}

void relay_deactivate(byte pin_relay){  
  digitalWrite(pin_relay, HIGH);
}; 

void relay_init(){
  relay_config(RELAY_humid);
  relay_config(RELAY_fans);
  relay_config(RELAY_pump);
}

void relay_control(float humidity, float temperature, int ppm_CO2_interior){
  if(ppm_CO2_interior < 500 || temperature > 35){
    relay_activate(RELAY_fans);
  }
  else{
    relay_deactivate(RELAY_fans);
  }
    
  if(humidity < 60){
      relay_activate(RELAY_humid);
    }
  else{
    relay_deactivate(RELAY_humid);
  } 
    
  //pump control every interval activated
  if((millis() - previousMillis_1 >= deactpump_interval) && (s == 0)){
      relay_activate(RELAY_pump);
      s = 1;    
  }
  else if(millis() - previousMillis_1 >= actpump_interval){
     relay_deactivate(RELAY_pump);
     previousMillis_1 = millis();
     s = 0;  
  }
}
