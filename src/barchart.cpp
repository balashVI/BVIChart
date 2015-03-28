#include "barchart.h"
#include <QFontMetrics>
#include <QPolygon>

BarChart::BarChart(QQuickPaintedItem *parent) :
    AbstractChart(parent), pXAxis{this}, pYAxis{this}
{
    pXAxis.setName("X");
}

QQmlListProperty<BarSeries> BarChart::series()
{
    return QQmlListProperty<BarSeries>(this, 0, &BarChart::appendSeries, &BarChart::seriesListLength,
                                       &BarChart::seriesAt, 0);
}

CategoryAxis *BarChart::xAxis()
{
    return &pXAxis;
}

StandartAxis *BarChart::yAxis()
{
    return &pYAxis;
}

void BarChart::appendSeries(QQmlListProperty<BarSeries> *seriesList, BarSeries *series)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if (chart) {
        series->setParent(chart);
        chart->seriesList.append(series);
        connect(series, SIGNAL(dataChanged()), chart, SLOT(calculateNumbersOfCategories()));
        connect(series, SIGNAL(dataChanged()), chart, SLOT(calculateDataRange()));
        chart->calculateNumbersOfCategories();
        chart->calculateDataRange();
        emit chart->seriesChanged();
    }
}

int BarChart::seriesListLength(QQmlListProperty<BarSeries> *seriesList)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if(chart)
        return chart->seriesList.length();
    else return 0;
}

BarSeries *BarChart::seriesAt(QQmlListProperty<BarSeries> *seriesList, int index)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if(chart)
        return chart->seriesList.at(index);
    return nullptr;
}

void BarChart::paint(QPainter *painter)
{
    //Обчислення додаткових параметрів
    double xAxisLabelsHeight = pXAxis.labelsFont()->getHeight();
    int labelsWidth{pXAxis.getWidthOfMaxLabel()};
    int maxSize {boundingRect().height()};
    double rotateLabels;
    if(boundingRect().width()/(pXAxis.labels().length()+1)<labelsWidth){
        rotateLabels = 45.0;
        if(boundingRect().width()/(pXAxis.labels().length()+1)<qCos(rotateLabels)*labelsWidth){
            rotateLabels = 90.0;
            maxSize -= labelsWidth;
        } else {
            maxSize -= qSin(rotateLabels)*labelsWidth;
        }
    } else {
        maxSize -= xAxisLabelsHeight;
    }
    qDebug() << boundingRect().width()/pXAxis.labels().length() << rotateLabels;
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

    double xAxisLength {boundingRect().width()-longestText-pXAxis.getWidthOfMaxLabel()};
    double valueHop = qFloor(xAxisLength/pXAxis.labels().length());
    double barWidth {(valueHop-pXAxis.axisLine()->width()*2 -
                pXAxis.barValueSpacing()*2 - pXAxis.barDatasetSpacing()*(seriesList.length()-1)) /
                seriesList.length()};
    double yAxisPosX {boundingRect().width()-pXAxis.getWidthOfMaxLabel()/2.0-xAxisLength};
    double xAxisPosY {scaleHeight + xAxisLabelsHeight};
    double scaleHop {qFloor(scaleHeight/pYAxis.labels().length())};

    //--------------------Малювання осей та сітки-------------------------------

    //Малювання осі Х
    painter->setPen(pXAxis.axisLine()->getPen());
    painter->drawLine(boundingRect().width()-pXAxis.getWidthOfMaxLabel()/2+5,xAxisPosY,
                      boundingRect().width()-pXAxis.getWidthOfMaxLabel()/2-xAxisLength-5,
                      xAxisPosY);
    painter->setFont(pXAxis.labelsFont()->getFont());
    for(int i=0;i<pXAxis.labels().length();i++){
        if(rotateLabels>0)
            drawRotatedText(painter, rotateLabels, yAxisPosX+i*valueHop, xAxisPosY+xAxisLabelsHeight, pXAxis.labels()[i]);
        else
            painter->drawText(yAxisPosX+i*valueHop, xAxisPosY, valueHop,
                              xAxisLabelsHeight, Qt::AlignCenter, pXAxis.labels()[i]);
    }
    painter->setPen(pXAxis.majorLines()->getPen());
    for(int i=0;i<pXAxis.labels().length();i++){
        painter->drawLine(yAxisPosX+(1+i)*valueHop, xAxisPosY+3, yAxisPosX+(1+i)*valueHop,5);
    }

    //Малювання осі У
    painter->setPen(pYAxis.axisLine()->getPen());
    painter->drawLine(yAxisPosX, xAxisPosY+5, yAxisPosX, 5);
    painter->setPen(pYAxis.majorLines()->getPen());
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
        for(int j=0;j<seriesList[i]->data().length();++j){
            if(j>pXAxis.labels().length())
                break;
            double barOffset {yAxisPosX+pXAxis.barValueSpacing()+valueHop*j+barWidth*i+
                        pXAxis.barDatasetSpacing()*i+pXAxis.axisLine()->width()};

            QPolygon poligon;
            poligon << QPoint(barOffset,xAxisPosY);
            double valueOffset {calculateOffset(seriesList[i]->data()[j],
                                                numberOfSteps, stepValue, graphMin, scaleHop)};
            poligon << QPoint(barOffset,xAxisPosY-valueOffset);
            poligon << QPoint(barOffset+barWidth,xAxisPosY-valueOffset);
            poligon << QPoint(barOffset+barWidth,xAxisPosY);
            painter->drawPolyline(poligon);
            painter->drawPolygon(poligon);
        }
    }
}

void BarChart::drawRotatedText(QPainter *painter, float degrees, int x, int y, const QString &text)
{
    painter->save();
    painter->translate(x, y);
    painter->rotate(degrees);
    painter->drawText(0, 0, text);
    painter->restore();
}

void BarChart::calculateDataRange()
{
    upperValue = std::numeric_limits<int>::min();
    loverValue = std::numeric_limits<int>::max();

    for(BarSeries *i: seriesList){
        for(double j: i->data()){
            if(j>upperValue)
                upperValue = j;
            if(j<loverValue)
                loverValue = j;
        }
    }
}

void BarChart::calculateNumbersOfCategories()
{
    int numberOfCategories{1};
    for(BarSeries* i: seriesList)
        if(numberOfCategories < i->data().length())
            numberOfCategories = i->data().length();
    pXAxis.setNumberOfCategories(numberOfCategories);
}
