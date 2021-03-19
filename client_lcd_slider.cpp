#include "client_lcd_slider.h"
#include <QGridLayout>
#include <QLabel>
#include <QStatusBar>
#include <QLineEdit>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define HOST "192.168.86.213"
#define PORT 8888

int make_socket()
{
    int sock;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons( PORT );

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, HOST, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    return sock;
}
   
Client_lcd_slider::Client_lcd_slider(QWidget *parent)
    : QMainWindow(parent) {

  QWidget* widget = new QWidget(this);
  QGridLayout *grid = new QGridLayout(widget);
  grid->setSpacing(10);
 
  labelR = new QLabel("R", this);
  labelR->setStyleSheet("QLabel{color:rgba(255, 0, 0, 255);}");
  labelG = new QLabel("G", this);
  labelG->setStyleSheet("QLabel{color:rgba(0, 255, 0, 255);}");
  labelB = new QLabel("B", this); 
  labelB->setStyleSheet("QLabel{color:rgba(0, 0, 255, 255);}");
  sliderR = new QSlider(Qt::Horizontal, this);
  sliderR->setRange(0, 255);
  sliderG = new QSlider(Qt::Horizontal, this);
  sliderG->setRange(0, 255);
  sliderB = new QSlider(Qt::Horizontal, this);
  sliderB->setRange(0, 255);

  grid->addWidget(sliderR, 0, 0);
  grid->addWidget(labelR, 0, 1);
  grid->addWidget(sliderG, 1, 0);
  grid->addWidget(labelG, 1, 1);
  grid->addWidget(sliderB, 2, 0);
  grid->addWidget(labelB, 2, 1);

  widget->setLayout(grid);
  setCentralWidget(widget);  
  statusBar();

  connect(sliderR, &QSlider::valueChanged, this, &Client_lcd_slider::send_lcd);
  connect(sliderG, &QSlider::valueChanged, this, &Client_lcd_slider::send_lcd);
  connect(sliderB, &QSlider::valueChanged, this, &Client_lcd_slider::send_lcd);

  sock = make_socket();
}

void Client_lcd_slider::send_lcd() {
  int valread;
  char buffer[1024] = {0};
  char lcd[10];
  sprintf(lcd, "%03d%03d%03d", sliderR->value(), sliderG->value(), sliderB->value());
  send(sock , lcd, strlen(lcd) , 0 );
  valread = read( sock, buffer, 1024 );
  buffer[valread] = '\0';
  statusBar()->showMessage(buffer);
}

int main(int argc, char *argv[]) {
    
  QApplication app(argc, argv);  
    
  Client_lcd_slider window;

  window.resize(300, 150);
  window.setWindowTitle("client lcd slider");
  window.show();

  return app.exec();
}
