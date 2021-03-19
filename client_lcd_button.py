#!/usr/bin/python3

import socket
import time
import sys
from PyQt5.QtWidgets import (QWidget, QMainWindow, QGridLayout, QPushButton, QApplication, QLineEdit)

HOST = '192.168.86.213'   # The remote host
PORT = 50007              # The same port as used by the server

sock=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

class Client_lcd_button(QMainWindow):
    
    def __init__(self):
        super().__init__()
        
        self.initUI()
        
        
    def initUI(self):      

        self.widget = QWidget()
        self.setCentralWidget(self.widget)

        redbtn = QPushButton("Red", self)
        greenbtn = QPushButton("Green", self)
        bluebtn = QPushButton("Blue", self)
        yellowbtn = QPushButton("Yellow", self)
        cyanbtn = QPushButton("Cyan", self)
        purplebtn = QPushButton("Purple", self)
        whitebtn = QPushButton("White", self)
        blackbtn = QPushButton("Black", self)
        self.qle = QLineEdit(self)
        sendtxtbtn = QPushButton("Sendtxt", self)

        grid = QGridLayout(self.widget)
        grid.setSpacing(10)
        grid.addWidget(redbtn, 0, 0)
        grid.addWidget(greenbtn, 0, 1)
        grid.addWidget(bluebtn, 0, 2)
        grid.addWidget(yellowbtn, 1, 0)
        grid.addWidget(cyanbtn, 1, 1)
        grid.addWidget(purplebtn, 1, 2)
        grid.addWidget(whitebtn, 2, 0)
        grid.addWidget(blackbtn, 2, 1)
        grid.addWidget(self.qle, 3, 0, 3, 2)
        grid.addWidget(sendtxtbtn, 4, 2)

        self.widget.setLayout(grid)

        redbtn.clicked.connect(self.buttonClicked)            
        greenbtn.clicked.connect(self.buttonClicked)
        bluebtn.clicked.connect(self.buttonClicked)   
        yellowbtn.clicked.connect(self.buttonClicked)
        cyanbtn.clicked.connect(self.buttonClicked)   
        purplebtn.clicked.connect(self.buttonClicked)
        whitebtn.clicked.connect(self.buttonClicked)
        blackbtn.clicked.connect(self.buttonClicked)
        self.qle.textChanged[str].connect(self.onChanged)
        sendtxtbtn.clicked.connect(self.buttonClicked)
 
        self.statusBar()
        
        self.setGeometry(300, 300, 290, 200)
        self.setWindowTitle('client lcd button')
        self.show()

    def onChanged(self, text):

        self.qle.setText(text)
        self.update()

    def buttonClicked(self):
      
        sender = self.sender()
        if sender.text() == "Red":
            sock.sendall(b"red")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Green":
            sock.sendall(b"green")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Blue":
            sock.sendall(b"blue")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Yellow":
            sock.sendall(b"yellow")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Cyan":
            sock.sendall(b"cyan")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Purple":
            sock.sendall(b"purple")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "White":
            sock.sendall(b"white")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Black":
            sock.sendall(b"black")
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        elif sender.text() == "Sendtxt":
            sock.sendall(bytearray(self.qle.text().encode('utf-8')))
            data = sock.recv(1024)
            self.statusBar().showMessage(repr(data))
        
if __name__ == '__main__':
    
    app = QApplication(sys.argv)
    ex = Client_lcd_button()
    sys.exit(app.exec_())
