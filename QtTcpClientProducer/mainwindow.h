#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();


  

public slots:
  void timerEvent(QTimerEvent *e);
  void putData();
  void tcpConnect();
  void tcpDisconnect();
  void startTime();
  void stopTime();

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  int timer;
};

#endif // MAINWINDOW_H
