#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  connect(ui->pushButtonConnect_2,
          SIGNAL(clicked(bool)),
          SLOT(tcpConnect()));

  connect(ui->pushButtonDisconnect_2,
          SIGNAL(clicked(bool)),
          SLOT(tcpDisconnect()));

  connect(ui->pushButtonConnectStart_2,
          SIGNAL(clicked(bool)),
          this,
          SLOT(startTime()));
  connect(ui->pushButtonConnectStop_2,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stopTime()));

}

void MainWindow::tcpConnect(){
  socket->connectToHost(ui->lineEditIp->text(),1234);
  if(socket->state() == QAbstractSocket::ConnectedState ||socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::tcpDisconnect()
{
    socket->disconnectFromHost();

    if(socket->state() == QAbstractSocket::UnconnectedState ||
            socket->waitForDisconnected(3000)){
      qDebug() << "Disconnected";
    }


}

void MainWindow::startTime()
{
    timer = startTimer(ui->horizontalSliderTiming_2->value()*1000);
}

void MainWindow::stopTime()
{
    killTimer(timer);
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    getData();

}

void MainWindow::getData(){
  QString str , get;
  QByteArray array;
  QStringList list;
  QListWidgetItem *item = ui->listWidget->currentItem();
  qint64 thetime;
  get = "get " + item->text() + " 5 \r\n";
  qDebug() << get;
  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      socket->write( get.toStdString().c_str() );
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          bool ok;
          str = list.at(0);
          thetime = str.toLongLong(&ok);
          str = list.at(1);
          qDebug() << thetime << ": " << str;
        }
      }
    }
  }
}


MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}
