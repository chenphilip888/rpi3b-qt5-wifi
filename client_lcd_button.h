#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QApplication>
#include <QPushButton>

class Client_lcd_button : public QMainWindow {
    
  Q_OBJECT

  public:
    Client_lcd_button(QWidget *parent = 0);

  private slots:
    void OnRed();
    void OnGreen();
    void OnBlue();
    void OnYellow();
    void OnCyan();
    void OnPurple();
    void OnWhite();
    void OnBlack();
    void setText(const QString &);
    void sendText();

  private:
    QLineEdit *edt2;
    void   send_lcd( const char * lcd );
    int    sock;
    QString m_text;
};
