#ifndef PLOTER_H
#define PLOTER_H

#include <QWidget>
#include <QDateTime>
class Ploter : public QWidget
{
    Q_OBJECT
private:
    int x0, y0;
public:
    explicit Ploter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void draw(qint64 time, int value);
signals:

public slots:
};

#endif // PLOTER_H
