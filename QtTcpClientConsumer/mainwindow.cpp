#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include "ploter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
    connect(ui->pushButtonUpdate,
            SIGNAL(clicked(bool)),
            this,
            SLOT(update()));


}

void MainWindow::tcpConnect(){
    socket->connectToHost(ui->lineEditIp->text(),1234);
    if(socket->state() == QAbstractSocket::ConnectedState ||socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }

    update();
}

void MainWindow::tcpDisconnect()
{
    socket->disconnectFromHost();

    if(socket->state() == QAbstractSocket::UnconnectedState ||
            socket->waitForDisconnected(3000)){
        qDebug() << "Disconnected";
    }


}

void MainWindow::start()
{
    timer = startTimer(ui->horizontalSliderTiming->value()*1000);
}

void MainWindow::stop()
{
    killTimer(timer);
}

void MainWindow::update()
{
    QString str, list;
    QListWidget* item = ui->listWidgetIps;

    list = "list\r\n";
    ui->listWidgetIps->clear();
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){

            socket->write(list.toStdString().c_str());
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            qDebug() << socket->bytesAvailable();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                qDebug() << str;
                ui->listWidgetIps->addItem(str);

            }
        }
    }

}

void MainWindow::updateLineEditIP()
{
    MainWindow::tcpDisconnect();
    QListWidgetItem *item = ui->listWidgetIps->currentItem();
    ui->lineEditIp->setText(item->text());
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    MainWindow::getData();

}

void MainWindow::getData(){
    QString str , get;
    QByteArray array;
    QStringList list;

    qint64 thetime;
    std::vector<qint64> timeList;
    std::vector<int> valueList;

    int nAmostras = 30;

    get = "get " + ui->lineEditIp->text() + " " + QString::number( nAmostras)  + "\r\n";
    qDebug() << get;
    qDebug() << "to get data...";
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "reading...";
            socket->write( get.toStdString().c_str() );
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            //      qDebug() << socket->bytesAvailable();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                list = str.split(" ");
                if(list.size() == 2){
                    bool ok;
                    str = list.at(0);
                    thetime = str.toLongLong(&ok);
                    str = list.at(1);
                    //qDebug()  << "theTime: "<< thetime << ": " << str;
                    // qDebug() << "int valor: ";
                    // qDebug() << str.toInt();
                    timeList.push_back(thetime);
                    valueList.push_back(str.toInt() );
                    if(timeList.size() >= 30 && valueList.size() >= 30){
                        //  qDebug() << "time size: " << timeList.size() << "value size: " << valueList.size();
                        ui->widgetGrafico->draw(timeList,valueList);
                        timeList.clear();
                        valueList.clear();

                    }


                    //  qDebug() << timeList.size();

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
