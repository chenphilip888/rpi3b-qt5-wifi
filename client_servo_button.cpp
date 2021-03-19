#include "client_servo_button.h"
#include <QGridLayout>
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
   
Client_servo_button::Client_servo_button(QWidget *parent)
    : QMainWindow(parent) {

  QWidget* widget = new QWidget(this);

  QPushButton *servoRightBtn = new QPushButton("Right", this);
  QPushButton *servoLeftBtn = new QPushButton("Left", this);
  QPushButton *servoMiddleBtn = new QPushButton("Middle", this);
  QPushButton *servoStopBtn = new QPushButton("Stop", this);
  
  QGridLayout *grid = new QGridLayout(widget);
  grid->addWidget(servoRightBtn, 0, 2);
  grid->addWidget(servoLeftBtn, 0, 0);
  grid->addWidget(servoMiddleBtn, 0, 1);
  grid->addWidget(servoStopBtn, 1, 0);

  widget->setLayout(grid);
  setCentralWidget(widget);
  statusBar();

  connect(servoRightBtn, &QPushButton::clicked, this, &Client_servo_button::servoRight);
  connect(servoLeftBtn, &QPushButton::clicked, this, &Client_servo_button::servoLeft);
  connect(servoMiddleBtn, &QPushButton::clicked, this, &Client_servo_button::servoMiddle);
  connect(servoStopBtn, &QPushButton::clicked, this, &Client_servo_button::servoStop);
  sock = make_socket();
}

void Client_servo_button::send_servo( const char * servo ) {

  int valread;
  char buffer[1024] = {0};
  send(sock , servo, strlen(servo) , 0 );
  valread = read( sock, buffer, 1024 );
  buffer[valread] = '\0';
  statusBar()->showMessage(buffer);
}

void Client_servo_button::servoRight() {
  const char *servo = "right";
  send_servo( servo );
}

void Client_servo_button::servoLeft() {
  const char *servo = "left";
  send_servo( servo );
} 

void Client_servo_button::servoMiddle() {
  const char *servo = "middle";
  send_servo( servo );
}

void Client_servo_button::servoStop() {
  const char *servo = "stop";
  send_servo( servo );
}

int main(int argc, char *argv[]) {
    
  QApplication app(argc, argv);  
    
  Client_servo_button window;

  window.resize(300, 200);
  window.setWindowTitle("client servo button");
  window.show();

  return app.exec();
}
