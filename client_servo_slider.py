#!/usr/bin/python3

import socket
import time
import sys
from PyQt5.QtWidgets import (QWidget, QMainWindow, QHBoxLayout, QStatusBar, QSlider, QApplication)
from PyQt5.QtCore import Qt

HOST = '192.168.86.213'   # The remote host
PORT = 50007              # The same port as used by the server

sock=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

class Client_servo_slider(QMainWindow):
    
    def __init__(self):
        super().__init__()
        
        self.initUI()
        
        
    def initUI(self):      

        self.widget = QWidget()
        self.setCentralWidget(self.widget)

        self.sld = QSlider(Qt.Horizontal, self)
        self.sld.setRange(30, 120)
        self.sld.valueChanged[int].connect(self.changeValue)

        hbox = QHBoxLayout(self.widget)
        hbox.addWidget(self.sld)

        self.widget.setLayout(hbox)
      
        self.statusBar()
        
        self.setGeometry(300, 300, 290, 150)
        self.setWindowTitle('client servo slider')
        self.show()
        
        
    def changeValue(self):

        str_val = str(self.sld.value())      
        sock.sendall(str_val.encode('utf-8'))
        data = sock.recv(1024)
        self.statusBar().showMessage(repr(data))
        
        
if __name__ == '__main__':
    
    app = QApplication(sys.argv)
    ex = Client_servo_slider()
    sys.exit(app.exec_())
