#include "categoryaxis.h"
#include <QPainter>

CategoryAxis::CategoryAxis(QQuickItem *parent) :
    AbstractAxis(parent), numberOfCategories{1}, axisLinePosition{0}, space{5}
{
}

void CategoryAxis::setNumberOfCategories(int value)
{
    numberOfCategories = value;
    update();
}

int CategoryAxis::calculateAxisLinePosition()
{

}

void CategoryAxis::paint(QPainter *painter)
{
    int y{height()};

    //Малювання назви осі
    if(pNameVisible){
        y -= pNameFont->getHeight();
        painter->setFont(pNameFont->getFont());
        painter->setPen(pNameColor);
        painter->drawText(QRectF(0, y, width(), pNameFont->getHeight()),
                           Qt::AlignCenter, pName);
        y -= space;
    }

    //Малювання назв категорій
    if(pLabelsVisible){
        y -= pLabelsFont->getHeight();
        painter->setFont(pLabelsFont->getFont());
        QRectF textRect{QRectF(0,0,width()/numberOfCategories, pLabelsFont->getHeight())};
        textRect.moveTop(y);
        int step{width()/numberOfCategories};
        for(int i{0}; i!=numberOfCategories && i!=pLabels.length(); ++i){
            textRect.moveLeft(i*step);
            painter->drawText(textRect, Qt::AlignCenter, pLabels.at(i));
        }
    }

    //Малювання основних ліній сітки
    if(pMajorLines->visible()){
        painter->setPen(pMajorLines->getPen());
        int lineX;
        for(int i{0}; i!=(numberOfCategories-1); ++i){
            lineX =(width()/numberOfCategories)*(i+1);
            painter->drawLine(lineX, 0, lineX, y);
        }
    }

    //Малювання лінії осі
    if(pAxisPen->visible()){
        y -= space;
        painter->setPen(pAxisPen->getPen());
        painter->drawLine(0, y, width(), y);
    }
}
