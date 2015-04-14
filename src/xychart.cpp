#include "xychart.h"
#include "chartpoint.h"

XYChart::XYChart(QQuickPaintedItem *parent):
    BarChart(parent), pXAxis{this}
{

}

XYChart::~XYChart()
{

}

QQmlListProperty<XYSeries> XYChart::series()
{
    return QQmlListProperty<XYSeries>(this, 0, &XYChart::appendSeries, &XYChart::seriesListLength,
                                      &XYChart::seriesAt, 0);
}

void XYChart::appendSeries(QQmlListProperty<XYSeries> *seriesList, XYSeries *series)
{
    XYChart *chart = qobject_cast<XYChart *>(seriesList->object);
    if (chart) {
        series->setParent(chart);
        chart->seriesList.append(series);
        connect(series, SIGNAL(dataChanged()), chart, SLOT(calculateDataRange()));
        chart->calculateDataRange();
        emit chart->seriesChanged();
    }
}

int XYChart::seriesListLength(QQmlListProperty<XYSeries> *seriesList)
{
    XYChart *chart = qobject_cast<XYChart *>(seriesList->object);
    if(chart)
        return chart->seriesList.length();
    else return 0;
}

XYSeries *XYChart::seriesAt(QQmlListProperty<XYSeries> *seriesList, int index)
{
    XYChart *series = qobject_cast<XYChart *>(seriesList->object);
    if (series) {
        return series->seriesList.at(index);
    } else return nullptr;
}

void XYChart::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    //Обчислення додаткових параметрів
    double xAxisLabelsHeight = pXAxis.labelsFont()->getHeight();
    //    int labelsWidth{pXAxis.getWidthOfMaxLabel()};

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

    for(int i=0;i<seriesList.length();++i){
        painter->setPen(seriesList[i]->strokePen()->getPen());
        painter->setBrush(QBrush(seriesList[i]->color()));
        QPoint points[seriesList[i]->getDataList()->length()];
        QPolygon poligon;
        for(int j=0;j<seriesList[i]->getDataList()->length();++j){
            if(j>pXAxis.labels().length())
                break;
            double xValueOffset {calculateOffset(seriesList[i]->getDataList()->at(j)->x(),
                                                xNumberOfSteps, xStepValue, xGraphMin, xScaleHop)};
            double yValueOffset {calculateOffset(seriesList[i]->getDataList()->at(j)->y(),
                                                yNumberOfSteps, yStepValue, yGraphMin, yScaleHop)};
            points[j].setX(yAxisPosX+xValueOffset);
            points[j].setY(xAxisPosY-yValueOffset);
            poligon << points[j];
        }
        painter->drawPolyline(poligon);

        if(seriesList.at(i)->drawPoints()){
            int padding {seriesList.at(i)->strokePen()->width()*2};
            painter->setPen(QColor("#00000000"));
            painter->setBrush(seriesList.at(i)->color());
            for(QPoint& point: points)
                painter->drawPie(point.x()-padding, point.y()-padding, padding*2, padding*2, 0, 5760);

            padding = seriesList.at(i)->strokePen()->width();
            painter->setBrush(seriesList.at(i)->strokePen()->color());
            for(QPoint& point: points)
                painter->drawPie(point.x()-padding, point.y()-padding, padding*2, padding*2, 0, 5760);
        }
    }
}

void XYChart::calculateDataRange()
{
    xUpperValue = std::numeric_limits<int>::min();
    xLoverValue = std::numeric_limits<int>::max();
    yUpperValue = std::numeric_limits<int>::min();
    yLoverValue = std::numeric_limits<int>::max();

    double xUpper, xLover, yUpper, yLover;
    for(XYSeries *i: seriesList){
        i->getDataRange(xLover, xUpper, yLover, yUpper);
        if(xUpper>xUpperValue)
            xUpperValue = xUpper;
        if(xLover<xLoverValue)
            xLoverValue = xLover;
        if(yUpper>yUpperValue)
            yUpperValue = yUpper;
        if(yLover<yLoverValue)
            yLoverValue = yLover;
    }

    double offset {(xUpperValue-xLoverValue)*0.01};
    xUpperValue += offset;
    xLoverValue -= offset;
    offset = (yUpperValue-yLoverValue)*0.01;
    yUpperValue += offset;
    yLoverValue -= offset;
}

