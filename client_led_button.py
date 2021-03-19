#!/usr/bin/python3

import socket
import time
import sys
from PyQt5.QtWidgets import (QWidget, QMainWindow, QGridLayout, QPushButton, QApplication)

HOST = '192.168.86.213'   # The remote host
PORT = 50007              # The same port as used by the server

sock=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

class Client_led_button(QMainWindow):
    
    def __init__(self):
        super().__init__()
        
        self.initUI()
        
        
    def initUI(self):      

        self.widget = QWidget()
        self.setCentralWidget(self.widget)

        btn1 = QPushButton("On", self)
        btn2 = QPushButton("Off", self)

        grid = QGridLayout(self.widget)
        grid.setSpacing(10)
        grid.addWidget(btn1, 0, 0)
        grid.addWidget(btn2, 0, 1)

        self.widget.setLayout(grid)
      
        btn1.clicked.connect(self.buttonClicked)            
        btn2.clicked.connect(self.buttonClicked)
        
        self.statusBar()
        
        self.setGeometry(300, 300, 290, 150)
        self.setWindowTitle('client led button')
        self.show()
        
        
    def buttonClicked(self):
      
        sender = self.sender()
        if sender.text() == "On":
            sock.sendall(b"1")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Off":
            sock.sendall(b"0")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        
        
if __name__ == '__main__':
    
    app = QApplication(sys.argv)
    ex = Client_led_button()
    sys.exit(app.exec_())
