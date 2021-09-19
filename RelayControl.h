void relay_init();
void relay_control(float humidity, float temperature, int ppm_CO2_interior, unsigned long deactpump_interval, unsigned long actpump_interval, int tempThreshold,
                  , int CO2Threshold, int humiThreshold);
void relay_config(byte pin_relay);
void relay_activate(byte pin_relay);
void relay_deactivate(byte pin_relay);
