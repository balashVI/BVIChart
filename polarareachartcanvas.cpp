#include "polarareachartcanvas.h"

PolarAreaChartCanvas::PolarAreaChartCanvas(QQuickItem *parent) :
    PieChartCanvas(parent), pAxis{new ChartAxis(this)}
{
}

ChartAxis *PolarAreaChartCanvas::axis() const
{
    return pAxis;
}

void PolarAreaChartCanvas::paint(QPainter *painter)
{
    painter->setBrush(QBrush(QColor("brown")));
    painter->setPen(QColor(255,255,255,255));
    QRectF rect = contentsBoundingRect();
    rect.setX(rect.x()+50);
    rect.setY(rect.y()+50);
    rect.setWidth(rect.width()-50);
    rect.setHeight(rect.height()-50);
    painter->drawRect(rect);
}
