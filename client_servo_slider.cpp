#include "client_servo_slider.h"
#include <QHBoxLayout>
#include <QStatusBar>
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
   
Client_servo_slider::Client_servo_slider(QWidget *parent)
    : QMainWindow(parent) {

  QWidget* widget = new QWidget(this);
  QHBoxLayout *hbox = new QHBoxLayout(widget);

  slider = new QSlider(Qt::Horizontal, this);
  slider->setRange(0, 80);
  hbox->addWidget(slider);

  widget->setLayout(hbox);
  setCentralWidget(widget);
  statusBar();

  connect(slider, &QSlider::valueChanged, this, &Client_servo_slider::send_servo);

  sock = make_socket();
}

void Client_servo_slider::send_servo() {

  int valread;
  char servo[4];
  sprintf(servo, "%d", slider->value());
  char buffer[1024] = {0};
  send(sock , servo, strlen(servo) , 0 );
  valread = read( sock, buffer, 1024 );
  buffer[valread] = '\0';
  statusBar()->showMessage(buffer);
}

int main(int argc, char *argv[]) {
    
  QApplication app(argc, argv);  
    
  Client_servo_slider window;

  window.resize(300, 70);
  window.setWindowTitle("client servo slider");
  window.show();

  return app.exec();
}
