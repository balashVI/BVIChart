#include "abstractchart.h"
#include <QDebug>

AbstractChart::AbstractChart(QQuickItem *parent) :
    QQuickItem(parent), pHeader{this}, pLegend{this}, pSpacing{10}
{
    qDebug() << (pHeader.parentItem() == this);
    setClip(true);
    connect(&pHeader, SIGNAL(sizeChanged()), this, SLOT(updateChildrenGeometry()));
    connect(&pLegend, SIGNAL(locationChanged()), this, SLOT(updateChildrenGeometry()));
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
    case (ChartLegend::RightLocation):
        pLegend.recalculateSize(height()-3*pSpacing-pHeader.height());
        pLegend.setX(x()+width()-pSpacing-pLegend.width());
        pLegend.setY(pHeader.y()+pHeader.height()+pSpacing);
        break;
    case(ChartLegend::LeftLocation):
        pLegend.recalculateSize(height()-3*pSpacing-pHeader.height());
        pLegend.setX(pSpacing);
        pLegend.setY(pHeader.y()+pHeader.height()+pSpacing);
        break;
    case(ChartLegend::TopLocation):
        pLegend.recalculateSize(width()-2*pSpacing);
        pLegend.setX(pSpacing);
        pLegend.setY(pHeader.y()+pHeader.height()+pSpacing);
        break;
    case(ChartLegend::BottomLocation):
        pLegend.recalculateSize(width()-2*pSpacing);
        pLegend.setX(pSpacing);
        pLegend.setY(y()+height()-pSpacing-pLegend.height());
        break;
    default:
        pLegend.recalculateSize(0);
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
