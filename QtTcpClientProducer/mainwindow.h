#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}
/*!
 *  A classe MainWindow é responsável pela construção da interface gráfica.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Inicializar as conecxões dos componetes.
    explicit MainWindow(QWidget *parent = 0);
    //! Finalizar as conecxões dos componetes.
    ~MainWindow();
    //!Gera números aleatórios.
    int frand();
public slots:
    //!Controla o tempo de envio de dados para o servidor.
    void timerEvent(QTimerEvent *e);
    //!Realizar o envio da hora e dado, para servidor.
    void putData();
    //!Realizar o processo de conecxão com o servidor.
    void tcpConnect();
    //!Realizar o processo de desconecxão com o servidor.
    void tcpDisconnect();
    //!Inicializar o processo de envio dos dados para servidor.
    void start();
    //!Finalizar o processo de envio dos dados para servidor.
    void stop();

private slots:
    //!Acionar o fechamento do programa.
    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    int timer;
};

#endif // MAINWINDOW_H
