#include "chartlegend.h"
#include <QDebug>
#include <QFontMetrics>
#include <QPainter>

ChartLegend::ChartLegend(QQuickItem *parent) :
    QQuickPaintedItem(parent), pLocation{RightLocation}, pFont{new ChartFont(this)}, pElementsWidth{100}, pElementsPadding{7},
    rows{-1}, columns{-1}
{
    setAntialiasing(true);
    connect(pFont, SIGNAL(changed()), this, SLOT(calculateElementsHeight()));
    calculateElementsHeight();
    updateLegend();
}

void ChartLegend::recalculateSize(int newSize)
{

    if(series){
        //Обчислення першої компоненти розміру
        if(newSize>0){
            if(pLocation == RightLocation || pLocation == LeftLocation){
                int newRows = floor((double)newSize/mElementsHeight);
                if(newRows!=rows){
                    if(newRows > series->length()){
                        setSize(QSize(pElementsWidth, mElementsHeight*series->length()));
                        rows = series->length();
                        columns = 1;
                        return;
                    } else {
                        setHeight(newRows*mElementsHeight);
                        rows = newRows;
                    }
                }
            } else {
                int newColumns = floor((double)newSize/pElementsWidth);
                if(newColumns!=columns){
                    if(newColumns > series->length()){
                        setSize(QSize(pElementsWidth*series->length(), mElementsHeight));
                        columns = series->length();
                        rows = 1;
                        return;
                    } else {
                        setWidth(newColumns*pElementsWidth);
                        columns = newColumns;
                    }
                }
            }
        }

        //Екщо не вміщається жоден елемент, то вихід
        if(pLocation == RightLocation || pLocation == LeftLocation){
            if(height() < mElementsHeight)
               return;
        }else {
            if(width() < pElementsWidth)
                return;
        }

        //Обчислення другої компоненти розміру
        if(pLocation == RightLocation || pLocation == LeftLocation){
            int newColumns = ceil((double)series->length()/floor((double)height()/mElementsHeight));
            if(newColumns != columns){
                setWidth(newColumns*pElementsWidth);
                columns = newColumns;
            }
        } else {
            int newRows = ceil((double)series->length()/floor((double)width()/pElementsWidth));
            if(newRows != rows){
                setHeight(newRows*mElementsHeight);
                rows = newRows;
            }
        }
    }
    update();
}

void ChartLegend::setSeriesList(QList<AbstractSeries *> *list)
{
    if(list){
        series = list;
        updateLegend();
    }else series = nullptr;
}

void ChartLegend::setElementsPadding(int value)
{
    if(value>0){
        pElementsPadding = value;
        emit elementsPaddingChanged();
        calculateElementsHeight();
    }
}

int ChartLegend::elementsPadding() const
{
    return pElementsPadding;
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
    qDebug() << "Legend: painted";
    painter->drawRect(boundingRect());
    if(series){
        QPoint elementPoint(0,0);
        for(int i=0;i<series->length();++i){
            painter->setPen(QPen(QColor(0,0,0,0)));
            painter->setBrush(QBrush(series->at(i)->color()));
            painter->drawRoundedRect(QRectF(elementPoint.x()+0.5*pElementsPadding, elementPoint.y()+0.5*pElementsPadding,
                                            mElementsHeight-pElementsPadding, mElementsHeight-pElementsPadding), 5, 5);

            painter->setPen(QPen(QColor(0,0,0)));
            QRectF textRect(elementPoint.x()+mElementsHeight, elementPoint.y()+pElementsPadding, pElementsWidth-mElementsHeight,
                            mElementsHeight-2*pElementsPadding);
            painter->drawText(textRect, series->at(i)->name());

            //Обчислення кооддинати нового елемента
            if(pLocation == RightLocation || pLocation == LeftLocation){
                if(!((i+1)%rows)){
                    elementPoint.setX(elementPoint.x()+pElementsWidth);
                    elementPoint.setY(0);
                } else
                    elementPoint.setY(elementPoint.y()+mElementsHeight);
            } else {
                if(!((i+1)%columns)){
                    elementPoint.setY(elementPoint.y()+mElementsHeight);
                    elementPoint.setX(0);
                } else
                    elementPoint.setX(elementPoint.x()+pElementsWidth);
            }

        }
    }
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
    mElementsHeight = metrics.height()+2*pElementsPadding;
    updateLegend();
}
