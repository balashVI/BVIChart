#include "barseries.h"
#include <QDebug>

BarSeries::BarSeries(QObject *parent) :
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
