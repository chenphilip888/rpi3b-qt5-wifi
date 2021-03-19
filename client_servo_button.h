#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>

class Client_servo_button : public QMainWindow {
    
  Q_OBJECT

  public:
    Client_servo_button(QWidget *parent = 0);

  private slots:
    void servoRight();
    void servoLeft();
    void servoMiddle();
    void servoStop();

  private:
    void   send_servo( const char * servo );
    int    sock;
};
