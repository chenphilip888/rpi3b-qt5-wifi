#include "client_led_button.h"
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
   
Client_led_button::Client_led_button(QWidget *parent)
    : QMainWindow(parent) {

  QWidget* widget = new QWidget(this);

  QPushButton *ledOnBtn = new QPushButton("On", this);
  QPushButton *ledOffBtn = new QPushButton("Off", this);
  
  QGridLayout *grid = new QGridLayout(widget);
  grid->addWidget(ledOnBtn, 0, 0);
  grid->addWidget(ledOffBtn, 0, 1);

  widget->setLayout(grid);
  setCentralWidget(widget);
  statusBar();

  connect(ledOnBtn, &QPushButton::clicked, this, &Client_led_button::ledOn);
  connect(ledOffBtn, &QPushButton::clicked, this, &Client_led_button::ledOff);
  sock = make_socket();
}

void Client_led_button::send_led( const char * led ) {

  int valread;
  char buffer[1024] = {0};
  send(sock , led, strlen(led) , 0 );
  valread = read( sock, buffer, 1024 );
  buffer[valread] = '\0';
  statusBar()->showMessage(buffer);
}

void Client_led_button::ledOn() {
  const char *led = "1";
  send_led( led );
}

void Client_led_button::ledOff() {
  const char *led = "0";
  send_led( led );
} 

int main(int argc, char *argv[]) {
    
  QApplication app(argc, argv);  
    
  Client_led_button window;

  window.resize(300, 200);
  window.setWindowTitle("client led button");
  window.show();

  return app.exec();
}
