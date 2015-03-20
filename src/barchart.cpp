#include "barchart.h"
#include <QFontMetrics>

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
    QPen pen(QColor("red"), 2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);

    drawAxes(painter);
}

void BarChart::prepare()
{
    int labelsWidth{pXAxis.getWidthOfMaxLabel()};
    int maxSize =  boundingRect().height();
    if(boundingRect().width()/pXAxis.labels().length()<labelsWidth){
        rotateLabels = 45.0*M_PI/180.0;
        if(boundingRect().width()/pXAxis.labels().length()<qCos(rotateLabels)*labelsWidth){
            rotateLabels = 90.0*M_PI/180.0;
            maxSize -= labelsWidth;
        } else {
            maxSize -= qSin(rotateLabels)*labelsWidth;
        }
    } else {
        maxSize -= QFontMetrics(pXAxis.labelsFont()->getFont()).height();
    }

    maxSize -= 5;

    maxSize -= QFontMetrics(pXAxis.labelsFont()->getFont()).height();

    int scaleHeight{maxSize};

    double maxSteps = qFloor(scaleHeight/(QFontMetrics(pYAxis.labelsFont()->getFont()).height()*0.66));
    double minSteps = qFloor(scaleHeight/QFontMetrics(pYAxis.labelsFont()->getFont()).height()*0.5);


}

void BarChart::drawAxes(QPainter *painter)
{
    painter->setPen(pXAxis.axisLine()->getPen());
    painter->drawLine(boundingRect().width()-pXAxis.getWidthOfMaxLabel()/2+5,50,100,100);
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
