#include "ploter.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

Ploter::Ploter(QWidget *parent) : QWidget(parent)
{

}

void Ploter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);
    pen.setColor(QColor(211,211,211));
    pen.setWidth(2);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(0,0,width(),height());


    pen.setColor(QColor(211,211,211));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);

    for(int i=0; i<width(); i= i+10){
        painter.drawLine(i,0,i,height());
    }

    for(int i=0; i<height(); i= i+10){
        painter.drawLine(0,i,width(),i);
    }



}
