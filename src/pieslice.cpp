#include "pieslice.h"
#include <QDebug>

PieSlice::PieSlice(QQuickItem *parent) :
    AbstractSeries(parent), pValue{0}
{
    pName = "Slice";
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

