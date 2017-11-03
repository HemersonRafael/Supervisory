#ifndef PLOTER_H
#define PLOTER_H

#include <QWidget>

class Ploter : public QWidget
{
    Q_OBJECT
public:
    explicit Ploter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
signals:

public slots:
};

#endif // PLOTER_H
