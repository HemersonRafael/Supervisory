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
    //!Construtor da classe
    explicit MainWindow(QWidget *parent = 0);
    //!Destrutor da classe
    ~MainWindow();



public slots:
    //!Resgata os dados enviado ao servidor.
    void getData();
    //!Manipula os eventos de temporização.
    void timerEvent(QTimerEvent *e);
    //!Inicializa a comunicação com o servidor.
    void tcpConnect();
    //!Finaliza a comunicação com servidor.
    void tcpDisconnect();
    //!Inicializa o processo de aquisição de dados.
    void start();
    //!Finaliza o processo de aquisição de dados.
    void stop();
    //!Atualiza a lista de ips que produziram dados.
    void update();
    //!Conecta-se ao ip clicado no listwidget
    void updateLineEditIP();

private slots:
    //!Trata ação de feixar o programa.
    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    int timer;
};

#endif // MAINWINDOW_H
