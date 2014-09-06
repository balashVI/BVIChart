#include "chartaxis.h"

ChartAxis::ChartAxis(QObject *parent) :
    QObject(parent), pVisible{true}, pVisibleLabels{true}, pAutomated{true}, pVisibleLines{true},
    pLineWidth{2}
{
}

void ChartAxis::changeFont(QVariantMap &value)
{
    ChartToolkit::variantMapToFont(pFont, value);
    emit changed();
    emit fontChanged();
}

bool ChartAxis::visible() const
{
    return pVisible;
}

void ChartAxis::setVisible(bool value)
{
    pVisible = value;
    emit visibleChanged();
    emit changed();
}

bool ChartAxis::visibleLabels() const
{
    return pVisibleLabels;
}

void ChartAxis::setVisibleLabels(bool value)
{
    pVisibleLabels = value;
    emit visibleLabelsChanged();
    emit changed();
}

QFont ChartAxis::font() const
{
    return pFont;
}

bool ChartAxis::automated() const
{
    return pAutomated;
}

void ChartAxis::setAutomated(bool value)
{
    pAutomated = value;
    emit automatedChanged();
    emit changed();
}

bool ChartAxis::visibleLines() const
{
    return pVisibleLines;
}

void ChartAxis::setVisibleLines(bool value)
{
    pVisibleLines = value;
    emit visibleLinesChanged();
    emit changed();
}

int ChartAxis::lineWidth() const
{
    return pLineWidth;
}

void ChartAxis::setLineWidth(int value)
{
    pLineWidth = value;
    emit lineWidthChanged();
    emit changed();
}
