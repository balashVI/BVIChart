#include "standartaxis.h"

StandartAxis::StandartAxis(QQuickItem *parent) :
    AbstractAxis(parent)
{
}

int StandartAxis::calculateAxisLinePosition()
{
    return 0;
}

void StandartAxis::paint(QPainter *painter)
{
//    painter->setBrush(QBrush(QColor("#11111111")));
//    painter->drawRect(QRect(0, 0, width()-1,height()));
}
