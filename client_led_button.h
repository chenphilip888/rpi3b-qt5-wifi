#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>

class Client_led_button : public QMainWindow {
    
  Q_OBJECT

  public:
    Client_led_button(QWidget *parent = 0);

  private slots:
    void ledOn();
    void ledOff();

  private:
    void   send_led( const char * led );
    int    sock;
};
