#include "polarareachart.h"

PolarAreaChart::PolarAreaChart(QQuickPaintedItem *parent):
    AbstractChart(parent), pAngleOffset{0}, pStrokePen{new ChartPen(this)}
{
    pStrokePen->setColor(QColor("white"));
    pStrokePen->setWidth(3);
}

ChartPen *PolarAreaChart::strokePen() const
{
    return pStrokePen;
}

void PolarAreaChart::setStrokePen(ChartPen *value)
{
    if(value){
        pStrokePen->deleteLater();
        pStrokePen=value;
        emit strokePenChanged();
    }
}

double PolarAreaChart::angleOffset() const
{
    return pAngleOffset;
}

void PolarAreaChart::setAngleOffset(double value)
{
    pAngleOffset = value;
    emit angleOffsetChanged();
}

void PolarAreaChart::calculateDataRange()
{

}

