
#include <Arduino.h>

//Initialize Serial Communication with CO2 sensor
void InitCO2(){
  //CO2 sensor connection
  Serial1.begin(9600,SERIAL_8N1,16,17); //for CO2 sensor, 16 is RX and 17 is TX
}

//Funciones para leer las ppm
int readCO2UART() {
  byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  char response[9];
  Serial.println("Sending CO2 request...");  
  Serial1.write(cmd, 9); //request PPM CO2
  
  // clear the buffer
  memset(response, 0, 9);
  int i = 0;
  while (Serial1.available() == 0) {  
       Serial.print("Waiting for response ");
       Serial.print(i);
       Serial.println(" s");
    delay(1000);
    i++;
  }
  if (Serial1.available() > 0) {
    Serial1.readBytes(response, 9);
  
  }
  // print out the response in hexa
  for (int i = 0; i < 9; i++) {
    Serial.print(String(response[i], HEX));
    Serial.print("   ");
  }
  Serial.println("");
  // checksum
  byte check = getCheckSum(response);
  if (response[8] != check) {
    Serial.println("Checksum not OK!");
    Serial.print("Received: ");
    Serial.println(response[8]);
    Serial.print("Should be: ");
    Serial.println(check);
  }
  // ppm
  int ppm_uart = 256 * (int)response[2] + response[3];
  Serial.print("UART CO2 PPM: ");
  Serial.println(ppm_uart);
  // status
  byte status = response[5];
  Serial.print("Status: ");
  Serial.println(status);
  if (status == 0x40) {
    Serial.println("Status OK");
  }

  return ppm_uart;
}

byte getCheckSum(char *packet) {
  byte i;
  unsigned char checksum = 0;
  for (i = 1; i < 8; i++) {
    checksum += packet[i];
  }
  checksum = 0xff - checksum;
  checksum += 1;
  return checksum;
}
