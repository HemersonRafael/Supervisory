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
    double deltaX = 0;
    double x1;


    bool firstPrint = true;

public:
    explicit Ploter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
//    std::vector<long long int> timeList;
//    std::vector<int>valueList;
    void draw(  std::vector<qint64 > _timeList, std::vector<int>_valueList);
signals:

public slots:
};

#endif // PLOTER_H
