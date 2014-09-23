#include "abstractseries.h"

AbstractSeries::AbstractSeries(QQuickItem *parent) :
    QQuickPaintedItem(parent), pName{"Series"}, pEnabled{true}, pColor{"gray"}
{
}

void AbstractSeries::setColor(const QColor &value)
{
    pColor = value;
    emit colorChanged();
}

QColor AbstractSeries::color() const
{
    return pColor;
}

void AbstractSeries::setEnabled(bool value)
{
    pEnabled = value;
    emit enabledChanged();
}

bool AbstractSeries::enabled() const
{
    return pEnabled;
}

QString AbstractSeries::name() const
{
    return pName;
}

void AbstractSeries::setName(const QString &value)
{
    pName=value;
    emit nameChanged();
}
