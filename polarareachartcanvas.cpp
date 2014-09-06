#include "polarareachartcanvas.h"

PolarAreaChartCanvas::PolarAreaChartCanvas(QQuickItem *parent) :
    PieChartCanvas(parent), pAxis{new ChartAxis(this)}
{
    pAxis->setOrientation(ChartAxis::AxisOrientation::Vertical);
    pAxis->setVisibleLabelBackground(true);
    connect(pAxis, SIGNAL(changed()), this, SLOT(update()));
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
        QRectF fillRect = contentsBoundingRect();
        QPointF center = fillRect.center();
        int maxRadius = (fillRect.width()<fillRect.height())?fillRect.width()/2:fillRect.height()*0.5;
        maxRadius-=padding();
        if(pAxis->visible())
            maxRadius -= qMax(pAxis->visibleLines()*pAxis->lineWidth(), pAxis->visibleLabels()*pAxis->labelHeight())*0.5;

        pAxis->setLength(maxRadius);

        if(numberOfEnabledSlices){
            //Змінні для вспливаючих підказок
            int phi = 0;
            QString popupTxt;
            int popupRadius{};

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
            QRectF pieRect;
            int segmentRadius;
            for (auto &i: slices) {
                ++counter;
                if(!i.enabled)
                    continue;
                segmentRadius = i.value*maxRadius/maxDataValue;
                if(counter == pCurrentSlice){
                    painter->setBrush(QBrush(i.color.lighter(135)));
                    if(pPopup->enabled()){
                        phi = ((int)(beginAngle + angleStep/2)%5760)/16;
                        popupTxt = i.label+": "+QString::number(i.value);
                        popupRadius = 0.5*segmentRadius;
                    }

                } else
                    painter->setBrush(QBrush(i.color));

                painter->drawPie(QRect(center.x()-segmentRadius, center.y()-segmentRadius, 2*segmentRadius, 2*segmentRadius),
                                 beginAngle, angleStep);
                beginAngle += angleStep;
            }

            //Малювання вспливаючої підказки
            if(pPopup->enabled() && pCurrentSlice!=-1){
                int popupPadding = pPopup->padding();
                painter->setFont(pPopup->font());
                QRect popupTextRect = painter->fontMetrics().boundingRect(popupTxt);
                QPoint popupPoint;
                QPoint popupCenterBottomPoint;
                popupCenterBottomPoint.setX(center.x()+popupRadius*qCos(phi*pi/180.0));
                popupCenterBottomPoint.setY(center.y()-popupRadius*qSin(phi*pi/180.0));
                popupPoint.setX(popupCenterBottomPoint.x() - popupTextRect.width()*0.5-popupPadding);
                popupPoint.setY(popupCenterBottomPoint.y() - popupTextRect.height()-2*popupPadding-9);

                painter->setBrush(QBrush(pPopup->backgroundColor()));
                painter->setPen(QPen(QColor(0,0,0,0)));
                painter->drawRoundedRect(popupPoint.x(), popupPoint.y(), popupTextRect.width()+2*popupPadding,
                                         popupTextRect.height()+2*popupPadding, 5, 5);
                QPainterPath triangle;
                triangle.moveTo(popupCenterBottomPoint);
                triangle.lineTo(popupCenterBottomPoint.x()-10, popupCenterBottomPoint.y()-9);
                triangle.lineTo(popupCenterBottomPoint.x()+10, popupCenterBottomPoint.y()-9);
                triangle.lineTo(popupCenterBottomPoint);
                painter->drawPath(triangle);
                painter->setPen(QPen(pPopup->textColor()));
                painter->drawText(popupPoint.x()+popupPadding, popupPoint.y()+popupPadding-popupTextRect.y(), popupTxt);
            }
        }
        drawAxis(painter, center, maxRadius);
    }
}

void PolarAreaChartCanvas::hoverMoveEvent(QHoverEvent *event)
{

}

void PolarAreaChartCanvas::drawAxis(QPainter *painter, QPointF &center, int maxRadius)
{
    painter->setPen(pAxis->getLinePen());
    if(pAxis->visibleLines()){
        int radiusSteap = maxRadius/pAxis->numberOfSteps();
        int currentRadius=0;
        for(int i=0;i<pAxis->numberOfSteps();++i){
            currentRadius+=radiusSteap;
            painter->drawArc(center.x()-currentRadius, center.y()-currentRadius, 2*currentRadius,
                             2*currentRadius, 0, 360*16);
        }
    }

    if(pAxis->visibleLabels()){
        int radiusSteap = maxRadius/pAxis->numberOfSteps();
        int currentRadius=0;
        const QList<QString>& labels = pAxis->labels();

        painter->setFont(pAxis->font());
        painter->setPen(pAxis->textColor());
        painter->setBrush(QBrush(pAxis->labelBackgroundColor()));
        for(int i=0;i<pAxis->numberOfSteps();++i){
            currentRadius+=radiusSteap;
            QRectF labelRect = painter->fontMetrics().boundingRect(labels.at(i));
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
    for(auto &i: slices)
        if(i.enabled)
            ++numberOfEnabledSlices;

    if(numberOfEnabledSlices){
        maxDataValue = slices.at(0).value;
        minDataValue = maxDataValue;
        for(auto &i:slices){
            if(!i.enabled)
                continue;
            if(i.value > maxDataValue)
                maxDataValue = i.value;
            if(i.value < minDataValue)
                minDataValue = i.value;
        }
    } else {
        maxDataValue = 10;
        minDataValue = 10;
    }

    if(acceptHoverEvents()){
        if(pCurrentSlice != -1)
            setCurrentItem(-1);
    }
    pAxis->setMinMaxValues(minDataValue, maxDataValue);
    update();
}
