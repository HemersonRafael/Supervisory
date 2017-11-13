#include "ploter.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>



Ploter::Ploter(QWidget *parent) : QWidget(parent)
{
    x0 = 0;
    y0 = height();
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

void Ploter::draw( std::vector<long long int> timeList, std::vector<int>valueList){

     qDebug() << timeList[0];

    QPainter painter(this);
    QBrush brush;
    QPen pen;

    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);
    pen.setColor(QColor(0,0,255));
    pen.setWidth(2);


}
