#include "chartlegend.h"
#include <QDebug>
#include <QFontMetrics>
#include <QPainter>

ChartLegend::ChartLegend(QQuickItem *parent) :
    QQuickPaintedItem(parent), pLocation{RightLocation}, pFont{new ChartFont(this)}, pElementsWidth{100}, rows{-1}, columns{-1}
{
    connect(pFont, SIGNAL(changed()), this, SLOT(calculateElementsHeight()));
    updateLegend();
}

void ChartLegend::recalculateSize(int newSize)
{
    qDebug() << "Legend: recalculateSize";
    if(series){
        //Обчислення першох компоненти розміру
        if(newSize>0){
            if(pLocation == RightLocation || pLocation == LeftLocation){
                int newRows = ceil((double)newSize/mElementsHeight);
                if(newRows!=rows)
                    setHeight(newSize);
            } else {
                int newColumns = ceil((double)newSize/pElementsWidth);
                if(newColumns!=columns)
                    setWidth(newSize);
            }
        }
        //Обчислення другої компоненти розміру
        if(pLocation == RightLocation || pLocation == LeftLocation){
            int newColumns = floor((double)series->length()/ceil((double)height()/mElementsHeight));
            if(newColumns != columns)
                setWidth(newColumns*pElementsWidth);
        } else {
            int newRows = floor((double)series->length()/ceil((double)width()/pElementsWidth));
            if(newRows != rows)
                setHeight(newRows*mElementsHeight);
        }
    }
}

void ChartLegend::setSeriesList(QList<AbstractSeries *> *list)
{
    if(list){
        series = list;
        updateLegend();
    }else series = nullptr;
}

void ChartLegend::setElementsWidth(int value)
{
    pElementsWidth = value;
    emit elementsWidthChanged();
    updateLegend();
}

int ChartLegend::elementsWidth() const
{
    return pElementsWidth;
}

void ChartLegend::setFont(ChartFont *value)
{
    if(value){
        pFont->deleteLater();
        pFont=value;
        emit fontChanged();
    }
}

ChartFont *ChartLegend::font()
{
    return pFont;
}

void ChartLegend::setLocation(int value)
{
    pLocation = static_cast<LegendLocation>(value);
    emit locationChanged();
    updateLegend();
}

ChartLegend::LegendLocation ChartLegend::location() const
{
    return pLocation;
}

void ChartLegend::paint(QPainter *painter)
{
    painter->setPen(QColor("black"));
    painter->drawRect(contentsBoundingRect());
}

void ChartLegend::updateLegend()
{
    if(series){
        recalculateSize(-1);
    }
}

void ChartLegend::calculateElementsHeight()
{
    QFontMetrics metrics(pFont->getFont());
    mElementsHeight = metrics.height()*1.2;
    updateLegend();
}
