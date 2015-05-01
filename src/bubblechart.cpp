#include "bubblechart.h"

BubbleChart::BubbleChart(QQuickPaintedItem *parent):
    XYChart(parent), pMinBubbleRadius{2}, pMaxBubbleRadius{20}
{

}

BubbleChart::~BubbleChart()
{

}

QQmlListProperty<BubbleSeries> BubbleChart::series()
{
    return QQmlListProperty<BubbleSeries>(this, 0, &BubbleChart::appendSeries, &BubbleChart::seriesListLength,
                                          &BubbleChart::seriesAt, 0);
}

int BubbleChart::maxBubbleRadius() const
{
    return pMaxBubbleRadius;
}

void BubbleChart::setMaxBubbleRadius(int value)
{
    pMaxBubbleRadius = value;
    emit maxBubbleRadiusChanged();
}

int BubbleChart::minBubbleRadius() const
{
    return pMinBubbleRadius;
}

void BubbleChart::setMinBubbleRadius(int value)
{
    pMinBubbleRadius = value;
    emit minBubbleRadiusChanged();
}

QVariantList BubbleChart::generateLegend()
{
    QVariantList list;
    QVariantMap map;
    for(BubbleSeries *series: seriesList){
        map.clear();
        map.insert("name", series->name());
        map.insert("color", series->color());
        map.insert("strokeColor", series->strokePen()->color());
        map.insert("strokeWidth", series->strokePen()->width());
        list.append(map);
    }
    return list;
}

void BubbleChart::appendSeries(QQmlListProperty<BubbleSeries> *seriesList, BubbleSeries *series)
{
    BubbleChart *chart = qobject_cast<BubbleChart *>(seriesList->object);
    if (chart) {
        series->setParent(chart);
        chart->seriesList.append(series);
        connect(series, SIGNAL(dataChanged()), chart, SLOT(calculateDataRange()));
        chart->calculateDataRange();
        emit chart->seriesChanged();
    }
}

int BubbleChart::seriesListLength(QQmlListProperty<BubbleSeries> *seriesList)
{
    BubbleChart *chart = qobject_cast<BubbleChart *>(seriesList->object);
    if(chart)
        return chart->seriesList.length();
    else return 0;
}

BubbleSeries *BubbleChart::seriesAt(QQmlListProperty<BubbleSeries> *seriesList, int index)
{
    BubbleChart *series = qobject_cast<BubbleChart *>(seriesList->object);
    if (series) {
        return series->seriesList.at(index);
    } else return nullptr;
}

