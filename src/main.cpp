#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <Servo.h>

#include "Private.h"

Servo myservo;
// cable colors SG90 servo:
// brown=GND, red=5V, orange=pulse 

int p;
int i;

void setup() {
  Serial.begin(115200);

	WiFi.persistent(false);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoReconnect(true);
	WiFi.begin(ssid, password);

  ArduinoOTA.setHostname("FishFeeder");
  //ArduinoOTA.setPassword(passwordOTA);
  ArduinoOTA.begin();

  myservo.attach(4);
  p=0;
  delay(5000);
}

void loop() {
  ArduinoOTA.handle();  
  
  if(p==0) p=15;

  i = map(p, 1, 14, 750, 2600); 
  Serial.printf("loch=%d, pos=%d\n",p,i);
  myservo.writeMicroseconds(i);   
  delay(10000);
  p--;

}