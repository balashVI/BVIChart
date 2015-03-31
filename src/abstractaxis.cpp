#include "abstractaxis.h"
#include <QDebug>

AbstractAxis::AbstractAxis(QQuickItem *parent) :
    QQuickItem(parent), pAxisPen{new ChartPen(this)}, pGridLines{new ChartPen(this)},
    pLabelsFont{new ChartFont(this)}, pNameFont{new ChartFont(this)},
    pNameVisible{true}, pLabelsVisible{true}
{
    pLabelsFont->setPointSize(9);
    pNameFont->setPointSize(12);
    pNameFont->setBold(true);
}

void AbstractAxis::setLabelsVisible(bool value)
{
    pLabelsVisible = value;
    emit labelsVisibleChanged();
}

bool AbstractAxis::labelsVisible() const
{
    return pLabelsVisible;
}

void AbstractAxis::setNameColor(const QColor &value)
{
    pNameColor = value;
    emit nameColorChanged();
}

const QColor &AbstractAxis::nameColor() const
{
    return pNameColor;
}

void AbstractAxis::setNameVisible(bool value)
{
    pNameVisible = value;
    emit nameVisibleChanged();
}

bool AbstractAxis::nameVisible() const
{
    return pNameVisible;
}

void AbstractAxis::setNameFont(ChartFont *value)
{
    if(value){
        pNameFont->deleteLater();
        pNameFont = value;
        emit nameFontChanged();
    }
}

ChartFont *AbstractAxis::nameFont() const
{
    return pNameFont;
}

const QString &AbstractAxis::name() const
{
    return pName;
}

void AbstractAxis::setName(QString value)
{
    pName = std::move(value);
    emit nameChanged();
}

void AbstractAxis::setLabelsFont(ChartFont *value)
{
    if(value){
        pLabelsFont->deleteLater();
        pLabelsFont = value;
        emit labelsFontChanged();
    }
}

ChartFont *AbstractAxis::labelsFont() const
{
    return pLabelsFont;
}

void AbstractAxis::setGridLines(ChartPen *value)
{
    if(value){
        pGridLines->deleteLater();
        pGridLines=value;
        emit gridLinesChanged();
    }
}

ChartPen *AbstractAxis::gridLines() const
{
    return pGridLines;
}

void AbstractAxis::setAxisLine(ChartPen *value)
{
    if(value){
        pAxisPen->deleteLater();
        pAxisPen=value;
        emit axisLineChanged();
    }
}

ChartPen *AbstractAxis::axisLine() const
{
    return pAxisPen;
}

void AbstractAxis::setLabels(QList<QString> in)
{
    pLabels = std::move(in);
    emit labelsChanged();
}

const QList<QString>& AbstractAxis::labels() const
{
    return pLabels;
}

int AbstractAxis::min(int a, int b)
{
    if(a<b)
        return a;
    else
        return b;
}
