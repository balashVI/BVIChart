#include "lineseries.h"

LineSeries::LineSeries(QObject *parent) : BarSeries(parent), pDrawPoints{true}
{
    pStrokePen->setWidth(4);
}

bool LineSeries::drawPoints() const
{
    return pDrawPoints;
}

void LineSeries::setDrawPoints(bool value)
{
    pDrawPoints = value;
    emit drawPointsChanged();
}
