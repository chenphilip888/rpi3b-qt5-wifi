#include "client_lcd_button.h"
#include <QGridLayout>
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
   
Client_lcd_button::Client_lcd_button(QWidget *parent)
    : QMainWindow(parent) {

  QWidget* widget = new QWidget(this);

  QPushButton *redBtn = new QPushButton("Red", this);
  QPushButton *greenBtn = new QPushButton("Green", this);
  QPushButton *blueBtn = new QPushButton("Blue", this);
  QPushButton *yellowBtn = new QPushButton("Yellow", this);
  QPushButton *cyanBtn = new QPushButton("Cyan", this);
  QPushButton *purpleBtn = new QPushButton("Purple", this);
  QPushButton *whiteBtn = new QPushButton("White", this);
  QPushButton *blackBtn = new QPushButton("Black", this);
  QPushButton *textBtn = new QPushButton("send text", this);
  
  QGridLayout *grid = new QGridLayout(widget);
  grid->setSpacing(10);
  grid->addWidget(redBtn, 0, 0);
  grid->addWidget(greenBtn, 0, 1);
  grid->addWidget(blueBtn, 0, 2);
  grid->addWidget(yellowBtn, 1, 0);
  grid->addWidget(cyanBtn, 1, 1);
  grid->addWidget(purpleBtn, 1, 2);
  grid->addWidget(whiteBtn, 2, 0);
  grid->addWidget(blackBtn, 2, 1);

  QLineEdit *edt2 = new QLineEdit(widget);
  grid->addWidget(edt2, 3, 0, 3, 2);
  grid->addWidget(textBtn, 4, 2);

  widget->setLayout(grid);
  setCentralWidget(widget);  
  statusBar();

  connect(redBtn, &QPushButton::clicked, this, &Client_lcd_button::OnRed);
  connect(greenBtn, &QPushButton::clicked, this, &Client_lcd_button::OnGreen);
  connect(blueBtn, &QPushButton::clicked, this, &Client_lcd_button::OnBlue);
  connect(yellowBtn, &QPushButton::clicked, this, &Client_lcd_button::OnYellow);
  connect(cyanBtn, &QPushButton::clicked, this, &Client_lcd_button::OnCyan);
  connect(purpleBtn, &QPushButton::clicked, this, &Client_lcd_button::OnPurple);
  connect(whiteBtn, &QPushButton::clicked, this, &Client_lcd_button::OnWhite);
  connect(blackBtn, &QPushButton::clicked, this, &Client_lcd_button::OnBlack);
  connect(edt2, &QLineEdit::textChanged, this, &Client_lcd_button::setText);
  connect(textBtn, &QPushButton::clicked, this, &Client_lcd_button::sendText);

  sock = make_socket();
}

void Client_lcd_button::setText(const QString &t) {
  m_text = t;
  update();
}

void Client_lcd_button::send_lcd( const char * lcd ) {

  int valread;
  char buffer[1024] = {0};
  send(sock , lcd, strlen(lcd) , 0 );
  valread = read( sock, buffer, 1024 );
  buffer[valread] = '\0';
  statusBar()->showMessage(buffer);
}

void Client_lcd_button::sendText() {

  QByteArray inBytes = m_text.toLocal8Bit();
  const char * lcd = inBytes.data();
  send_lcd( lcd );
}

void Client_lcd_button::OnRed() {
  const char *lcd = "red";
  send_lcd( lcd );
}

void Client_lcd_button::OnGreen() {
  const char *lcd = "green";
  send_lcd( lcd ); 
}

void Client_lcd_button::OnBlue() {
  const char *lcd = "blue";
  send_lcd( lcd );
}

void Client_lcd_button::OnYellow() {
  const char *lcd = "yellow";
  send_lcd( lcd );
}

void Client_lcd_button::OnCyan() {
  const char *lcd = "cyan";
  send_lcd( lcd );
}

void Client_lcd_button::OnPurple() {
  const char *lcd = "purple";
  send_lcd( lcd );
}

void Client_lcd_button::OnWhite() {
  const char *lcd = "white";
  send_lcd( lcd );
}

void Client_lcd_button::OnBlack() {
  const char *lcd = "black";
  send_lcd( lcd );
}

int main(int argc, char *argv[]) {
    
  QApplication app(argc, argv);  
    
  Client_lcd_button window;

  window.resize(300, 200);
  window.setWindowTitle("client lcd button");
  window.show();

  return app.exec();
}
