#include "chartpen.h"

ChartPen::ChartPen(QObject *parent) :
    QObject(parent)
{
}

int ChartPen::width() const
{
    return pen.width();
}

void ChartPen::setWidth(int newWidth)
{
    pen.setWidth(newWidth);
    emit widthChanged();
}

QColor ChartPen::color() const
{
    return pen.color();
}

void ChartPen::setColor(const QColor &newColor)
{
    pen.setColor(newColor);
    emit colorChanged();
}
