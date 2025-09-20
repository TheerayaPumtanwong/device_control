# import sys
# import serial
# from PyQt5.QtWidgets import (
#     QApplication, QWidget, QVBoxLayout, QLabel, QFrame
# )
# from PyQt5.QtGui import QFont, QColor, QPalette
# from PyQt5.QtCore import Qt


# ser = serial.Serial('COM3', 9600, timeout=1)

# class SensorDisplay(QWidget):
#     def __init__(self):
#         super().__init__()
#         self.setWindowTitle("Test")
#         self.setFixedSize(600, 600)
#         self.setStyleSheet("background-color: #f0f4f8;")

#         # Layout หลัก
#         layout = QVBoxLayout()
#         layout.setContentsMargins(50, 50, 50, 50)
#         layout.setSpacing(30)

#         # หัวข้อ
#         self.title = QLabel("Test")
#         self.title.setFont(QFont("Arial", 24, QFont.Bold))
#         self.title.setAlignment(Qt.AlignCenter)
#         self.title.setStyleSheet("color: #333;")

#         # กรอบแสดงข้อมูล
#         self.data_frame = QFrame()
#         self.data_frame.setStyleSheet("""
#             QFrame {
#                 background-color: white;
#                 border-radius: 20px;
#                 padding: 30px;
#                 border: 2px solid #ccc;
#             }
#         """)
#         frame_layout = QVBoxLayout()
        
#         # ข้อมูล1
#         self.data_label = QLabel("15")
#         self.data_label.setFont(QFont("Arial", 20))
#         self.data_label.setAlignment(Qt.AlignCenter)

#         # ข้อมูล2
#         self.data1_label = QLabel("30")
#         self.data1_label.setFont(QFont("Arial", 20))
#         self.data1_label.setAlignment(Qt.AlignCenter)
        
#          # ข้อมูล3
#         self.data2_label = QLabel("60")
#         self.data2_label.setFont(QFont("Arial", 20))
#         self.data2_label.setAlignment(Qt.AlignCenter)
        
#          # ข้อมูล4
#         self.data3_label = QLabel("90")
#         self.data3_label.setFont(QFont("Arial", 20))
#         self.data3_label.setAlignment(Qt.AlignCenter)
        
#          # ข้อมูล5
#         self.data4_label = QLabel("115")
#         self.data4_label.setFont(QFont("Arial", 20))
#         self.data4_label.setAlignment(Qt.AlignCenter)
        
#          # ข้อมูล6
#         self.data5_label = QLabel("135")
#         self.data5_label.setFont(QFont("Arial", 20))
#         self.data5_label.setAlignment(Qt.AlignCenter)
        
#          # ข้อมูล7
#         self.data6_label = QLabel("160")
#         self.data6_label.setFont(QFont("Arial", 20))
#         self.data6_label.setAlignment(Qt.AlignCenter)
        
#          # ข้อมูล8
#         self.data7_label = QLabel("STOP")
#         self.data7_label.setFont(QFont("Arial", 20))
#         self.data7_label.setAlignment(Qt.AlignCenter)

#         frame_layout.addWidget(self.data_label)
#         frame_layout.addWidget(self.data1_label)
#         frame_layout.addWidget(self.data2_label)
#         frame_layout.addWidget(self.data3_label)
#         frame_layout.addWidget(self.data4_label)
#         frame_layout.addWidget(self.data5_label)
#         frame_layout.addWidget(self.data6_label)
#         frame_layout.addWidget(self.data7_label)
        
#         self.data_frame.setLayout(frame_layout)

#         layout.addWidget(self.title)
#         layout.addWidget(self.data_frame)
#         self.setLayout(layout)

       

#     def read_serial(self):
#         try:
#             if ser.in_waiting:
#                 line = ser.readline().decode().strip()
#                 if "Temp:" in line and "Hum:" in line:
#                     temp = line.split("Temp:")[1].split(";")[0]
#                     hum = line.split("Hum:")[1]
#                     self.data_label.setText(f"15")
#                     self.data1_label.setText(f"30")
#         except Exception as e:
#             self.data_label.setText("Error reading data")
#             self.data1_label.setText(str(e))


