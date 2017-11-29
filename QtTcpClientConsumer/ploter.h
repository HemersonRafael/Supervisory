#ifndef PLOTER_H
#define PLOTER_H

#include <QWidget>
#include <QDateTime>
#include <vector>
class Ploter : public QWidget
{
    Q_OBJECT
private:
    std::vector< double >timeList;
    std::vector< double >valueList;
    double deltaX;
    double x1;
    bool firstPrint;

public:
    //!Construtor da classe
    explicit Ploter(QWidget *parent = nullptr);
    //!Atualiza a região do ploter
    void paintEvent(QPaintEvent *event);
    //!Plotar o gráfico no Qwidget a partir das amostras coletadas no servidor.
    void draw(  std::vector<qint64 > _timeList, std::vector<int>_valueList);
signals:

public slots:
};

#endif // PLOTER_H
