#include "polarareachartcanvas.h"
#include <limits>

PolarAreaChartCanvas::PolarAreaChartCanvas(QQuickItem *parent) :
    PieChartCanvas(parent), pAxis{new ChartAxis(this)}, pAxisAboveChart{true}
{
    pAxis->setOrientation(ChartAxis::AxisOrientation::Vertical);
    pAxis->setVisibleLabelBackground(true);
    connect(pAxis, SIGNAL(changed()), this, SLOT(update()));
}

bool PolarAreaChartCanvas::axisAboveChart() const
{
    return pAxisAboveChart;
}

void PolarAreaChartCanvas::setAxisAboveChart(bool value)
{
    pAxisAboveChart = value;
    emit axisAboveChartChanged();
    update();
}

ChartAxis *PolarAreaChartCanvas::axis() const
{
    return pAxis;
}

void PolarAreaChartCanvas::paint(QPainter *painter)
{
    if(!pPausePainting){
        painter->setRenderHints(QPainter::Antialiasing, true);

        //Обчислення допоміжних даних
        QRectF fillRect {contentsBoundingRect()};
        QPointF center {fillRect.center()};
        int maxRadius = (fillRect.width()<fillRect.height())?fillRect.width()/2:fillRect.height()*0.5;
        maxRadius-=padding();

        pAxis->setLength(maxRadius);

        //Змінні для вспливаючих підказок
        int phi = 0;
        QString popupTxt;
        int popupRadius{};

        if(!pAxisAboveChart)
            drawAxis(painter, center);

        if(numberOfEnabledSlices){
            //Малювання сегментів
            if(pStrokeVisible){
                QPen pen(pStrokeColor);
                pen.setWidth(pStrokeWidth);
                painter->setPen(pen);
            } else
                painter->setPen(QPen(QColor(0,0,0,0)));

            int beginAngle{pAngleOffset+1440};
            int angleStep = 360*16/numberOfEnabledSlices;
            int counter{-1};
            int segmentRadius;
            for (PieSlice *i: mSlices) {
                ++counter;
                if(i->enabled()){
                    segmentRadius = pAxis->convertValue(i->value());
                    if(counter == pCurrentSlice){
                        painter->setBrush(QBrush(i->highlightColor()));
                        if(pPopup->enabled()){
                            phi = ((int)(beginAngle + angleStep/2)%5760)/16;
                            popupTxt = i->label()+": "+QString::number(i->value());
                            popupRadius = 0.5*segmentRadius;
                        }

                    } else
                        painter->setBrush(QBrush(i->color()));

                    painter->drawPie(QRect(center.x()-segmentRadius, center.y()-segmentRadius, 2*segmentRadius, 2*segmentRadius),
                                     beginAngle, angleStep);
                    beginAngle += angleStep;
                }
            }
        }

        if(pAxisAboveChart)
            drawAxis(painter, center);

        //Малювання вспливаючої підказки
        if(pPopup->enabled() && pCurrentSlice!=-1){
            painter->setFont(pPopup->font());
            QRectF popupTextRect{painter->fontMetrics().boundingRect(popupTxt)};
            popupTextRect += QMargins(pPopup->padding(), pPopup->padding(), pPopup->padding(), pPopup->padding());
            QPointF popupPoint {QPointF(center.x()+popupRadius*qCos(phi*pi/180.0), center.y()-popupRadius*qSin(phi*pi/180.0))};
            popupTextRect.moveCenter(QPointF(popupPoint.x(), popupPoint.y()-popupTextRect.height()/2-9));

            painter->setBrush(QBrush(pPopup->backgroundColor()));
            painter->setPen(QPen(QColor(0,0,0,0)));
            painter->drawRoundedRect(popupTextRect, 5, 5);
            QPainterPath triangle;
            triangle.moveTo(popupPoint);
            triangle.lineTo(popupPoint.x()-10, popupPoint.y()-9);
            triangle.lineTo(popupPoint.x()+10, popupPoint.y()-9);
            triangle.lineTo(popupPoint);
            painter->drawPath(triangle);
            painter->setPen(QPen(pPopup->textColor()));
            painter->drawText(popupTextRect, Qt::AlignHCenter | Qt::AlignVCenter, popupTxt);
        }
    }
}

