#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QSlider>
#include <QLabel>

class Client_lcd_slider : public QMainWindow {
    
  Q_OBJECT

  public:
    Client_lcd_slider(QWidget *parent = 0);

  private slots:
    void send_lcd();

  private:
    QSlider *sliderR;
    QSlider *sliderG;
    QSlider *sliderB;
    QLabel *labelR;
    QLabel *labelG;
    QLabel *labelB;
    int    sock;
};
