#include <Servo.h>

const int soilMoisturePin = A0;
const int rainSensorPin = 2;
const int motorPin = 4;
const int servoPin = 3;

const int soilMoistureThreshold = 500;
const int rainThreshold = 1;

Servo drainageServo;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(rainSensorPin, INPUT);
  drainageServo.attach(servoPin);
  drainageServo.write(0);
  Serial.begin(115200);
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin);
  int rainSensorValue = digitalRead(rainSensorPin);

  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);
  Serial.print("Rain Sensor: ");
  Serial.println(rainSensorValue);

  if (soilMoistureValue < soilMoistureThreshold && rainSensorPin == 1) {
    digitalWrite(motorPin, HIGH);
    drainageServo.write(0);
  }else if(soilMoistureValue < soilMoistureThreshold && rainSensorPin == 0){
    digitalWrite(motorPin, LOW);
    drainageServo.write(0);
  } else {
    digitalWrite(motorPin, LOW);
    Serial.println("Motor is OFF.");
    drainageServo.write(90);
  }
  delay(1500);
}
