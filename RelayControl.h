#include <Arduino.h>

void relay_init();
int relay_control(float internal_humidity, float internal_temperature, int internal_CO2, unsigned long deactpump_interval, unsigned long actpump_interval, int tempThreshold,
                  int CO2Threshold, int humiThreshold);
void relay_config(byte pin_relay);
void relay_activate(byte pin_relay);
void relay_deactivate(byte pin_relay);
