#include "categoryaxis.h"
#include <QPainter>

CategoryAxis::CategoryAxis(QQuickItem *parent) :
    AbstractAxis(parent), numberOfCategories{1}
{
}

void CategoryAxis::setNumberOfCategories(int value)
{
    numberOfCategories = value;
    update();
}

void CategoryAxis::paint(QPainter *painter)
{
    //Малювання основних ліній сітки
    if(pMajorLines->visible()){
        painter->setPen(pMajorLines->getPen());
        int lineX;
        for(int i{0}; i!=(numberOfCategories-1); ++i){
            lineX =(width()/numberOfCategories)*(i+1);
            painter->drawLine(lineX, 0, lineX, height());
        }
    }
}
