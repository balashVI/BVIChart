#include "polarareachartcanvas.h"

PolarAreaChartCanvas::PolarAreaChartCanvas(QQuickItem *parent) :
    PieChartCanvas(parent), pAxis{new ChartAxis(this)}
{
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
        int labelHeight = 0;
        if(pAxis->visible()){
            painter->setFont(pAxis->font());
            if(pAxis->visibleLabels())
                labelHeight = painter->fontMetrics().height();
            if(pAxis->visibleLines()){
                if(labelHeight)
                    maxRadius -= (labelHeight>pAxis->lineWidth())?labelHeight/2:pAxis->lineWidth()*0.5;
                else
                    maxRadius -= pAxis->lineWidth()*0.5;
            } else
                maxRadius -= labelHeight*0.5;
        }

        int maxSteps = qFloor(maxRadius / (labelHeight*0.66));
        int minSteps = qFloor(maxRadius / labelHeight*0.5);


//        //Малювання сегментів
//        int beginAngle = pAngleOffset;
//        int segmentAngle;
//        int angleStep = pi*32/slices.length();
//        for (int i=0; i<slices.length(); ++i) {
//            if(!slices.at(i).enabled)
//                continue;
//            segmentAngle = (slices.at(i).value/sumSlicesValue) * 5760;
//            if(i == pCurrentSlice){
//                //Виділення активного сегмента
//                painter->setBrush(QBrush(slices.at(i).color.lighter(125)));
//                painter->drawPie(QRectF(fillRect.x()-7, fillRect.y()-7, fillRect.width()+14, fillRect.height()+14), beginAngle, segmentAngle);
//                painter->drawArc(fillRect, beginAngle, segmentAngle);

//                //Обчислення даних для вспливаючої підказки
//                if(pPopup->enabled()){
//                    phi = ((int)(beginAngle + segmentAngle/2)%5760)/16;
//                    popupTxt = slices.at(i).label+": "+QString::number(slices.at(i).value);
//                }

//            } else {
//                painter->setBrush(QBrush(slices.at(i).color));
//                painter->drawPie(fillRect, beginAngle, segmentAngle);
//            }
//            beginAngle += segmentAngle;
//        }




//        for (var i=0; i<data.length; i++) {

//            ctx.beginPath();
//            ctx.arc(width/2,height/2,scaleAnimation * calculateOffset(data[i].value,calculatedScale,scaleHop),startAngle, startAngle + rotateAnimation*angleStep, false);
//            ctx.lineTo(width/2,height/2);
//            ctx.closePath();
//            ctx.fillStyle = data[i].color;
//            ctx.fill();

//            if(config.segmentShowStroke) {
//                ctx.strokeStyle = config.segmentStrokeColor;
//                ctx.lineWidth = config.segmentStrokeWidth;
//                ctx.stroke();
//            }
//            startAngle += rotateAnimation*angleStep;
//        }
    }
}

void PolarAreaChartCanvas::hoverMoveEvent(QHoverEvent *event)
{

}

void PolarAreaChartCanvas::paintAxis(QPainter *painter, QPointF &center, int maxRadius)
{

}

void PolarAreaChartCanvas::sliceChanged()
{
    if(slices.length()){
        maxDataValue = slices.at(0).value;
        minDataValue = maxDataValue;
        for(auto &i:slices){
            if(i.value > maxDataValue)
                maxDataValue = i.value;
            if(i.value < minDataValue)
                minDataValue = i.value;
        }
    } else {
        maxDataValue = 10;
        minDataValue = 10;
    }

    numberOfEnabledSlices = 0;
    for(auto &i: slices)
        if(i.enabled)
            ++numberOfEnabledSlices;

    if(acceptHoverEvents()){
        if(pCurrentSlice != -1)
            setCurrentItem(-1);
    }

    update();
}
