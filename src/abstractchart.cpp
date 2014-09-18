#include "abstractchart.h"
#include <QDebug>

AbstractChart::AbstractChart(QQuickItem *parent) :
    QQuickItem(parent), pHeader{this}, pLegend{this}, pPadding{10}
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
    pHeader.setPosition(QPoint((width()-pHeader.width())/2, pPadding));
}

void AbstractChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    updateChildrenGeometry();
}

void AbstractChart::setPadding(int value)
{
    if(pPadding!=value){
        pPadding = value;
        updateChildrenGeometry();
        emit paddingChanged();
    }
}

int AbstractChart::padding() const
{
    return pPadding;
}
