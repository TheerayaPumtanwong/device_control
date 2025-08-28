#include <ESP32Servo.h>

Servo myservo;
char user_input;

void setup() {
  Serial.begin(9600);
  myservo.attach(22);
  Serial.println("Enter angle: 0, 90, 180, 30 or 120");
}

void loop() {
  if (Serial.available() > 0) {
    user_input = Serial.read();

    if (user_input == '0') {
      Serial.println("Servo Motor => 0");
      myservo.write(0);
    } 
    else if (user_input == '1') { 
      Serial.println("Servo Motor => 90");
      myservo.write(90);
    } 
    else if (user_input == '2') { 
      Serial.println("Servo Motor => 180");
      myservo.write(180);
    }else if (user_input == '3') { 
      Serial.println("Servo Motor => 30");
      myservo.write(30);
    }else if (user_input == '4') { 
      Serial.println("Servo Motor => 120");
      myservo.write(120);
    }
    delay(1000);
  }
}


//01
import sys
import serial

from  PyQt5.QtWidgets import QApplication,QWidget,QPushButton,QVBoxLayout,QMessageBox

try :
  arduino = serial.Serial('COM3', 9600, timeout=1) #เปลี่ยน COM3 เป็นพอร์ตที่ Arduino เชื่อมต่อ
except Exception as e:
  arduino = None
  print("เชื่อต่อไม่ได้: ",e)

class AruinoControl(QWidget):
    def __init__(self):
      super().__init__()
      self.setWindowTitle("Aruino Controller") #ชื่อโปรแกรมที่กำหนด
      self.setGeometry(600,600,400,100) #ขนาด

      layout = QVBoxLayout()
      self.btn_15 = QPushButton("Sovereignty 15")
      self.btn_15.clicked.connect(lambda:self.send_command("15"))
      layout.addWidget(self.btn_15)

      self.btn_30 = QPushButton("Sovereignty 30")
      self.btn_30.clicked.connect(lambda:self.send_command("30"))
      layout.addWidget(self.btn_30)

      self.btn_60 = QPushButton("Sovereignty 60")
      self.btn_60.clicked.connect(lambda:self.send_command("60"))
      layout.addWidget(self.btn_60)

      self.btn_90 = QPushButton("Sovereignty 90")
      self.btn_90.clicked.connect(lambda:self.send_command("90"))
      layout.addWidget(self.btn_90)

      self.btn_115 = QPushButton("Sovereignty 115")
      self.btn_115.clicked.connect(lambda:self.send_command("115"))
      layout.addWidget(self.btn_115)

      self.btn_135 = QPushButton("Sovereignty 135")
      self.btn_135.clicked.connect(lambda:self.send_command("135"))
      layout.addWidget(self.btn_135)

      self.btn_160 = QPushButton("Sovereignty 160")
      self.btn_160.clicked.connect(lambda:self.send_command("160"))
      layout.addWidget(self.btn_160)

      self.btn_Stop = QPushButton("Sovereignty Stop")
      self.btn_Stop.clicked.connect(lambda:self.send_command("Stop"))
      layout.addWidget(self.btn_Stop)

      self.setLayout(layout)

    def send_command(self, command):
      if(arduino):
        arduino.write((command+'\n').encode())
      else:
        QMessageBox.critical(self, "Error","ไม่พบการเชื่อมต่อ Arduino")
if __name__ == "__main__":
  app = QApplication(sys.argv)
  window = AruinoControl()
  window.show()
  sys.exit(app.exec_())


//arduino
#include <ESP32Servo.h>
Servo myservo;
String command;          // เก็บคำสั่งล่าสุด
unsigned long previousMillis = 0; //เก็บเวลาที่พึ่งกระพิบไฟ 
const long interval = 400; // 0.4 วินาที เก็บเวลาเอาไว้กระพิบ
bool ledState = LOW;       // สถานะไฟ

void setup() {
  Serial.begin(9600);
  myservo.attach(22);
  pinMode(2, OUTPUT);
}