void PolarAreaChartCanvas::hoverMoveEvent(QHoverEvent *event)
{
    QRectF rect {contentsBoundingRect()};
    QPointF center(rect.center());
    QPointF X {event->posF()};
    double a {qFabs(X.y()-center.y())};
    double b {qSqrt((X.x()-center.x())*(X.x()-center.x())+((X.y()-center.y())*(X.y()-center.y())))};
    double alpha {qAsin(a/b)*180.0/pi};
    if(X.x()>center.x()){
        if(X.y()>center.y())
            alpha = 360 - alpha;
    } else {
        if(X.y()>center.y())
            alpha += 180;
        else
            alpha = 180 - alpha;
    }
    alpha = (int)(alpha - pAngleOffset/16 - 90) % 360;
    if(alpha<0)
        alpha = 360+alpha;
    int current {qFloor(numberOfEnabledSlices*alpha/360)};
    int currentSliceRadius{0};

    for(int i=0, counter=-1;i<mSlices.length();++i){
        if(mSlices.at(i)->enabled())
            ++counter;
        if(counter==current){
            currentSliceRadius=pAxis->convertValue(mSlices.at(i)->value());
            current=i;
            break;
        }
    }
    if(b > currentSliceRadius){
        if(pCurrentSlice!=-1){
            setCurrentItem(-1);
            emit hoverSliceChanged();
        }
    } else{
        setCurrentItem(current);
        emit hoverSliceChanged();
    }
}

void PolarAreaChartCanvas::drawAxis(QPainter *painter, QPointF &center)
{

    painter->setPen(pAxis->getLinePen());
    int radiusSteap;
    int currentRadius;
    if(pAxis->visibleLines()){
        radiusSteap = pAxis->length()/pAxis->numberOfSteps();
        currentRadius = 0;

        for(int i=0;i<pAxis->numberOfSteps();++i){
            currentRadius+=radiusSteap;
            painter->drawArc(center.x()-currentRadius, center.y()-currentRadius, 2*currentRadius,
                             2*currentRadius, 0, 360*16);
        }
    }

    if(pAxis->visibleLabels()){
        radiusSteap = pAxis->length()/pAxis->numberOfSteps();
        currentRadius = 0;
        const QList<QString>& labels {pAxis->labels()};
        painter->setFont(pAxis->font());
        painter->setPen(pAxis->textColor());
        painter->setBrush(QBrush(pAxis->labelBackgroundColor()));
        for(int i=0;i<pAxis->numberOfSteps();++i){
            currentRadius+=radiusSteap;
            QRectF labelRect {painter->fontMetrics().boundingRect(labels.at(i))};
            labelRect.moveCenter(QPointF(center.x(), center.y()-currentRadius));
            labelRect += QMargins(pAxis->labelPadding(), pAxis->labelPadding(), pAxis->labelPadding(), pAxis->labelPadding());
            painter->setPen(QColor(255,255,255,0));
            painter->drawRoundedRect(labelRect, 3, 3);
            painter->setPen(pAxis->textColor());
            painter->drawText(labelRect, Qt::AlignHCenter | Qt::AlignVCenter, labels.at(i));
        }
    }
}

void PolarAreaChartCanvas::sliceChanged()
{
    numberOfEnabledSlices = 0;
    for(PieSlice *i: mSlices)
        if(i->enabled())
            ++numberOfEnabledSlices;

    if(numberOfEnabledSlices){
        maxDataValue = INT_MIN;
        minDataValue = INT_MAX;
        for(PieSlice *i: mSlices){
            if(i->enabled()){
            if(i->value() > maxDataValue)
                maxDataValue = i->value();
            if(i->value() < minDataValue)
                minDataValue = i->value();
            }
        }
    } else {
        maxDataValue = 10;
        minDataValue = 10;
    }
    if(minDataValue > 0)
        minDataValue=0;

    if(acceptHoverEvents()){
        if(pCurrentSlice != -1)
            setCurrentItem(-1);
    }
    pAxis->setMinMaxDataValues(minDataValue, maxDataValue);
    emit slicesChanged();
    update();
}
