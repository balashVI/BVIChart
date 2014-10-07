#include "abstractaxis.h"
#include <QDebug>

AbstractAxis::AbstractAxis(QQuickItem *parent) :
    QQuickPaintedItem(parent), pAxisPen{new ChartPen}
{
}

void AbstractAxis::setLabels(QList<QString> in)
{
    pLabels = std::move(in);
    emit labelsChanged();
}

QList<QString> AbstractAxis::labels() const
{
    return pLabels;
}
