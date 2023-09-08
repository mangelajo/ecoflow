#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "RTClib.h"
#include <SPI.h>

#include "riego_1_0_0.h"
#include "wifi_pass.h"

RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_WIFI, PASS_WIFI);
  ArduinoOTA.setPort(3232);
  ArduinoOTA.setHostname("ecoflow");
//  ArduinoOTA.setPassword("admin");
  ArduinoOTA.begin();

   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

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
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


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

 DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();


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


