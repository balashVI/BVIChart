#include "pieslice.h"
#include <QDebug>

PieSlice::PieSlice(QQuickItem *parent) :
    QQuickItem(parent), pValue{0}, pLabel{"Slice"}, pEnabled{true}, pColor{QColor("gray")}, pHighlightColor{QColor("lightgray")}
{
    setObjectName("PieSlice");
}

void PieSlice::setHighlightColor(const QColor &value)
{
    pHighlightColor = value;
    emit highlightColorChanged();
    emit changed();
}

const QColor &PieSlice::highlightColor() const
{
    return pHighlightColor;
}

void PieSlice::setColor(const QColor &value)
{
    pColor = value;
    emit colorChanged();
    emit changed();
}

const QColor &PieSlice::color() const
{
    return pColor;
}

void PieSlice::setEnabled(bool value)
{
    pEnabled = value;
    emit enabledChanged();
    emit changed();
}

bool PieSlice::enabled() const
{
    return pEnabled;
}

void PieSlice::setLabel(const QString &value)
{
    pLabel = value;
    emit labelChanged();
    emit changed();
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
    emit changed();
}

