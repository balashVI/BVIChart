#include "bubble.h"

Bubble::Bubble(QQuickItem *parent): ChartPoint(parent), pValue{0}
{

}

Bubble::~Bubble()
{

}

double Bubble::value() const
{
    return pValue;
}

void Bubble::setValue(double value)
{
    pValue = value;
    emit valueChanged();
}

