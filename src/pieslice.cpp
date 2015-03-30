#include "pieslice.h"
#include <QDebug>

PieSlice::PieSlice(QQuickItem *parent) :
    QQuickItem(parent), pValue{0}, pLabel{"Slice"}, pColor{QColor("gray")}
{
}

void PieSlice::setColor(const QColor &value)
{
    pColor = value;
    emit colorChanged();
}

const QColor &PieSlice::color() const
{
    return pColor;
}

void PieSlice::setLabel(const QString &value)
{
    pLabel = value;
    emit labelChanged();
}

const QString& PieSlice::label() const
{
    return pLabel;
}

double PieSlice::value() const
{
    return pValue;
}

void PieSlice::setValue(double value)
{
    pValue = value;
    emit valueChanged();
}

