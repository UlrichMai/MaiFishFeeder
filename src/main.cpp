#include <Arduino.h>
#include <Servo.h>

Servo myservo;
// cable colors SG90 servo:
// brown=GND, red=5V, orange=pulse 

int p;
int i;

void setup() {
  Serial.begin(115200);
  myservo.attach(5);
  p=0;
  delay(5000);
}

void loop() {

  if(p==0) p=15;

  i = map(p, 1, 14, 750, 2600); 
  Serial.printf("loch=%d, pos=%d\n",p,i);
  myservo.writeMicroseconds(i);   
  delay(2000);
  p--;

}