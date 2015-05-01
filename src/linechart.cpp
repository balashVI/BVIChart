#include "linechart.h"

LineChart::LineChart(QQuickPaintedItem *parent) : BarChart(parent)
{

}

LineChart::~LineChart()
{

}

QQmlListProperty<LineSeries> LineChart::series()
{
    return QQmlListProperty<LineSeries>(this, 0, &LineChart::appendSeries, &LineChart::seriesListLength,
                                        &LineChart::seriesAt, 0);
}

void LineChart::appendSeries(QQmlListProperty<LineSeries> *seriesList, LineSeries *series)
{
    LineChart *chart = qobject_cast<LineChart *>(seriesList->object);
    if (chart) {
        series->setParent(chart);
        chart->seriesList.append(series);
        connect(series, SIGNAL(dataChanged()), chart, SLOT(calculateDataRange()));
        chart->calculateDataRange();
        emit chart->seriesChanged();
    }
}

int LineChart::seriesListLength(QQmlListProperty<LineSeries> *seriesList)
{
    LineChart *chart = qobject_cast<LineChart *>(seriesList->object);
    if(chart)
        return chart->seriesList.length();
    else return 0;
}

LineSeries *LineChart::seriesAt(QQmlListProperty<LineSeries> *seriesList, int index)
{
    LineChart *chart = qobject_cast<LineChart *>(seriesList->object);
    if(chart)
        return chart->seriesList.at(index);
    return nullptr;
}

void LineChart::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    //Обчислення додаткових параметрів
    double xAxisLabelsHeight = pXAxis.labelsFont()->getHeight();
    int labelsWidth{pXAxis.getWidthOfLongestLabel()};
    int maxSize {boundingRect().height()};
    maxSize -= xAxisLabelsHeight;
    maxSize -= 5;
    maxSize -= xAxisLabelsHeight;

    int scaleHeight{maxSize};

    double maxSteps = qFloor(scaleHeight/(pYAxis.labelsFont()->getHeight()*0.66));
    double minSteps = qFloor(scaleHeight/pYAxis.labelsFont()->getHeight()*0.5);

    int numberOfSteps;
    double stepValue, graphMin;
    calculateScale(scaleHeight, maxSteps, minSteps, upperValue, loverValue, numberOfSteps, stepValue, graphMin);
    pYAxis.setLabels(populateLabels(numberOfSteps, graphMin, stepValue));

    int longestText = 1;
    if(pXAxis.labelsVisible()){
        QFontMetrics fm = QFontMetrics(pYAxis.labelsFont()->getFont());
        for(int i=0;i<pYAxis.labels().length();++i){
            int labelWidth = fm.width(pYAxis.labels()[i]);
            if(labelWidth > longestText)
                longestText = labelWidth;
        }
        longestText += 10;
    }

    double xAxisLength {boundingRect().width()-longestText-pXAxis.getWidthOfLongestLabel()};
    double valueHop = qFloor(xAxisLength/(pXAxis.labels().length()-1));
    double barWidth {(valueHop-pXAxis.axisLine()->width()*2 -
                pXAxis.barValueSpacing()*2 - pXAxis.barDatasetSpacing()*(seriesList.length()-1)) /
                seriesList.length()};
    double yAxisPosX {boundingRect().width()-pXAxis.getWidthOfLongestLabel()/2.0-xAxisLength};
    double xAxisPosY {scaleHeight + xAxisLabelsHeight};
    double scaleHop {qFloor(scaleHeight/pYAxis.labels().length())};

    //--------------------Малювання осей та сітки-------------------------------

    //Малювання осі Х
    painter->setPen(pXAxis.axisLine()->getPen());
    painter->drawLine(boundingRect().width()-pXAxis.getWidthOfLongestLabel()/2+5,xAxisPosY,
                      boundingRect().width()-pXAxis.getWidthOfLongestLabel()/2-xAxisLength-5,
                      xAxisPosY);
    painter->setFont(pXAxis.labelsFont()->getFont());
    for(int i=0;i<pXAxis.labels().length();i++){
        painter->drawText(yAxisPosX+i*valueHop-valueHop/2.0, xAxisPosY, valueHop,
                          xAxisLabelsHeight, Qt::AlignCenter, pXAxis.labels()[i]);
    }
    painter->setPen(pXAxis.gridLines()->getPen());
    for(int i=0;i<pXAxis.labels().length();i++){
        painter->drawLine(yAxisPosX+(1+i)*valueHop, xAxisPosY+3, yAxisPosX+(1+i)*valueHop,5);
    }

    //Малювання осі У
    painter->setPen(pYAxis.axisLine()->getPen());
    painter->drawLine(yAxisPosX, xAxisPosY+5, yAxisPosX, 5);
    painter->setPen(pYAxis.gridLines()->getPen());
    for(int i=0;i<pYAxis.labels().length();++i){
        painter->drawLine(yAxisPosX-3,xAxisPosY-(i+1)*scaleHop, yAxisPosX+xAxisLength+5,
                          xAxisPosY-(i+1)*scaleHop);
    }
    painter->setFont(pYAxis.labelsFont()->getFont());
    for(int i=0;i<pYAxis.labels().length();++i){
        painter->drawText(yAxisPosX-5-longestText, xAxisPosY-(i+1)*scaleHop+pYAxis.labelsFont()->getHeight()/2,
                          longestText, pYAxis.labelsFont()->getHeight(), Qt::AlignRight, pYAxis.labels()[i]);
    }

    //---------------------------------------Малювання графіка------------------------------------

    for(int i=0;i<seriesList.length();++i){
        painter->setPen(seriesList[i]->strokePen()->getPen());
        painter->setBrush(QBrush(seriesList[i]->color()));
        QPoint points[seriesList[i]->data().length()];
        QPolygon poligon;
        for(int j=0;j<seriesList[i]->data().length();++j){
            if(j>pXAxis.labels().length())
                break;
            double valueOffset {calculateOffset(seriesList[i]->data()[j],
                                                numberOfSteps, stepValue, graphMin, scaleHop)};
            points[j].setX(yAxisPosX+valueHop*j);
            points[j].setY(xAxisPosY-valueOffset);
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

void LineChart::calculateDataRange()
{
    upperValue = std::numeric_limits<int>::min();
    loverValue = std::numeric_limits<int>::max();

    for(LineSeries *i: seriesList){
        for(double j: i->data()){
            if(j>upperValue)
                upperValue = j;
            if(j<loverValue)
                loverValue = j;
        }
    }
    double offset {(upperValue-loverValue)*0.01};
    upperValue += offset;
    loverValue -= offset;
}

