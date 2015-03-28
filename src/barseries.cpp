#include "barseries.h"
#include <QDebug>

BarSeries::BarSeries(QObject *parent) :
    AbstractSeries(parent), pStrokePen{new ChartPen(this)}
{
}

QColor BarSeries::color() const
{
    return pColor;
}

void BarSeries::setColor(const QColor &newColor)
{
    pColor = newColor;
    emit colorChanged();
}

ChartPen *BarSeries::strokePen() const
{
    return pStrokePen;
}

void BarSeries::setStrokePen(ChartPen *value)
{
    if(value){
        pStrokePen->deleteLater();
        pStrokePen=value;
        emit strokePenChanged();
    }
}

const QList<double> &BarSeries::data() const
{
    return pData;
}

void BarSeries::setData(QList<double> value)
{
    pData = std::move(value);
    emit dataChanged();
}
