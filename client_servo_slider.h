#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QSlider>

class Client_servo_slider : public QMainWindow {
    
  Q_OBJECT

  public:
    Client_servo_slider(QWidget *parent = 0);

  private slots:
    void send_servo();

  private:
    QSlider *slider;
    int    sock;
};