# # เริ่มต้นโปรแกรม
# if __name__ == '__main__':
#     app = QApplication(sys.argv)
#     window = SensorDisplay()
#     window.show()
#     sys.exit(app.exec_())


# import sys
# import serial

# from  PyQt5.QtWidgets import QApplication,QWidget,QPushButton,QVBoxLayout,QMessageBox

# try :
#   arduino = serial.Serial('COM3', 9600, timeout=1) #เปลี่ยน COM3 เป็นพอร์ตที่ Arduino เชื่อมต่อ
# except Exception as e:
#   arduino = None
#   print("เชื่อต่อไม่ได้: ",e)

# class AruinoControl(QWidget):
#     def __init__(self):
#       super().__init__()
#       self.setWindowTitle("Aruino Controller") #ชื่อโปรแกรมที่กำหนด
#       self.setGeometry(600,600,400,100) #ขนาด

#       layout = QVBoxLayout()
#       self.btn_15 = QPushButton("Sovereignty 15")
#       self.btn_15.clicked.connect(lambda:self.send_command("15"))
#       layout.addWidget(self.btn_15)

#       self.btn_30 = QPushButton("Sovereignty 30")
#       self.btn_30.clicked.connect(lambda:self.send_command("30"))
#       layout.addWidget(self.btn_30)

#       self.btn_60 = QPushButton("Sovereignty 60")
#       self.btn_60.clicked.connect(lambda:self.send_command("60"))
#       layout.addWidget(self.btn_60)

#       self.btn_90 = QPushButton("Sovereignty 90")
#       self.btn_90.clicked.connect(lambda:self.send_command("90"))
#       layout.addWidget(self.btn_90)

#       self.btn_115 = QPushButton("Sovereignty 115")
#       self.btn_115.clicked.connect(lambda:self.send_command("115"))
#       layout.addWidget(self.btn_115)

#       self.btn_135 = QPushButton("Sovereignty 135")
#       self.btn_135.clicked.connect(lambda:self.send_command("135"))
#       layout.addWidget(self.btn_135)

#       self.btn_160 = QPushButton("Sovereignty 160")
#       self.btn_160.clicked.connect(lambda:self.send_command("160"))
#       layout.addWidget(self.btn_160)

#       self.btn_Stop = QPushButton("Sovereignty Stop")
#       self.btn_Stop.clicked.connect(lambda:self.send_command("Stop"))
#       layout.addWidget(self.btn_Stop)

#       self.setLayout(layout)

#     def send_command(self, command):
#       if(arduino):
#         arduino.write((command+'\n').encode())
#       else:
#         QMessageBox.critical(self, "Error","ไม่พบการเชื่อมต่อ Arduino")
# if __name__ == "__main__":
#   app = QApplication(sys.argv)
#   window = AruinoControl()
#   window.show()
#   sys.exit(app.exec_())


import sys  # ใช้สำหรับจัดการระบบ เช่น การออกจากโปรแกรม (sys.exit) และรับ argument (sys.argv)
import serial  # ใช้สำหรับสื่อสารกับ Arduino ผ่านพอร์ต Serial (ต้องติดตั้ง pyserial ก่อน)

# นำเข้าโมดูลที่ใช้สร้าง GUI จาก PyQt5
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QMessageBox

# พยายามเชื่อมต่อกับ Arduino ผ่านพอร์ต COM3 ที่ Baud Rate = 9600
try:
    arduino = serial.Serial('COM3', 9600, timeout=1)  # กำหนดพอร์ตเป็น COM3, Baud rate = 9600, timeout = 1 วินาที
except Exception as e:
    arduino = None  # ถ้าเชื่อมต่อไม่ได้ ให้กำหนดค่า arduino เป็น None
    print("เชื่อต่อไม่ได้: ", e)  # แสดงข้อความข้อผิดพลาดใน Console

