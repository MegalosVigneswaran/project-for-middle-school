/*
Developed by: Vigneswaran
Date: 08-Jan-2025
Description: Ultrasonic sensor-based system for depth and obstacle detection with motor, vibrator, and buzzer control.
*/

#include "Servo.h"

#define echo_depth 2
#define trig_depth 3
#define echo_obs 4
#define trig_obs 5
#define buzzer 7
#define motor_right 8
#define motor_left 9

Servo s;
/* 
Change the following as per your requirement.
உங்கள் தேவைக்கேற்ப பின்வருவனவற்றை மாற்றவும்.
*/
const int obs_range = 65; //Unit (cm)
const int depth_range = 35; //Unit (cm)

void setup() {
  Serial.begin(9600);
  pinMode(trig_depth, OUTPUT);
  pinMode(echo_depth, INPUT);
  pinMode(trig_obs, OUTPUT);
  pinMode(echo_obs, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motor_left,OUTPUT);
  pinMode(motor_right,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  s.attach(10);
  s.write(90);
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.034) / 2;
  return distance;
}

void loop() {
getobs();
}

void getobs(){
  float depth = getDistance(trig_depth, echo_depth);
  delay(50);
  float obstacle = getDistance(trig_obs, echo_obs);
  Serial.print("Depth: ");
  Serial.print(depth);
  Serial.print(" cm | Obstacle: ");
  Serial.print(obstacle);
  Serial.println(" cm");

  if (depth < depth_range && obstacle > 50) {
    Serial.println("there is no interference");
    digitalWrite(motor_right,HIGH);
    digitalWrite(motor_left,HIGH);
    digitalWrite(buzzer, LOW);
  } 
  else {
    if(obstacle < obs_range) {
      digitalWrite(buzzer, HIGH);
      digitalWrite(motor_right,LOW);
      digitalWrite(motor_left,LOW);
 
      s.write(120);
      float left = getDistance(trig_obs, echo_obs);
      Serial.print("left distance ");
      Serial.println(left);
      s.write(60);
      float right = getDistance(trig_obs, echo_obs);
      Serial.print("Right distance ");
      Serial.println(right);

      if(left > right){
        digitalWrite(motor_right,HIGH);
        digitalWrite(motor_left,LOW);
        delay(1000);
        digitalWrite(motor_right,HIGH);
        digitalWrite(motor_left,HIGH);
        delay(3000);
        digitalWrite(motor_right,LOW);
        digitalWrite(motor_left,HIGH);
        delay(1000);
        digitalWrite(motor_right,HIGH);
        digitalWrite(motor_left,HIGH);
      }else{
        digitalWrite(motor_right,LOW);
        digitalWrite(motor_left,HIGH);
        delay(1000);
        digitalWrite(motor_right,HIGH);
        digitalWrite(motor_left,HIGH);
        delay(3000);
        digitalWrite(motor_right,HIGH);
        digitalWrite(motor_left,LOW);
        delay(1000);
        digitalWrite(motor_right,HIGH);
        digitalWrite(motor_left,HIGH);
      }
    } 
    else {
      digitalWrite(buzzer, LOW);
    }
    if (depth > depth_range) {
      digitalWrite(motor_right, LOW);
      digitalWrite(motor_left, LOW);
      digitalWrite(buzzer,HIGH);
      delay(500);
      digitalWrite(buzzer,LOW);
      delay(500);
      digitalWrite(buzzer,HIGH);
      delay(500);
      digitalWrite(buzzer,LOW);
    }
  }
}
