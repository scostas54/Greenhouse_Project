#include <HTTPClient.h>

void HHTP_send_value(String serverName, String apiKeyValue, String location_id, String fans, String RGB, unsigned long pumpInterval, int tempThreshold, 
                     , int humiThreshold, int CO2Threshold, float CO2Sensor, float HumiSensor, float TempSensor) { 
  
  HTTPClient http;
  
  // Your Domain name with URL path or IP address with path
  http.begin(serverName);
  
  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Prepare your HTTP POST request data
  String httpRequestData = "api_key=" + apiKeyValue + "&location_id=" + location_id + "&fans=" + fans + "&RGB=" + RGB + "&pump_interval=" + pumpInterval +
                      + "&temp_threshold=" + tempThreshold + "&evap_threshold=" + humiThreshold + "&CO2_threshold=" + CO2Threshold + "&CO2sensor=" + CO2Sensor +
                      + "&Humisensor=" + HumiSensor + "&Tempsensor=" + String(TempSensor) + "";
  
  // You can comment the httpRequestData variable above
  // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)    
  //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=CO2&module=Modulo_1&shelving=Shelve_1&sector=Sector_1&value=1005.14";

  Serial.print("httpRequestData: ");
  Serial.println(httpRequestData);
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(httpRequestData);     
    
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

}
