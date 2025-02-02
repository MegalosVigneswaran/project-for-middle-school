#include "SoftwareSerial.h"
#include <TinyGPS++.h>

#define IN1 26      //D1
#define IN2 27      //D2
#define sen 18      //D3
#define blue_RX 19  //D7
#define blue_TX 21  //D8
#define gps_RX 22   //D6                                                                                                                                                                                                                                     
#define gps_TX 23   //D5

bool isquaked = false;
bool isopened = false;

TinyGPSPlus  gps;

SoftwareSerial bluetooth(blue_RX,blue_TX);
SoftwareSerial gpse(gps_RX,gps_TX);

void setup()               
{
  Serial.begin(9600);
 bluetooth.begin(9600);
 gpse.begin(9600);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(sen,INPUT);  
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);
}

void loop()
{  
checkquake();

}

void checkquake(){

  if(isquaked){

    char rescueme = bluetooth.read();

    if(rescueme == 'o' && !isopened){
      isopened = true;
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      delay(100);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      Serial.println("Opened");
    }else if(rescueme == 'c' && isopened){
      isquaked = false;
      isopened = false;
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      delay(100);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      Serial.println("Closed");
    } 
  }else{

    if(digitalRead(sen) == LOW){

      isquaked = true;

      Serial.println("Quake detected");

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      delay(700);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      delay(4000);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      delay(700);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);

    }
  }
}

void updatedata(){

  while(gpse.available() > 0){
    gps.encode(gpse.read());
  }
}

void addquake(){

}

void removequake(){

}