#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

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
  void getData();
  void timerEvent(QTimerEvent *e);
  void tcpConnect();
  void tcpDisconnect();
  void start();
  void stop();
  void update();
  void updateLineEditIP();

private slots:
  void on_actionQuit_triggered();

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  int timer;
};

#endif // MAINWINDOW_H