void loop() {
  // อ่าน Serial
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

    // คำสั่งปรับมุม
    if (command == "15" || command == "30" || command == "45" || 
        command == "60" || command == "90") {
      myservo.write(command.toInt());

    } else if (command == "115" || command == "135" || command == "160") {
      myservo.write(command.toInt());
      digitalWrite(2, HIGH);   // ไฟติดค้าง

    } else if (command == "Stop") {
      myservo.write(0);
      digitalWrite(2, LOW);    // ไฟดับ
    }
  }

  // จัดการไฟกระพริบ (สำหรับคำสั่ง 15–90)
  if (command == "15" || command == "30" || command == "45" || 
      command == "60" || command == "90") {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;              // สลับสถานะ
      digitalWrite(2, ledState);
    }
  }
}
การทำงานของโค้ด


### 1. ส่วนประกาศตัวแปร
#include <ESP32Servo.h>
Servo myservo;
String command;                 // เก็บคำสั่งล่าสุดจาก Serial
unsigned long previousMillis = 0; // เก็บค่าเวลาล่าสุดที่ใช้เช็คไฟกระพริบ
const long interval = 400;        // 0.4 วินาที ใช้เป็นรอบเวลาในการกระพริบ
bool ledState = LOW;              // สถานะไฟปัจจุบัน (ดับเป็นค่าเริ่มต้น)

```
ESP32Servo.h` : ไลบรารีควบคุมเซอร์โวมอเตอร์บน ESP32
Servo myservo;` : สร้างออบเจ็กต์เซอร์โวเพื่อควบคุม
command : เก็บข้อความที่อ่านมาจาก Serial (คำสั่งจากผู้ใช้)
previousMillis` & `interval` : ใช้สำหรับการทำให้ LED กระพริบแบบ **non-blocking** (ไม่ใช้ `delay()`)
ledState : สถานะ ON/OFF ของ LED

---

### 2. setup()

void setup() {
  Serial.begin(9600);    // เปิด Serial monitor ที่ baud rate 9600
  myservo.attach(22);    // ต่อเซอร์โวเข้าที่ขา 22
  pinMode(2, OUTPUT);    // กำหนดขา 2 เป็น OUTPUT สำหรับควบคุม LED
}
```

* เริ่ม Serial monitor
* เซอร์โวเชื่อมที่ขา GPIO22
* LED เชื่อมที่ขา GPIO2

---

### 3. loop() - ส่วนรับคำสั่งจาก Serial

if (Serial.available()) {
  command = Serial.readStringUntil('\n'); // อ่านจนเจอ newline
  command.trim(); // ตัดช่องว่างหรือ \r \n ออก
```

* เช็คว่ามีข้อมูลเข้ามาทาง Serial หรือไม่
* อ่านข้อมูลเป็น `String` จนเจอ **Enter (newline)**
* ลบช่องว่างส่วนเกิน

---

#### 3.1 คำสั่งปรับมุม 15–90 องศา

```cpp
if (command == "15" || command == "30" || command == "45" || 
    command == "60" || command == "90") {
  myservo.write(command.toInt());
}
```
* ถ้าคำสั่งเป็นตัวเลข 15, 30, 45, 60, 90 → หมุนเซอร์โวไปที่มุมนั้น
* LED จะไม่ติดค้าง แต่ไปทำงานในโหมด "กระพริบ" (จัดการด้านล่าง)

---

#### 3.2 คำสั่งปรับมุม 115–160 องศา

```cpp
else if (command == "115" || command == "135" || command == "160") {
  myservo.write(command.toInt());
  digitalWrite(2, HIGH);   // ไฟ LED ติดค้าง
}
```

* ถ้าเป็น 115, 135 หรือ 160 → หมุนเซอร์โว และทำให้ LED **ติดค้าง (ไม่กระพริบ)**

---

#### 3.3 คำสั่ง Stop

```cpp
else if (command == "Stop") {
  myservo.write(0);
  digitalWrite(2, LOW);    // ไฟดับ
}
```

* คำสั่ง `"Stop"` → เซอร์โวกลับไปที่มุม 0° และ LED ดับ

---

### 4. ส่วนควบคุมไฟกระพริบ (เฉพาะมุม 15–90)

```cpp
if (command == "15" || command == "30" || command == "45" || 
    command == "60" || command == "90") {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;              // สลับสถานะ ON <-> OFF
    digitalWrite(2, ledState);
  }
}
```

