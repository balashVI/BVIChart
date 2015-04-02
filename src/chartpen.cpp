#include "chartpen.h"

ChartPen::ChartPen(QObject *parent) :
    QObject(parent), pVisible{true}
{
    pen.setColor("lightgray");
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

bool ChartPen::visible() const
{
    return pVisible;
}

void ChartPen::setVisible(bool value)
{
    pVisible = value;
    emit visibleChanged();
}

const QPen &ChartPen::getPen() const
{
    return pen;
}
