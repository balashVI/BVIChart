#include "categoryaxis.h"
#include <QPainter>

CategoryAxis::CategoryAxis(QQuickItem *parent) :
    AbstractAxis(parent)
{
}

void CategoryAxis::paint(QPainter *painter)
{
    int categorysCount{pLabels.length()};
    if(categorysCount == 0) categorysCount = 1;
    int lineX;
    for(int i{0}; i!=(categorysCount-1); ++i){
        lineX =(width()/categorysCount)*(i+1);
        painter->drawLine(lineX, 0, lineX, height());
    }
}
