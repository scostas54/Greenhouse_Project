void relay_init();
void relay_control(float humidity, float temperature, int ppm_CO2_interior);
void relay_config(byte pin_relay);
void relay_activate(byte pin_relay);
void relay_deactivate(byte pin_relay);