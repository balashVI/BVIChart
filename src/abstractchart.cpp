#include "abstractchart.h"
#include <QDebug>

AbstractChart::AbstractChart(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent), pSpacing{10}
{
    setClip(true);
}

void AbstractChart::setSpacing(int value)
{
    if(pSpacing!=value){
        pSpacing = value;
        emit spacingChanged();
    }
}

int AbstractChart::spacing() const
{
    return pSpacing;
}

void AbstractChart::paint(QPainter *painter)
{

}

double AbstractChart::calculateOrderOfMagnitude(double x)
{
    return qFloor(log(x)/log(10));
}

void AbstractChart::calculateScale(double drawingHeight, double maxSteps, double minSteps, double maxValue, double minValue,
                                   int &numberOfSteps, double &stepValue, double &graphMin)
{
    double valueRange {maxValue - minValue};
    stepValue = pow10(calculateOrderOfMagnitude(valueRange));
    graphMin = floor(minValue/stepValue)*stepValue;
    double graphMax {ceil(minValue/stepValue)*stepValue};
    double graphRange {graphMax-graphMin};
    numberOfSteps = qRound(graphRange/stepValue);
    while(numberOfSteps<minSteps || numberOfSteps>maxSteps){
        if(numberOfSteps<minSteps){
            stepValue /= 2.0;
            numberOfSteps = qRound(graphRange/stepValue);
        } else {
            stepValue *= 2.0;
            numberOfSteps = qRound(graphRange/stepValue);
        }
    }
}
