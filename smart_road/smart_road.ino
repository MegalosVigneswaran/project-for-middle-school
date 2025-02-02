#include "Servo.h"
#include <LiquidCrystal.h>

#define pin_rs 9
#define pin_ps 10
#define p_red 6
#define p_green 7
#define r_red 11
#define r_green 12

const int cd = 5000;
// Define LCD pins (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(5, 4, 3 , 2 , 1, 0);

Servo rs;
Servo ps;

void setup() {

    lcd.begin(16,2);

    pinMode(p_red, OUTPUT);
    pinMode(p_green, OUTPUT);
    pinMode(r_red, OUTPUT);
    pinMode(r_green, OUTPUT);

    rs.attach(pin_rs);
    ps.attach(pin_ps);
}

void loop() {

    lcd.setCursor(3,0);
    lcd.print("8AM to 10AM");

    rs.write(0);
    ps.write(90);
    digitalWrite(p_green,LOW);
    digitalWrite(p_red,HIGH);
    digitalWrite(r_green,HIGH);
    digitalWrite(r_red,LOW);
    delay(cd);

    rs.write(90);
    ps.write(0);
    digitalWrite(p_green,HIGH);
    digitalWrite(p_red,LOW);
    digitalWrite(r_green,LOW);
    digitalWrite(r_red,HIGH);
    delay(cd);

    rs.write(180);
    ps.write(90);
    digitalWrite(p_green,LOW);
    digitalWrite(p_red,HIGH);
    digitalWrite(r_green,HIGH);
    digitalWrite(r_red,LOW);
    delay(cd);

    lcd.clear();

    lcd.setCursor(3,0);
    lcd.print("10AM to 4PM");

    rs.write(90);
    ps.write(0);
    digitalWrite(p_green,HIGH);
    digitalWrite(p_red,LOW);
    digitalWrite(r_green,LOW);
    digitalWrite(r_red,HIGH);
    delay(cd);

    rs.write(0);
    ps.write(90);
    digitalWrite(p_green,LOW);
    digitalWrite(p_red,HIGH);
    digitalWrite(r_green,HIGH);
    digitalWrite(r_red,LOW);
    delay(cd);

    rs.write(90);
    ps.write(0);
    digitalWrite(p_green,HIGH);
    digitalWrite(p_red,LOW);
    digitalWrite(r_green,LOW);
    digitalWrite(r_red,HIGH);
    delay(cd);

    rs.write(0);
    ps.write(90);
    digitalWrite(p_green,LOW);
    digitalWrite(p_red,HIGH);
    digitalWrite(r_green,HIGH);
    digitalWrite(r_red,LOW);
    delay(cd);

    lcd.clear();

    lcd.setCursor(3,0);
    lcd.print("4PM to 8PM");

    rs.write(0);
    ps.write(90);
    digitalWrite(p_green,LOW);
    digitalWrite(p_red,HIGH);
    digitalWrite(r_green,HIGH);
    digitalWrite(r_red,LOW);
    delay(cd);

    rs.write(90);
    ps.write(0);
    digitalWrite(p_green,HIGH);
    digitalWrite(p_red,LOW);
    digitalWrite(r_green,LOW);
    digitalWrite(r_red,HIGH);
    delay(cd);

    rs.write(180);
    ps.write(90);
    digitalWrite(p_green,LOW);
    digitalWrite(p_red,HIGH);
    digitalWrite(r_green,HIGH);
    digitalWrite(r_red,LOW);
    delay(cd);

    lcd.clear();

    lcd.setCursor(3,0);
    lcd.print("5PM to 8AM");

    rs.write(90);
    ps.write(0);
    digitalWrite(p_green,HIGH);
    digitalWrite(p_red,LOW);
    digitalWrite(r_green,LOW);
    digitalWrite(r_red,HIGH);
    delay(cd);

    rs.write(0);
    ps.write(90);
    digitalWrite(p_green,LOW);
    digitalWrite(p_red,HIGH);
    digitalWrite(r_green,HIGH);
    digitalWrite(r_red,LOW);
    delay(cd);

    rs.write(90);
    ps.write(0);
    digitalWrite(p_green,HIGH);
    digitalWrite(p_red,LOW);
    digitalWrite(r_green,LOW);
    digitalWrite(r_red,HIGH);
    delay(cd);

    rs.write(0);
    ps.write(90);
    digitalWrite(p_green,LOW);
    digitalWrite(p_red,HIGH);
    digitalWrite(r_green,HIGH);
    digitalWrite(r_red,LOW);
    delay(cd);

    lcd.clear();

}
