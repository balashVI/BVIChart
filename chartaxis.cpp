#include "chartaxis.h"
#include <QDebug>
#include <QtMath>
#include <QFontMetrics>

ChartAxis::ChartAxis(QObject *parent):
    QObject(parent), pVisible{true}, pVisibleLabels{true}, pVisibleLines{true},
    pTextColor{QColor(0,0,0)}, pVisibleLabelBackground{false}, pLabelBackgroundColor{QColor(250,250,250,200)},
    pLabelPadding{3}, pInvert{false}, pFixedMin{false}, pFixedMax{false}, pMin{0}, pMax{10}, pFixedNumberOfSteps{false},
    pNumberOfSteps{5}, pFixedLabels{false}, mOrientation{AxisOrientation::Horizontal}, mLength{0}
{
    pFont.setPointSize(10);
    linePen.setWidth(1);
    linePen.setColor(QColor(150,150,150, 200));
    linePen.setStyle(Qt::DotLine);
}

void ChartAxis::setOrientation(int value)
{
    mOrientation = value;
}

const QPen &ChartAxis::getLinePen() const
{
    return linePen;
}

int ChartAxis::labelHeight() const
{
    return mLabelHeight;
}

void ChartAxis::setMinMaxDataValues(double min, double max)
{
    minDataValue = min;
    maxDataValue = max;
    update();
}

const QList<QString> &ChartAxis::labels()
{
    return pFixedLabels?pLabels:mLabels;
}

int ChartAxis::convertValue(double value) const
{
    if(pInvert)
        return (value-maxPaintedValue)/(minPaintedValue-maxPaintedValue)*mLength;
    else
        return (value-minPaintedValue)/(maxPaintedValue-minPaintedValue)*mLength;
}

void ChartAxis::setLength(int value)
{
    if(value>0 && mLength!=value){
        mLength = value;
        update();
    }
}

int ChartAxis::length() const
{
    return mCorrectedLength;
}

void ChartAxis::changeFont(QVariantMap &value)
{
    ChartToolkit::variantMapToFont(pFont, value);
    update();
    emit changed();
    emit fontChanged();
}

void ChartAxis::setLabels(QList<QString> &value)
{
    pLabels = value;
    if(!pFixedLabels){
        pFixedLabels = true;
        emit fixedLabelsChanged();
    }
    update();
    emit labelsChanged();
    emit changed();
}

void ChartAxis::setFixedLabels(bool value)
{
    pFixedLabels = value;
    update();
    emit changed();
    emit fixedLabelsChanged();
}

bool ChartAxis::fixedLabels() const
{
    return pFixedLabels;
}

void ChartAxis::setNumberOfSteps(int value)
{
    if(value > 0){
        pNumberOfSteps = value;
        if(!pFixedNumberOfSteps){
            pFixedNumberOfSteps = true;
            emit fixedNumberOfStepsChanged();
        }
        emit numberOfStepsChanged();
        emit changed();
    }
}

int ChartAxis::numberOfSteps() const
{
    return mNumberOfSteps;
}

void ChartAxis::setFixedNumberOfSteps(bool value)
{
    pFixedNumberOfSteps = value;
    update();
    emit fixedNumberOfStepsChanged();
    emit changed();
}

bool ChartAxis::fixedNumberOfSteps() const
{
    return pFixedNumberOfSteps;
}

void ChartAxis::setMax(double value)
{
    pMax = value;
    if(!pFixedMax){
        pFixedMax = true;
        emit fixedMaxChanged();
    }
    update();
    emit maxChanged();
    emit changed();
}

double ChartAxis::max() const
{
    return pMax;
}

void ChartAxis::setFixedMax(bool value)
{
    pFixedMax = value;
    update();
    emit fixedMaxChanged();
    emit changed();
}

bool ChartAxis::fixedMax() const
{
    return pFixedMax;
}

void ChartAxis::setMin(double value)
{
    pMin = value;
    if(!pFixedMin){
        pFixedMin = true;
        emit fixedMinChanged();
    }
    update();
    emit minChanged();
    emit changed();
}

double ChartAxis::min() const
{
    return pMin;
}

void ChartAxis::setFixedMin(bool value)
{
    pFixedMin = value;
    update();
    emit fixedMinChanged();
    emit changed();
}

bool ChartAxis::fixedMin() const
{
    return pFixedMin;
}

void ChartAxis::setInvert(bool value)
{
    pInvert = value;
    update();
    emit changed();
    emit invertChanged();
}

bool ChartAxis::invert() const
{
    return pInvert;
}

void ChartAxis::setLabelPadding(unsigned int value)
{
    pLabelPadding = value;
    update();
    emit labelPaddingChanged();
    emit changed();
}

unsigned int ChartAxis::labelPadding() const
{
    return pLabelPadding;
}

void ChartAxis::setLabelBackgroundOpacity(double value)
{
    if(value>=1 || value<0)
        pLabelBackgroundColor.setAlpha(1);
    else
        pLabelBackgroundColor.setAlpha(value);
    emit labelBackgroundOpacityChanged();
    emit changed();
}

