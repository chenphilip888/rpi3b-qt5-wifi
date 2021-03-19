#!/usr/bin/python3

import socket
import time
import sys
from PyQt5.QtWidgets import (QWidget, QMainWindow, QGridLayout, QLabel, QStatusBar, QSlider, QApplication)
from PyQt5.QtCore import Qt

HOST = '192.168.86.213'   # The remote host
PORT = 50007              # The same port as used by the server

sock=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

class Client_lcd_slider(QMainWindow):
    
    def __init__(self):
        super().__init__()
        
        self.initUI()
        
        
    def initUI(self):      

        self.widget = QWidget()
        self.setCentralWidget(self.widget)

        self.red   = QLabel('R')
        self.red.setStyleSheet("QLabel{color:rgba(225,0,0,255);}")
        self.green = QLabel('G')
        self.green.setStyleSheet("QLabel{color:rgba(0,255,0,255);}")
        self.blue  = QLabel('B')
        self.blue.setStyleSheet("QLabel{color:rgba(0,0,255,255);}")
        self.sldr = QSlider(Qt.Horizontal, self)
        self.sldr.setRange(0, 255)
        self.sldr.valueChanged[int].connect(self.changeValue)
        self.sldg = QSlider(Qt.Horizontal, self)
        self.sldg.setRange(0, 255)
        self.sldg.valueChanged[int].connect(self.changeValue)
        self.sldb = QSlider(Qt.Horizontal, self)
        self.sldb.setRange(0, 255)
        self.sldb.valueChanged[int].connect(self.changeValue)

        grid = QGridLayout(self.widget)
        grid.addWidget(self.sldr, 0, 0)
        grid.addWidget(self.sldg, 1, 0)
        grid.addWidget(self.sldb, 2, 0)
        grid.addWidget(self.red,   0, 1)
        grid.addWidget(self.green, 1, 1)
        grid.addWidget(self.blue,  2, 1)

        self.widget.setLayout(grid)
      
        self.statusBar()
        
        self.setGeometry(300, 300, 290, 150)
        self.setWindowTitle('client lcd slider')
        self.show()
        
        
    def changeValue(self):

        valr = str(self.sldr.value())
        if len(valr) == 1:
            valr = '00' + valr
        elif len(valr) == 2:
            valr = '0' + valr
        valg = str(self.sldg.value())
        if len(valg) == 1:
            valg = '00' + valg 
        elif len(valg) == 2:
            valg = '0' + valg
        valb = str(self.sldb.value())
        if len(valb) == 1:
            valb = '00' + valb 
        elif len(valb) == 2:
            valb = '0' + valb
        val = valr + valg + valb
        sock.sendall(val.encode('utf-8'))
        data = sock.recv(1024)
        self.statusBar().showMessage(repr(data))
        
        
if __name__ == '__main__':
    
    app = QApplication(sys.argv)
    ex = Client_lcd_slider()
    sys.exit(app.exec_())
