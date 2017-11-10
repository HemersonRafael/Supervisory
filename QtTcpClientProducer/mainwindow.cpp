#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QString>
#include <QTextBrowser>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          SLOT(tcpConnect()));

  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          SLOT(tcpDisconnect()));

  connect(ui->pushButtonConnectStart,
          SIGNAL(clicked(bool)),
          this,
          SLOT(start()));
  connect(ui->pushButtonConnectStop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stop()));

}

void MainWindow::tcpConnect(){
  socket->connectToHost(ui->lineEditIp->text(),1234);
  if(socket->state() == QAbstractSocket::ConnectedState ||
          socket->waitForConnected(3000)){
    qDebug() << "Connected";
    ui->textBrowser->append("Connected");
  }
  else{
    qDebug() << "Disconnected";
    ui->textBrowser->append("Disconnected");
  }
}

void MainWindow::tcpDisconnect(){
    socket->disconnectFromHost();

    if(socket->state() == QAbstractSocket::UnconnectedState ||
            socket->waitForDisconnected(3000)){
      qDebug() << "Disconnected";
      ui->textBrowser->append("Disconnected");
    }
}

void MainWindow::start(){
    timer = startTimer(ui->horizontalSliderTiming->value()*1000);
}

void MainWindow::stop(){
    killTimer(timer);
}

void MainWindow::timerEvent(QTimerEvent *e){
    MainWindow::putData();

}

void MainWindow::putData(){
  QDateTime datetime;
  QString str;
  qint64 msecdate;


  if(socket->state()== QAbstractSocket::ConnectedState){

    msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
    str = "set "+ QString::number(msecdate) + " " + QString::number(frand())+"\r\n";
      qDebug() << ui->horizontalSliderMax->value();
      qDebug() << ui->horizontalSliderMin->value();
      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      ui->textBrowser->append(str);
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }

}

MainWindow::~MainWindow(){
  delete socket;
    delete ui;
}

void MainWindow::on_actionQuit_triggered(){
    close();
}
int MainWindow::frand(){
   int i;
   i = qrand()%ui->horizontalSliderMax->value()+ui->horizontalSliderMin->value();
   if(i<=ui->horizontalSliderMax->value()){
       return i;
   }
   else{
       return ui->horizontalSliderMax->value();
   }


}