double ChartAxis::labelBackgroundOpacity() const
{
    return pLabelBackgroundColor.alpha()/255.0;
}

void ChartAxis::setLabelBackgroundColor(QColor value)
{
    value.setAlpha(pLabelBackgroundColor.alpha());
    pLabelBackgroundColor = value;
    emit labelBackgroundColorChanged();
    emit changed();
}

QColor ChartAxis::labelBackgroundColor() const
{
    return pLabelBackgroundColor;
}

void ChartAxis::setVisibleLabelBackground(bool value)
{
    pVisibleLabelBackground = value;
    update();
    emit visibleLabelBackgroundChanged();
    emit changed();
}

bool ChartAxis::visibleLabelBackground() const
{
    return pVisibleLabelBackground;
}

QColor ChartAxis::textColor() const
{
    return pTextColor;
}

void ChartAxis::setTextColor(QColor &value)
{
    pTextColor = value;
    emit textColorChanged();
    emit changed();
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
    update();
    emit visibleLabelsChanged();
    emit changed();
}

QFont ChartAxis::font() const
{
    return pFont;
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
    return linePen.width();
}

void ChartAxis::setLineWidth(int value)
{
    linePen.setWidth(value);
    emit lineWidthChanged();
    emit changed();
}

QColor ChartAxis::lineColor() const
{
    return linePen.color();
}

void ChartAxis::setLineColor(QColor value)
{
    value.setAlpha(linePen.color().alpha());
    linePen.setColor(value);
    emit lineColorChanged();
    emit changed();
}

double ChartAxis::lineOpacity() const
{
    return linePen.color().alpha()/255.0;
}

void ChartAxis::setLineOpacity(double value)
{
    QColor color {linePen.color()};
    color.setAlpha(value*255);
    linePen.setColor(color);
    emit lineOpacityChanged();
    emit changed();
}

Qt::PenStyle ChartAxis::lineStyle() const
{
    return linePen.style();
}

void ChartAxis::setLineStyle(Qt::PenStyle value)
{
    linePen.setStyle(value);
    emit lineStyleChanged();
    emit changed();
}

void ChartAxis::update()
{
    QFontMetrics metrics(pFont);
    mLabelHeight = metrics.height();
    if(pVisibleLabelBackground)
        mLabelHeight+=2*pLabelPadding;

    int maxSteps;
    int minSteps;

    if(mOrientation == AxisOrientation::Vertical){
        maxSteps = qFloor(mLength / (mLabelHeight*0.66));
        minSteps = qFloor(mLength / mLabelHeight*0.5);
    }else{
        maxSteps=0;
        minSteps=0;
    }

    //Знаходження максимального і мінімального відображуваного значення
    double valueRange {maxDataValue - minDataValue};
    double rangeOrderOfMagnitude {qPow(10, calculateOrderOfMagnitude(valueRange))};
    if(pFixedMin)
        minPaintedValue = pMin;
    else
        minPaintedValue = qFloor(minDataValue / rangeOrderOfMagnitude) * rangeOrderOfMagnitude;
    if(pFixedMax)
        maxPaintedValue = pMax;
    else
        maxPaintedValue = qCeil(maxDataValue / rangeOrderOfMagnitude) * rangeOrderOfMagnitude;

    if(pFixedLabels){
        if(!pLabels.length())
            pLabels << "";
        mNumberOfSteps = pLabels.length();
    } else {
        //Знаходження кількості кроків сітки
        double stepValue {rangeOrderOfMagnitude};
        double graphRange {maxPaintedValue - minPaintedValue};
        if(!pFixedNumberOfSteps){
            mNumberOfSteps = qRound(graphRange / stepValue);
            while(mNumberOfSteps < minSteps || mNumberOfSteps > maxSteps) {
                if (mNumberOfSteps < minSteps) {
                    stepValue /= 2;
                    mNumberOfSteps = qRound(graphRange/stepValue);
                } else{
                    stepValue *=2;
                    mNumberOfSteps = qRound(graphRange/stepValue);
                }
            }
            if(pFixedMax || pFixedMin)
                stepValue = graphRange/mNumberOfSteps;
            if(!mNumberOfSteps)
                mNumberOfSteps=1;
        } else {
            mNumberOfSteps = pNumberOfSteps;
            stepValue = graphRange/mNumberOfSteps;
        }

        //Заповнення списку позначок
        mLabels.clear();
        if(pInvert)
            for (int i=mNumberOfSteps-1; i>=0; --i)
                mLabels.append(QString::number(minPaintedValue + (stepValue * i)));
        else
            for (int i=1; i<=mNumberOfSteps; ++i)
                mLabels.append(QString::number(minPaintedValue + (stepValue * i)));
    }
    mCorrectedLength = qFloor(mLength/mNumberOfSteps)*mNumberOfSteps;
}

double ChartAxis::calculateOrderOfMagnitude(double value)
{
    return qFloor(qLn(value)/qLn(10));
}