* เมื่อคำสั่งล่าสุดคือ 15–90 → จะเข้าสู่โหมดกระพริบไฟ
* ใช้ `millis()` แทน `delay()` เพื่อไม่ให้โปรแกรมหยุดทำงาน
* ทุกๆ 400ms → เปลี่ยนสถานะ LED
* ผลลัพธ์: **ไฟกระพริบขณะที่เซอร์โวอยู่ที่มุม 15–90**

---

## ✅ สรุปการทำงานโดยรวม

1. ผู้ใช้พิมพ์คำสั่งผ่าน **Serial Monitor**
2. ESP32 อ่านค่าแล้วเลือกทำงาน:

   * `"15–90"` → เซอร์โวหมุน และ LED กระพริบ
   * `"115–160"` → เซอร์โวหมุน และ LED ติดค้าง
   * `"Stop"` → เซอร์โวกลับ 0° และ LED ดับ

---

## 🔦 ตัวอย่างการใช้งาน

* พิมพ์ `45` → เซอร์โวหมุนไปที่ 45° และ LED บน GPIO2 กระพริบ
* พิมพ์ `135` → เซอร์โวหมุนไปที่ 135° และ LED ติดค้าง
* พิมพ์ `Stop` → เซอร์โวหมุนกลับไป 0° และ LED ดับ






//23
import sys
import serial

from PyQt5.QtWidgets import QApplication, QWidget,QPushButton,QVBoxLayout,QMessageBox, QLabel
from PyQt5.QtGui import QFont, QColor, QPalette
from PyQt5.QtCore import Qt, QTimer


#เชื่อมต่อบอร์ดและพอร์ตคอมใช้พอร์ตอะไรแก้ให้ถูก
try :
  arduino = serial.Serial('COM3',9600,timeout=1)
except Exception as e:
  arduino = None
  print("เชื่อมต่อมไม่ได้ :",e)

#สร้างGUI
class GUI(QWidget):
    def __init__(self):
      super().__init__()
      self.setWindowTitle("Arduino Control") #ชื่อโปรแกรม
      self.setGeometry(800,800,500,300) #ขนาด

      layout = QVBoxLayout()
      #--Button เปิด -----

      self.btn_on = QPushButton("15") #ปุ่มแสดงว่าเป็นปุ่มที่ส่งค่า15
      self.btn_on.clicked.connect(lambda:self.send_command("15")) #เมื่อคลิกปุ่มนี้จะเชื่อมต่อไปที่บอร์ดและส่งค่า15ไป
      layout.addWidget(self.btn_on) #เพิ่มปุ่มเข้า layout
      

      self.btn_on = QPushButton("30") #ปุ่มแสดงว่าเป็นปุ่มที่ส่งค่า30
      self.btn_on.clicked.connect(lambda:self.send_command("30"))#เมื่อคลิกปุ่มนี้จะเชื่อมต่อไปที่บอร์ดและส่งค่า30ไป
      layout.addWidget(self.btn_on) #เพิ่มปุ่มเข้า layout
     

      self.btn_on = QPushButton("45")#ปุ่มแสดงว่าเป็นปุ่มที่ส่งค่า45
      self.btn_on.clicked.connect(lambda:self.send_command("45"))#เมื่อคลิกปุ่มนี้จะเชื่อมต่อไปที่บอร์ดและส่งค่า45ไป
      layout.addWidget(self.btn_on) #เพิ่มปุ่มเข้า layout
      

      self.btn_on = QPushButton("90")#ปุ่มแสดงว่าเป็นปุ่มที่ส่งค่า90
      self.btn_on.clicked.connect(lambda:self.send_command("90"))#เมื่อคลิกปุ่มนี้จะเชื่อมต่อไปที่บอร์ดและส่งค่า90ไป
      layout.addWidget(self.btn_on) #เพิ่มปุ่มเข้า layout
      
      self.btn_on = QPushButton("125")#ปุ่มแสดงว่าเป็นปุ่มที่ส่งค่า125
      self.btn_on.clicked.connect(lambda:self.send_command("125"))#เมื่อคลิกปุ่มนี้จะเชื่อมต่อไปที่บอร์ดและส่งค่า125ไป
      layout.addWidget(self.btn_on) #เพิ่มปุ่มเข้า layout
     

      self.btn_on = QPushButton("135")#ปุ่มแสดงว่าเป็นปุ่มที่ส่งค่า135
      self.btn_on.clicked.connect(lambda:self.send_command("135"))#เมื่อคลิกปุ่มนี้จะเชื่อมต่อไปที่บอร์ดและส่งค่า135ไป
      layout.addWidget(self.btn_on) #เพิ่มปุ่มเข้า layout
      

      self.btn_on = QPushButton("150")#ปุ่มแสดงว่าเป็นปุ่มที่ส่งค่า150
      self.btn_on.clicked.connect(lambda:self.send_command("150"))#เมื่อคลิกปุ่มนี้จะเชื่อมต่อไปที่บอร์ดและส่งค่า150ไป
      layout.addWidget(self.btn_on) #เพิ่มปุ่มเข้า layout
      



      #--Button ปิด -----
      self.btn_off = QPushButton("STOP")#ปุ่มแสดงว่าเป็นปุ่มที่ส่งค่าหยุด
      self.btn_off.clicked.connect(lambda:self.send_command("OFF"))#เมื่อคลิกปุ่มนี้จะเชื่อมต่อไปที่บอร์ดและส่งคำสั่งไปยัง Arduino เพื่อหยุดการทำงาน (เช่นหยุดหมุนมอเตอร์)
      layout.addWidget(self.btn_off) #เพิ่มปุ่มเข้า layout


      self.setLayout(layout) #กำหนด layout หลักให้หน้าต่าง


    #ฟังก์ชันส่งคำสั่งไปยัง Arduino
    def send_command(self,command):
      if(arduino):
        arduino.write((command + '\n').encode())#แปลง string เป็น byte แล้วส่งไปทาง serial
      else:
        QMessageBox.critical(self,"Error","ไม่พบการเชื่อมต่อ Arduino")


