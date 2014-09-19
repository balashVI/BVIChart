#include "abstractseries.h"

AbstractSeries::AbstractSeries(QQuickItem *parent) :
    QQuickPaintedItem(parent), pName{"Series"}, pEnabled{true}
{
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
    if(pName!=value){
        pName=value;
        emit nameChanged();
    }
}