# สร้างคลาสสำหรับ GUI โดยสืบทอดจาก QWidget
class AruinoControl(QWidget):
    def __init__(self):
        super().__init__()  # เรียกคอนสตรัคเตอร์ของ QWidget
        self.setWindowTitle("Aruino Controller")  # ตั้งชื่อหน้าต่างโปรแกรม
        self.setGeometry(600, 600, 400, 100)  # กำหนดตำแหน่งและขนาดของหน้าต่าง (x, y, width, height)

        layout = QVBoxLayout()  # สร้าง Layout แบบแนวตั้ง (ปุ่มจะเรียงจากบนลงล่าง)

        # สร้างปุ่ม Sovereignty 15 และเชื่อมกับฟังก์ชัน send_command โดยส่งค่า "15"
        self.btn_15 = QPushButton("Sovereignty 15")  # สร้างปุ่มชื่อ Sovereignty 15
        self.btn_15.clicked.connect(lambda: self.send_command("15"))  # เมื่อคลิกให้ส่งค่า "15" ไปที่ฟังก์ชัน
        layout.addWidget(self.btn_15)  # เพิ่มปุ่มลงใน Layout

        # ปุ่ม Sovereignty 30
        self.btn_30 = QPushButton("Sovereignty 30")
        self.btn_30.clicked.connect(lambda: self.send_command("30"))
        layout.addWidget(self.btn_30)

        # ปุ่ม Sovereignty 60
        self.btn_60 = QPushButton("Sovereignty 60")
        self.btn_60.clicked.connect(lambda: self.send_command("60"))
        layout.addWidget(self.btn_60)

        # ปุ่ม Sovereignty 90
        self.btn_90 = QPushButton("Sovereignty 90")
        self.btn_90.clicked.connect(lambda: self.send_command("90"))
        layout.addWidget(self.btn_90)

        # ปุ่ม Sovereignty 115
        self.btn_115 = QPushButton("Sovereignty 115")
        self.btn_115.clicked.connect(lambda: self.send_command("115"))
        layout.addWidget(self.btn_115)

        # ปุ่ม Sovereignty 135
        self.btn_135 = QPushButton("Sovereignty 135")
        self.btn_135.clicked.connect(lambda: self.send_command("135"))
        layout.addWidget(self.btn_135)

        # ปุ่ม Sovereignty 160
        self.btn_160 = QPushButton("Sovereignty 160")
        self.btn_160.clicked.connect(lambda: self.send_command("160"))
        layout.addWidget(self.btn_160)

        # ปุ่ม Stop
        self.btn_Stop = QPushButton("Sovereignty Stop")
        self.btn_Stop.clicked.connect(lambda: self.send_command("Stop"))
        layout.addWidget(self.btn_Stop)

        # กำหนด Layout ให้กับหน้าต่างหลัก
        self.setLayout(layout)

    # ฟังก์ชันสำหรับส่งคำสั่งไปยัง Arduino
    def send_command(self, command):
        if arduino:  # ถ้ามีการเชื่อมต่อ Arduino
            arduino.write((command + '\n').encode())  # ส่งคำสั่งพร้อม newline ไปยัง Arduino (แปลงเป็น bytes)
        else:
            QMessageBox.critical(self, "Error", "ไม่พบการเชื่อมต่อ Arduino")  # ถ้าไม่มีการเชื่อมต่อ ให้แสดงกล่องข้อความ Error

# ส่วนของโปรแกรมหลัก
if __name__ == "__main__":
    app = QApplication(sys.argv)  # สร้างแอปพลิเคชัน PyQt
    window = AruinoControl()  # สร้างหน้าต่างหลัก
    window.show()  # แสดงหน้าต่าง
    sys.exit(app.exec_())  # เริ่ม loop ของแอปพลิเคชัน และปิดเมื่อผู้ใช้กดปิดโปรแกรม
