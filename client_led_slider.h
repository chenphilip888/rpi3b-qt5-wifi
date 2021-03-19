#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QSlider>

class Client_led_slider : public QMainWindow {
    
  Q_OBJECT

  public:
    Client_led_slider(QWidget *parent = 0);

  private slots:
    void   send_led();

  private:
    QSlider *slider;
    int    sock;
};
