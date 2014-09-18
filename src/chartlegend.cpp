#include "chartlegend.h"

ChartLegend::ChartLegend(QQuickItem *parent) :
    QQuickItem(parent)
{
}

void ChartLegend::setLegendData(QVector<QString> &&labels, QVector<QColor> &&colors)
{

}

void ChartLegend::setLocation(int value)
{
    pLocation = static_cast<LegendLocation>(value);
    emit locationChanged();
}

ChartLegend::LegendLocation ChartLegend::location() const
{
    return pLocation;
}
