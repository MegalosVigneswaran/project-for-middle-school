#define BLYNK_TEMPLATE_ID "TMPL3y_2OZUjN"
#define BLYNK_TEMPLATE_NAME "Smart irrigation "
#define BLYNK_AUTH_TOKEN "578ZnKQbL05fEL2-jnPMYo_jUco3cGWH"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <ESP32Servo.h>
#include <BlynkSimpleEsp32.h> 

const int f1_min = 50;
const int f1_max = 80;
const int f2_min = 30;
const int f2_max = 70;

#define f1_se 34    // Field 1 soil moisture sensor
#define f2_se 35    // Field 2 soil moisture sensor
#define f1_m 21     // Field 1 water pump
#define f2_m 22     // Field 2 water pump
#define f1_s 23     // Field 1 servo motor
#define f2_s 19     // Field 2 servo motor

char auth[] = BLYNK_AUTH_TOKEN;  // Replace with your Blynk auth token
char ssid[] = "NHSS_LAB";   // Replace with your WiFi credentials
char pass[] = "NHSS1234";

BlynkTimer timer;

bool f1_spray = false;
bool f2_spray = false;

Servo servo1;
Servo servo2;

void sendSensorData()
{

  // Map the analog sensor values to a percentage (0-100) 
  int f1_moi = map(analogRead(f1_se), 0, 4095, 100, 0);
  int f2_moi = map(analogRead(f2_se), 0, 4095, 100, 0);
  
  Serial.println(f1_moi);
  Serial.println(f2_moi);
  Serial.println(".............");
  Blynk.virtualWrite(V0, f1_moi);
  Blynk.virtualWrite(V1, f2_moi);

  if (f1_moi < f1_min) {
    f1_spray = true;
  } else if (f1_moi > f1_max) {
    f1_spray = false;
  }
  if (f2_moi < f2_min) {
    f2_spray = true;
  } else if (f2_moi > f2_max) {
    f2_spray = false;
  }

  Blynk.virtualWrite(V2, f1_spray);
  Blynk.virtualWrite(V3, f2_spray);

  if (f1_spray && f2_spray) {
    Serial.println("field 1 and field 2 motor ");
    digitalWrite(f1_m, HIGH);
    digitalWrite(f2_m, HIGH);
    servo1.write(180);
    servo2.write(180);
    delay(700);
    servo1.write(0);
    servo2.write(0);
    delay(700);
    servo1.write(90);
    servo2.write(90);
    delay(700);
  } else if (f2_spray) {
    Serial.println("Field 2 motor");
    digitalWrite(f2_m, HIGH);
    digitalWrite(f1_m, LOW);
    servo2.write(180);
    delay(700);
    servo2.write(0);
    delay(700);
    servo2.write(90);
    delay(700);
  } else if (f1_spray) {
    Serial.println("Field 1");
    digitalWrite(f1_m, HIGH);
    digitalWrite(f2_m, LOW);
    servo1.write(180);
    delay(700);
    servo1.write(0);
    delay(700);
    servo1.write(90);
    delay(700);
  } else {
    Serial.println("No motor is running");
    digitalWrite(f1_m, LOW);
    digitalWrite(f2_m, LOW);
    delay(1000);
  }

}

void setup()
{
  servo1.attach(f1_s);
  servo2.attach(f2_s);
  servo1.write(90);
  servo2.write(90);
  pinMode(f1_m,OUTPUT);
  pinMode(f2_m,OUTPUT);
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1500L, sendSensorData);
  // Setup switch widget
  Blynk.virtualWrite(V2, f1_spray);
  Blynk.virtualWrite(V3, f2_spray);
  Blynk.syncVirtual(f1_spray);
  Blynk.syncVirtual(f2_spray);

}

void loop()
{
  Blynk.run();
  timer.run();
}