#การสร้าง GUI OUTPUT
#เริ่มต้นโปรแกรมและแสดงหน้าต่าง GUI
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = GUI()
    window.show()
    sys.exit(app.exec_())



//arduino
#include <ESP32Servo.h>        // เรียกใช้ไลบรารีสำหรับควบคุม Servo บน ESP32

Servo myservo;                 // สร้างอ็อบเจกต์ servo ชื่อ myservo
String command;                // สร้างตัวแปร String สำหรับเก็บค่าคำสั่งที่รับมาจาก Serial

void setup() {
  Serial.begin(9600);          // เริ่มต้นการสื่อสาร Serial ที่ baudrate 9600
  myservo.attach(22);          // กำหนดขาควบคุม Servo ใช้ขา GPIO 22
  pinMode(2, OUTPUT);          // กำหนดขา GPIO 2 ให้เป็นเอาต์พุต (ใช้ต่อกับ LED)
}

void loop() {
  if (Serial.available()) {                        // ตรวจสอบว่ามีข้อมูลส่งเข้ามาทาง Serial หรือไม่
    String command = Serial.readStringUntil('\n'); // อ่านข้อมูลจาก Serial จนกว่าจะเจอ '\n' (ขึ้นบรรทัดใหม่)
    command.trim();                                // ตัดช่องว่าง (space/enter) ที่เกินออกไป

    if (command == "15") {                         // ถ้าข้อมูลที่รับมาเป็น "15"
      Serial.println("Servo Motor => 15");         // แสดงข้อความใน Serial Monitor
      myservo.write(15);                           // หมุน Servo ไปที่มุม 15 องศา
      blinkLED();                                  // กระพริบ LED แบบเร็ว
    } 
    else if (command == "30") {                    // ถ้าข้อมูลที่รับมาเป็น "30"
      Serial.println("Servo Motor => 30");
      myservo.write(30);                           // หมุน Servo ไปที่ 30 องศา
      blinkLED();                                  // กระพริบ LED แบบเร็ว
    } 
    else if (command == "45") {                    // ถ้าข้อมูลที่รับมาเป็น "45"
      Serial.println("Servo Motor => 45");
      myservo.write(45);                           // หมุน Servo ไปที่ 45 องศา
      blinkLED();                                  // กระพริบ LED แบบเร็ว
    } 
    else if (command == "90") {                    // ถ้าข้อมูลที่รับมาเป็น "90"
      Serial.println("Servo Motor => 90");
      myservo.write(90);                           // หมุน Servo ไปที่ 90 องศา
      digitalWrite(2, HIGH);                       // เปิด LED ค้างไว้ (ไม่กระพริบ)
    }
    else if (command == "125") {                   // ถ้าข้อมูลที่รับมาเป็น "125"
      Serial.println("Servo Motor => 125");
      myservo.write(125);                          // หมุน Servo ไปที่ 125 องศา
      secLED();                                    // กระพริบ LED ช้า (ทุก 2 วินาที)
    }
    else if (command == "135") {                   // ถ้าข้อมูลที่รับมาเป็น "135"
      Serial.println("Servo Motor => 135");
      myservo.write(135);                          // หมุน Servo ไปที่ 135 องศา
      secLED();                                    // กระพริบ LED ช้า
    }
    else if (command == "150") {                   // ถ้าข้อมูลที่รับมาเป็น "150"
      Serial.println("Servo Motor => 150");
      myservo.write(150);                          // หมุน Servo ไปที่ 150 องศา
      secLED();                                    // กระพริบ LED ช้า
    }
    else if (command == "OFF"){                    // ถ้าข้อมูลที่รับมาเป็น "OFF"
      Serial.println("Servo Motor => 0");
      myservo.write(0);                            // หมุน Servo กลับไปที่ 0 องศา
      digitalWrite(2, LOW);                        // ปิด LED
    }
    delay(1000);                                   // หน่วงเวลา 1 วินาทีเพื่อไม่ให้ loop ทำงานเร็วเกินไป
  }
}


