#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "riego_1_0_0.h"
#include "wifi_pass.h"

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_WIFI, PASS_WIFI);
  ArduinoOTA.setPort(3232);
  ArduinoOTA.setHostname("ecoflow");
//  ArduinoOTA.setPassword("admin");
  ArduinoOTA.begin();

  delay(300);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(0, INPUT);

  Serial.println("Setup done");
  test();
}

void loop() {

  if (digitalRead(0)==0) {
     Serial.println("Reboot");
     delay(200);
     ESP.restart();
  }
 
  float vin = readVIN();
  

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("VIN: ");
  Serial.println(vin);

  ArduinoOTA.handle();
  delay(100);
}

float readVIN() {
  // VIN reading for solar battery monitoring ///
  int x = analogRead(VIN_SENSOR);

  // manual measurements for calibration:  
  // 12.49V = 3090
  // 5.00V = 1130

  // We assume linear ADC behavior between 5.0V and 12.49 V input, and we take 5V as floor.
  // (3090 - 1130)/(12.49-5.0) = 261.682 per volt

  return 5.0 + ((float)x-1130.0)/261.682;
}

void test() {

  Serial.println("Relay1");
  digitalWrite(RELAY1, HIGH);
  delay(300);
  digitalWrite(RELAY1, LOW);
  delay(300);  
  
  Serial.println("Relay2");
  digitalWrite(RELAY2, HIGH);
  delay(300);
  digitalWrite(RELAY2, LOW);
  delay(300);  
  
  Serial.println("Relay3");
  digitalWrite(RELAY3, HIGH);
  delay(300);
  digitalWrite(RELAY3, LOW);
  delay(300);  
  
  Serial.println("Relay4");
  digitalWrite(RELAY4, HIGH);
  delay(300);
  digitalWrite(RELAY4, LOW);
  delay(300);  
  
  Serial.println("Relay5");
  digitalWrite(RELAY5, HIGH);
  delay(300);
  digitalWrite(RELAY5, LOW);
  delay(300);  

 
  Serial.println("Led1");
  digitalWrite(LED1, HIGH);
  delay(300);
  digitalWrite(LED1, LOW);
  delay(300);  


  Serial.println("Led2");
  digitalWrite(LED2, HIGH);
  delay(300);
  digitalWrite(LED2, LOW);
  delay(300);  

}


