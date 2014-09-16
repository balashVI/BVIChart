#include "xychart.h"
#include <QDebug>

XYChart::XYChart(QQuickItem *parent) :
    QQuickItem(parent)
{
    pHeader.setParentItem(this);
    pHeader.setX(10);
    pHeader.setY(10);
    pHeader.setSize(QSize(100,100));
}

void XYChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    pHeader.setPosition(QPointF(width()/2, height()/2));
}

ChartHeader *XYChart::header()
{
    return &pHeader;
}

//void XYChart::paint(QPainter *painter)
//{
//}
