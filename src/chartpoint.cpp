#include "chartpoint.h"

ChartPoint::ChartPoint(QQuickItem *parent): QQuickItem(parent), pX{0}, pY{0}
{

}

ChartPoint::~ChartPoint()
{

}

double ChartPoint::x() const
{
    return pX;
}

void ChartPoint::setX(double value)
{
    pX = value;
    emit xChanged();
}

double ChartPoint::y() const
{
    return pY;
}

void ChartPoint::setY(double value)
{
    pY = value;
    emit yChanged();
}