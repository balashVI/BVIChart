#include "abstractaxis.h"
#include <QDebug>

AbstractAxis::AbstractAxis(QQuickItem *parent) :
    QQuickPaintedItem(parent), pAxisPen{new ChartPen(this)}, pMajorLines{new ChartPen(this)},
    pMinorLines{new ChartPen(this)}, pFont{new ChartFont(this)}
{
}

void AbstractAxis::setMinorLines(ChartPen *value)
{
    if(value){
        pMinorLines->deleteLater();
        pMinorLines=value;
        emit minorLinesChanged();
    }
}

ChartPen *AbstractAxis::minorLines() const
{
    return pMinorLines;
}

void AbstractAxis::setMajorLines(ChartPen *value)
{
    if(value){
        pMajorLines->deleteLater();
        pMajorLines=value;
        emit majorLinesChanged();
    }
}

ChartPen *AbstractAxis::majorLines() const
{
    return pMajorLines;
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
