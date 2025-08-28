#include <ESP32Servo.h>
Servo doorServo;
#define SERVO_PIN 32   // ใช้ GPIO32 บน ESP32

void setup() {
  Serial.begin(9600);
  doorServo.attach(SERVO_PIN);
  doorServo.write(0);   // เริ่มต้นที่ตำแหน่ง "ล็อก"
  pinMode(2,OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'O') {
      // doorServo.write(90);   // เปิด
      Serial.println("Door Opened");
      digitalWrite(2,HIGH);
    } 
    else if (command == 'C') {
      // doorServo.write(0);    // ล็อก
      Serial.println("Door Locked");
      digitalWrite(2,LOW);
    }
  }
}