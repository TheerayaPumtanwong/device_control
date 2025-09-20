#include <ESP32Servo.h>
Servo myservo;
char user_input;

void setup() {
  Serial.begin(9600);
  myservo.attach(22);
  Servo();


}

void loop() {
while(Serial.available() > 0){
  char select_mode = Serial.read();
  user_input = select_mode;
  
  if(user_input != select_mode){
    user_input = select_mode;

  }else{
    user_input = user_input;

  }
}
if(user_input == '0'){
  Serial.println('Servo Motor => 0');
  myservo.write(0);
  delay(1000);
}else if(user_input == '90'){
  Serial.println('Servo Motor => 90');
  myservo.write(90);
  delay(1000);
}else if(user_input == '180'){
  Serial.println('Servo Motor => 180');
  myservo.write(180);
  delay(1000);
}else if(user_input == '30'){
  Serial.println('Servo Motor => 30');
  myservo.write(30);
  delay(1000);
}else if(user_input == '120'){
  Serial.println('Servo Motor => 120');
  myservo.write(120);
  delay(1000);
}else{
  Serial.println('Servo Motor => 0');
  myservo.write(0);
  delay(1000);
}
}