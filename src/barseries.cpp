#include "barseries.h"

BarSeries::BarSeries(QQuickItem *parent) :
    AbstractSeries(parent)
{
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

void BarSeries::paint(QPainter *painter)
{
}