void BubbleChart::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    //Обчислення додаткових параметрів
    double xAxisLabelsHeight = pXAxis.labelsFont()->getHeight();

    int scaleHeight{boundingRect().height()-5-2.0*xAxisLabelsHeight};
    double yMaxSteps = qFloor(scaleHeight/(pYAxis.labelsFont()->getHeight()*0.66));
    double yMinSteps = qFloor(scaleHeight/pYAxis.labelsFont()->getHeight()*0.5);
    int yNumberOfSteps;
    double yStepValue, yGraphMin;
    calculateScale(scaleHeight, yMaxSteps, yMinSteps, yUpperValue, yLoverValue, yNumberOfSteps, yStepValue, yGraphMin);
    pYAxis.setLabels(populateLabels(yNumberOfSteps, yGraphMin, yStepValue));

    int scaleWidth {boundingRect().width()-10-pYAxis.getWidthOfLongestLabel()};
    double xMaxSteps = qFloor(scaleWidth/(pXAxis.labelsFont()->getHeight()*0.66));
    double xMinSteps = qFloor(scaleWidth/pXAxis.labelsFont()->getHeight()*0.3);
    int xNumberOfSteps;
    double xStepValue, xGraphMin;

    calculateScale(scaleWidth, xMaxSteps, xMinSteps, xUpperValue, xLoverValue, xNumberOfSteps, xStepValue, xGraphMin);
    pXAxis.setLabels(populateLabels(xNumberOfSteps, xGraphMin, xStepValue));

    xMaxSteps = qFloor(scaleWidth/(pXAxis.getWidthOfLongestLabel()*0.66));
    xMinSteps = qFloor(scaleWidth/pXAxis.getWidthOfLongestLabel()*0.4);
    calculateScale(scaleWidth, xMaxSteps, xMinSteps, xUpperValue, xLoverValue, xNumberOfSteps, xStepValue, xGraphMin);
    pXAxis.setLabels(populateLabels(xNumberOfSteps, xGraphMin, xStepValue));

    double yAxisPosX {boundingRect().width()-scaleWidth};
    double xAxisPosY {scaleHeight + xAxisLabelsHeight};
    double yScaleHop {qFloor(scaleHeight/pYAxis.labels().length())};
    double xScaleHop {qFloor(scaleWidth/pXAxis.labels().length())};

    //    //--------------------Малювання осей та сітки-------------------------------

    //Малювання осі Х
    painter->setPen(pXAxis.axisLine()->getPen());
    painter->drawLine(boundingRect().width()+5,xAxisPosY,
                      boundingRect().width()-scaleWidth-5,
                      xAxisPosY);
    painter->setFont(pXAxis.labelsFont()->getFont());
    for(int i=0;i<pXAxis.labels().length();i++){
        painter->drawText(yAxisPosX+i*xScaleHop-xScaleHop/2.0, xAxisPosY, xScaleHop,
                          xAxisLabelsHeight, Qt::AlignCenter, pXAxis.labels()[i]);
    }
    painter->setPen(pXAxis.gridLines()->getPen());
    for(int i=0;i<pXAxis.labels().length();i++){
        painter->drawLine(yAxisPosX+(1+i)*xScaleHop, xAxisPosY+3, yAxisPosX+(1+i)*xScaleHop,5);
    }

    //Малювання осі У
    painter->setPen(pYAxis.axisLine()->getPen());
    painter->drawLine(yAxisPosX, xAxisPosY+5, yAxisPosX, 5);
    painter->setPen(pYAxis.gridLines()->getPen());
    for(int i=0;i<pYAxis.labels().length();++i){
        painter->drawLine(yAxisPosX-3,xAxisPosY-(i+1)*yScaleHop, yAxisPosX+scaleWidth+5,
                          xAxisPosY-(i+1)*yScaleHop);
    }
    painter->setFont(pYAxis.labelsFont()->getFont());
    for(int i=0;i<pYAxis.labels().length();++i){
        painter->drawText(yAxisPosX-5-scaleWidth/pXAxis.labels().length(), xAxisPosY-(i+1)*yScaleHop+pYAxis.labelsFont()->getHeight()/2,
                          scaleWidth/pXAxis.labels().length(), pYAxis.labelsFont()->getHeight(), Qt::AlignRight, pYAxis.labels()[i]);
    }

    //---------------------------------------Малювання графіка------------------------------------

    double valueScale {(pMaxBubbleRadius-pMinBubbleRadius)/(upperValue-loverValue)};
    double valueShift {pMinBubbleRadius-valueScale*loverValue};
    for(int i=0;i<seriesList.length();++i){
        painter->setPen(seriesList[i]->strokePen()->getPen());
        painter->setBrush(QBrush(seriesList[i]->color()));
        for(int j=0;j<seriesList[i]->getDataList()->length();++j){
            double xValueOffset {calculateOffset(seriesList[i]->getDataList()->at(j)->x(),
                                                xNumberOfSteps, xStepValue, xGraphMin, xScaleHop)};
            double yValueOffset {calculateOffset(seriesList[i]->getDataList()->at(j)->y(),
                                                yNumberOfSteps, yStepValue, yGraphMin, yScaleHop)};
            double bubbleRadius {valueScale*seriesList[i]->getDataList()->at(j)->value()+valueShift};
            painter->drawEllipse(QPoint(yAxisPosX+xValueOffset, xAxisPosY-yValueOffset),
                                 bubbleRadius, bubbleRadius);
        }
    }
}

void BubbleChart::calculateDataRange()
{
    xUpperValue = std::numeric_limits<int>::min();
    xLoverValue = std::numeric_limits<int>::max();
    yUpperValue = std::numeric_limits<int>::min();
    yLoverValue = std::numeric_limits<int>::max();
    upperValue = std::numeric_limits<int>::min();
    loverValue = std::numeric_limits<int>::max();

    double xUpper, xLover, yUpper, yLover, upper, lover;
    for(BubbleSeries *i: seriesList){
        i->getDataRange(xLover, xUpper, yLover, yUpper, lover, upper);
        if(xUpper>xUpperValue)
            xUpperValue = xUpper;
        if(xLover<xLoverValue)
            xLoverValue = xLover;
        if(yUpper>yUpperValue)
            yUpperValue = yUpper;
        if(yLover<yLoverValue)
            yLoverValue = yLover;
        if(upper>upperValue)
            upperValue = upper;
        if(lover<loverValue)
            loverValue = lover;
    }
    double offset {(xUpperValue-xLoverValue)*0.01};
    xUpperValue += offset;
    xLoverValue -= offset;
    offset = (yUpperValue-yLoverValue)*0.01;
    yUpperValue += offset;
    yLoverValue -= offset;
    if(upperValue == loverValue)
        loverValue -= 1;
}

