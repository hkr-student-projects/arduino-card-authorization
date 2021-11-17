#include <Servo.h>
int trigPin=8;
int echoPin=10;



Servo servo;
int angle=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  servo.attach(9);
  servo.write(angle);
  delay(2000);
  

}

void loop() {
  long duration,distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=(duration/2)/29.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(10);
  if(distance<=10){
    servo.write(90);
    delay(100);
   
  }
  else if(distance>10){
    servo.write(angle);
  }
//servo.write(90);
//delay(1000);
//servo.write(0);
//delay(1000);
}