void blinkLED(){                                   // ฟังก์ชันสำหรับทำให้ LED กระพริบเร็ว
  for(int i = 0; i<5; i++){                        // ทำซ้ำ 5 รอบ
    digitalWrite(2, HIGH);                         // เปิด LED
    delay(400);                                    // หน่วงเวลา 0.4 วินาที
    digitalWrite(2, LOW);                          // ปิด LED
    delay(400);                                    // หน่วงเวลา 0.4 วินาที
  }
}

void secLED(){                                     // ฟังก์ชันสำหรับทำให้ LED กระพริบช้า
  for(int i = 0; i<5; i++){                        // ทำซ้ำ 5 รอบ
    digitalWrite(2, HIGH);                         // เปิด LED
    delay(2000);                                   // หน่วงเวลา 2 วินาที
    digitalWrite(2, LOW);                          // ปิด LED
    delay(2000);                                   // หน่วงเวลา 2 วินาที
  }
}




#include <ESP32Servo.h>
Servo myservo;
String command;          // เก็บคำสั่งล่าสุด
unsigned long previousMillis = 0; //เก็บเวลาที่พึ่งกระพิบไฟ 
const long interval = 400; // 0.4 วินาที เก็บเวลาเอาไว้กระพิบ
bool ledState = LOW;       // สถานะไฟ

void setup() {
  Serial.begin(9600);
  myservo.attach(32);
  pinMode(2, OUTPUT);
}

void loop() {
  // อ่าน Serial
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

    // คำสั่งปรับมุม
    if (command == "15" || command == "30" || command == "45" || 
        command == "60" || command == "90") {
      myservo.write(command.toInt());

    } else if (command == "115" || command == "135") {
      myservo.write(command.toInt());
      digitalWrite(2, HIGH);   // ไฟติดค้าง

    } else if (command == "160") {
      myservo.write(command.toInt());
      digitalWrite(2, HIGH);   // ไฟติดค้าง
      delay(3000);
      digitalWrite(2, LOW);   // ไฟติดค้าง

      digitalWrite(2, HIGH);   // ไฟติดค้าง
      delay(3000);
      digitalWrite(2, LOW);   // ไฟติดค้าง

    } else if (command == "Stop") {
      myservo.write(0);
      digitalWrite(2, LOW);    // ไฟดับ
    }
  }

  // จัดการไฟกระพริบ (สำหรับคำสั่ง 15–90)
  if (command == "15" || command == "30" || command == "45" || 
      command == "60" || command == "90") {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;              // สลับสถานะ
      digitalWrite(2, ledState);
    }
  }
}