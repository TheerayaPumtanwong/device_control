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

      self.btn_125 = QPushButton("Sovereignty 125")
      self.btn_125.clicked.connect(lambda:self.send_command("125"))
      layout.addWidget(self.btn_125)

      self.btn_145 = QPushButton("Sovereignty 145")
      self.btn_145.clicked.connect(lambda:self.send_command("145"))
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