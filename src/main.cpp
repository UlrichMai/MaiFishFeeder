#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include <Servo.h>

#include "Private.h"

// Webserver on port 80
ESP8266WebServer server(80);

#define SERVO_PIN 4

Servo myservo;
// cable colors SG90 servo:
// brown=GND, red=5V, orange=pulse 

const int FeederPos[] = {2702,2559,2416,2273,2130,1987,1844,1701,1558,1415,1272,1129,986,843,700,0};
int ServoPos = 0; // to be persisted
uint32_t LastServoMove = 1;

void refill() {
  myservo.attach(SERVO_PIN);
  ServoPos = 0;
  int ms = FeederPos[ServoPos];
  myservo.writeMicroseconds(ms); 
  LastServoMove = millis();
}
void feed() {
  if (FeederPos[ServoPos+1] ==0) {
    return;
  }

  myservo.attach(SERVO_PIN);
  ServoPos++;
  int ms = FeederPos[ServoPos];
  myservo.writeMicroseconds(ms);
  LastServoMove = millis();
}

void setup() {
  Serial.begin(115200);
  Serial.printf("setup...\n");

	WiFi.persistent(false);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoReconnect(true);
	WiFi.begin(ssid, password);
  Serial.printf("wifi...\n");

  ArduinoOTA.setHostname("FishFeeder");
  //ArduinoOTA.setPassword(passwordOTA);
  ArduinoOTA.begin();
  Serial.printf("OTA...\n");

  // Webserver
  server.on("/", []() {
    server.send(200, "text/html", "<html><body> <style>body{font-size:300%;}</style> <h3>Fish Feeder</h3> <p><a href='/feed'>feed</a></p> <p><a href='/refill'>refill</a></p> <p></p></body></html>");
  });
  server.on("/refill", []() {
    refill();
    server.sendHeader("Location", "/",true); 
    server.send(302, "text/plain","ok");  
    server.client().stop();  
  });
  server.on("/feed", []() {
    feed();
    server.sendHeader("Location", "/",true); 
    server.send(302, "text/plain","ok");  
    server.client().stop();  
  });
  server.on("/set", []() {
    if (server.args()>=1) {
      if (server.argName(0).equals("ms")) {
        myservo.writeMicroseconds(server.arg(0).toInt());
      }
    }
    server.sendHeader("Location", "/",true); 
    server.send(302, "text/plain","ok");  
    server.client().stop();  
  });

  server.onNotFound( []() {
    server.send(404, "text/plain", "not found");
  });
  server.begin(); 
  Serial.printf("Webserver...\n");
  
  // Servo
  myservo.attach(SERVO_PIN);
  Serial.printf("servo...\n");
}

void loop() {
  ArduinoOTA.handle();  
  server.handleClient();
  
  //shut off servo after 5s to stop shaking
  if (LastServoMove!=0 && LastServoMove+5000 < millis()) {
    myservo.detach();
    LastServoMove=0;
  }
}