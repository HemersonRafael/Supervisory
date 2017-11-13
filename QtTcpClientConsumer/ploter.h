#ifndef PLOTER_H
#define PLOTER_H

#include <QWidget>
#include <QDateTime>
#include <vector>
class Ploter : public QWidget
{
    Q_OBJECT
private:
    int x0, y0;
public:
    explicit Ploter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
//    std::vector<long long int> timeList;
//    std::vector<int>valueList;
    void draw(  std::vector<long long int> timeList, std::vector<int>valueList);
signals:

public slots:
};

#endif // PLOTER_H
