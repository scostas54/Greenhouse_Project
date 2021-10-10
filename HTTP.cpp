#include <Arduino.h>
#include <HTTPClient.h>

void HHTP_send_value(String serverName, String apiKeyValue, String location_id, int fans, String RGB, unsigned long pumpInterval, int tempThreshold, 
                     int humiThreshold, int CO2Threshold, float TempInternal, float HumiInternal, int CO2Internal) { 
  
  HTTPClient http;
  
  // Your Domain name with URL path or IP address with path
  http.begin(serverName);
  
  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Prepare your HTTP POST request data
  String httpRequestData = "api_key=" + apiKeyValue + "&location_id=" + location_id + "&fans=" + String(fans) + "&RGB=" + RGB + "&pump_interval=" + String(pumpInterval) +
                      "&temp_threshold=" + String(tempThreshold) + "&humidity_threshold=" + String(humiThreshold) + "&CO2_threshold=" + String(CO2Threshold) +
                      "&temp_internal=" + String(TempInternal) + "&humidity_internal=" + String(HumiInternal) + "&CO2_internal=" + String(CO2Internal) + "";
  
  // You can comment the httpRequestData variable above
  // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)    
  // String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=CO2&module=Modulo_1&shelving=Shelve_1&sector=Sector_1&value=1005.14";

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
