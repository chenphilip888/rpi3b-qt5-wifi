#!/usr/bin/python3

import socket
import time
import sys
from PyQt5.QtWidgets import (QWidget, QMainWindow, QGridLayout, QPushButton, QApplication)

HOST = '192.168.86.213'   # The remote host
PORT = 50007              # The same port as used by the server

sock=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

class Client_servo_button(QMainWindow):
    
    def __init__(self):
        super().__init__()
        
        self.initUI()
        
        
    def initUI(self):      

        self.widget = QWidget()
        self.setCentralWidget(self.widget)

        leftbtn = QPushButton("Left", self)
        middlebtn = QPushButton("Middle", self)
        rightbtn = QPushButton("Right", self)
        stopbtn = QPushButton("Stop", self)

        grid = QGridLayout(self.widget)
        grid.setSpacing(10)
        grid.addWidget(leftbtn, 0, 0)
        grid.addWidget(middlebtn, 0, 1)
        grid.addWidget(rightbtn, 0, 2)
        grid.addWidget(stopbtn, 1, 0)

        self.widget.setLayout(grid)
      
        leftbtn.clicked.connect(self.buttonClicked)            
        middlebtn.clicked.connect(self.buttonClicked)
        rightbtn.clicked.connect(self.buttonClicked)
        stopbtn.clicked.connect(self.buttonClicked)
        
        self.statusBar()
        
        self.setGeometry(300, 300, 290, 200)
        self.setWindowTitle('client servo button')
        self.show()
        
        
    def buttonClicked(self):
      
        sender = self.sender()
        if sender.text() == "Left":
            sock.sendall(b"left")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Middle":
            sock.sendall(b"middle")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Right":
            sock.sendall(b"right")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Stop":
            sock.sendall(b"stop")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        
if __name__ == '__main__':
    
    app = QApplication(sys.argv)
    ex = Client_servo_button()
    sys.exit(app.exec_())
