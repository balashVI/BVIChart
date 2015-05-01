#include "polarareachart.h"
#include <QPainter>

PolarAreaChart::PolarAreaChart(QQuickPaintedItem *parent):
    AbstractChart(parent), pAngleOffset{0}, pStrokePen{new ChartPen(this)}
{
    pStrokePen->setColor(QColor("white"));
    pStrokePen->setWidth(3);
}

QQmlListProperty<PolarArea> PolarAreaChart::polarAreas()
{
    return QQmlListProperty<PolarArea>(this, 0, &PolarAreaChart::appendPolarArea, &PolarAreaChart::polarAreasListLength,
                                       &PolarAreaChart::polarAreaAt, 0);
}

PolarRAxis *PolarAreaChart::axis()
{
    return &pAxis;
}

ChartPen *PolarAreaChart::strokePen() const
{
    return pStrokePen;
}

void PolarAreaChart::setStrokePen(ChartPen *value)
{
    if(value){
        pStrokePen->deleteLater();
        pStrokePen=value;
        emit strokePenChanged();
    }
}

double PolarAreaChart::angleOffset() const
{
    return pAngleOffset/16;
}

void PolarAreaChart::setAngleOffset(double value)
{
    pAngleOffset = value*16;
    emit angleOffsetChanged();
}

QVariantList PolarAreaChart::generateLegend()
{
    QVariantList list;
    QVariantMap map;
    for(PolarArea *area: polarAreasList){
        map.clear();
        map.insert("name", area->name());
        map.insert("color", area->color());
        list.append(map);
    }
    return list;
}

void PolarAreaChart::appendPolarArea(QQmlListProperty<PolarArea> *polarAreasList, PolarArea *polarArea)
{
    PolarAreaChart *chart = qobject_cast<PolarAreaChart *>(polarAreasList->object);
    if (chart) {
        polarArea->setParent(chart);
        chart->polarAreasList.append(polarArea);
        connect(polarArea, SIGNAL(valueChanged()), chart, SLOT(calculateDataRange()));
        chart->calculateDataRange();
        emit chart->polarAreasChanged();
    }
}

int PolarAreaChart::polarAreasListLength(QQmlListProperty<PolarArea> *polarAreasList)
{
    PolarAreaChart *chart = qobject_cast<PolarAreaChart *>(polarAreasList->object);
    if(chart)
        return chart->polarAreasList.length();
    else return 0;
}

PolarArea *PolarAreaChart::polarAreaAt(QQmlListProperty<PolarArea> *polarAreasList, int index)
{
    PolarAreaChart *chart = qobject_cast<PolarAreaChart *>(polarAreasList->object);
    if(chart)
        return chart->polarAreasList.at(index);
    else return 0;
}

void PolarAreaChart::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);

        //Обчислення допоміжних даних
        QRectF fillRect {boundingRect()};
        QPointF center {fillRect.center()};
        double maxRadius { qMin(fillRect.width(), fillRect.height())*0.5 };
        maxRadius -= qMax(0.5*pAxis.gridLines()->width(), 0.5*pAxis.labelsFont()->getHeight());
        if(pAxis.drawLabelsBackground())
            maxRadius -= 0.5*pAxis.labelsFont()->getHeight();

        double maxSteps { qFloor(maxRadius/(pAxis.labelsFont()->getHeight()*0.66)) };
        double minSteps { qFloor(maxRadius/pAxis.labelsFont()->getHeight()*0.5) };

        int numberOfSteps;
        double stepValue, graphMin;
        calculateScale(maxRadius, maxSteps, minSteps, upperValue, loverValue, numberOfSteps, stepValue, graphMin);
        pAxis.setLabels(populateLabels(numberOfSteps+1, graphMin, stepValue));
        double scaleHop { maxRadius/numberOfSteps };

        //Малювання сегментів
        painter->setPen(pStrokePen->getPen());
        double beginAngle {pAngleOffset+1440};
        double angleStep {360*16/polarAreasList.length()};
        double segmentRadius;

        for(PolarArea *i: polarAreasList){
            painter->setBrush(QColor(i->color()));
            segmentRadius = calculateOffset(i->value(), numberOfSteps, stepValue, graphMin, scaleHop);
            painter->drawPie(QRect(center.x()-segmentRadius, center.y()-segmentRadius, 2*segmentRadius, 2*segmentRadius),
                                             beginAngle, angleStep);
            beginAngle += angleStep;
        }

        //Малювання сітки
        painter->setPen(pAxis.gridLines()->getPen());
        double radius;
        for(int i=1;i<pAxis.labels().length();++i){
            radius = scaleHop*i;
            painter->drawArc(center.x()-radius, center.y()-radius, radius*2.0, radius*2.0, 0, 5760);
        }

        //Малювання міток
        painter->setFont(pAxis.labelsFont()->getFont());
        painter->setBrush(QBrush(pAxis.labelsBackgroundColor()));
        QRectF labelRect {QRectF(0,0,0,0)};
        for(QString i:pAxis.labels()){
            QRectF currentLabelRect = painter->fontMetrics().boundingRect(i);
            if(currentLabelRect.width()>labelRect.width())
                labelRect = currentLabelRect;
        }
        double labelsPadding {labelRect.height()*0.25};
        labelRect.adjust(-labelsPadding, 0, labelsPadding, 0);
        for(int i=1;i<pAxis.labels().length();++i){
            radius = scaleHop*i;
            labelRect.moveCenter(QPointF(center.x(), center.y()-radius));
            painter->setPen(QColor(pAxis.labelsBackgroundColor()));
            painter->drawRoundRect(labelRect, pAxis.labelsFont()->getHeight(), pAxis.labelsFont()->getHeight());
            painter->setPen(QColor(pAxis.labelsColor()));
            painter->drawText(labelRect, Qt::AlignCenter, pAxis.labels().at(i));
        }


}

void PolarAreaChart::calculateDataRange()
{
    upperValue = std::numeric_limits<int>::min();
    loverValue = std::numeric_limits<int>::max();

    for(PolarArea *i: polarAreasList){
        if(i->value()>upperValue)
            upperValue = i->value();
        if(i->value()<loverValue)
            loverValue = i->value();
    }
    double offset {(upperValue-loverValue)*0.2};
    upperValue += offset;
    loverValue -= offset;
}

