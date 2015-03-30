#include "piechart.h"
#include <QPainter>

PieChart::PieChart(QQuickPaintedItem *parent) :
    AbstractChart(parent), pAngleOffset{0}, pStrokePen{new ChartPen(this)}
{
    pStrokePen->setColor(QColor("white"));
    pStrokePen->setWidth(3);
}

QQmlListProperty<PieSlice> PieChart::slices()
{
    return QQmlListProperty<PieSlice>(this, 0, &PieChart::appendSlice, &PieChart::slicesListLength,
                                      &PieChart::sliceAt, 0);
}

ChartPen *PieChart::strokePen() const
{
    return pStrokePen;
}

void PieChart::setStrokePen(ChartPen *value)
{
    if(value){
        pStrokePen->deleteLater();
        pStrokePen=value;
        emit strokePenChanged();
    }
}

double PieChart::angleOffset() const
{
    return pAngleOffset;
}

void PieChart::setAngleOffset(double value)
{
    pAngleOffset = value;
    emit angleOffsetChanged();
}

void PieChart::appendSlice(QQmlListProperty<PieSlice> *slicesList, PieSlice *slice)
{
    PieChart *chart = qobject_cast<PieChart *>(slicesList->object);
    if (chart) {
        slice->setParent(chart);
        chart->slicesList.append(slice);
        connect(slice, SIGNAL(valueChanged()), chart, SLOT(calculateDataRange()));
        chart->calculateDataRange();
        emit chart->slicesChanged();
    }
}

int PieChart::slicesListLength(QQmlListProperty<PieSlice> *slicesList)
{
    PieChart *chart = qobject_cast<PieChart *>(slicesList->object);
    if(chart)
        return chart->slicesList.length();
    else return 0;
}

PieSlice *PieChart::sliceAt(QQmlListProperty<PieSlice> *slicesList, int index)
{
    PieChart *chart = qobject_cast<PieChart *>(slicesList->object);
    if(chart)
        return chart->slicesList.at(index);
    return nullptr;
}

void PieChart::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    //Обчислення області для малювання
    QRectF fillRect = boundingRect();
    if(fillRect.height() > fillRect.width()){
        fillRect.setY(fillRect.y() + (fillRect.height()-fillRect.width())/2);
        fillRect.setHeight(fillRect.width());
    } else {
        fillRect.setX(fillRect.x() + (fillRect.width()-fillRect.height())/2);
        fillRect.setWidth(fillRect.height());
    }
    fillRect.adjust(pStrokePen->width(), pStrokePen->width(), -pStrokePen->width(),
                    -pStrokePen->width());

    qDebug() << sumSliceValue;

    //Малювання сегментів
    painter->setPen(pStrokePen->getPen());
    double beginAngle = pAngleOffset;
    double segmentAngle;
    for(PieSlice* i:slicesList){
        painter->setBrush(QBrush(i->color()));
        segmentAngle = 5760.0 * fabs(i->value())/sumSliceValue;
        painter->drawPie(fillRect, beginAngle, segmentAngle);
        beginAngle += segmentAngle;
    }
}

void PieChart::calculateDataRange()
{
    sumSliceValue = 0;
    for(PieSlice* i:slicesList)
        sumSliceValue += fabs(i->value());
    update();
}
