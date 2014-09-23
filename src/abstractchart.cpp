#include "abstractchart.h"
#include <QDebug>

AbstractChart::AbstractChart(QQuickItem *parent) :
    QQuickItem(parent), pHeader{this}, pLegend{this}, pSpacing{10}
{
    qDebug() << (pHeader.parentItem() == this);
    setClip(true);
    connect(&pHeader, SIGNAL(sizeChanged()), this, SLOT(updateChildrenGeometry()));
}

ChartHeader *AbstractChart::header()
{
    return &pHeader;
}

ChartLegend *AbstractChart::legend()
{
    return &pLegend;
}

void AbstractChart::updateChildrenGeometry()
{
    pHeader.setPosition(QPoint((width()-pHeader.width())/2, pSpacing));
    //Визначення координат та розмірів ChartLegend
    switch (pLegend.location()) {
    case ((int)ChartLegend::RightLocation):
        pLegend.recalculateSize(height()-3*spacing()-pHeader.height());
        pLegend.setX(x()+width()-spacing()-pLegend.width());
        pLegend.setY(pHeader.y()+pHeader.height()+spacing());
        break;
    default:
        break;
    }
}

void AbstractChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    updateChildrenGeometry();
}

void AbstractChart::setSpacing(int value)
{
    if(pSpacing!=value){
        pSpacing = value;
        updateChildrenGeometry();
        emit spacingChanged();
    }
}

int AbstractChart::spacing() const
{
    return pSpacing;
}
