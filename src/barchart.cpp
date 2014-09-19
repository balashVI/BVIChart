#include "barchart.h"

BarChart::BarChart(QQuickItem *parent) :
    AbstractChart(parent)
{
}

QQmlListProperty<BarSeries> BarChart::series()
{
    return QQmlListProperty<BarSeries>(this, 0, &BarChart::appendSeries, &BarChart::seriesListLength,
                                       &BarChart::seriesAt, 0);
}

void BarChart::appendSeries(QQmlListProperty<BarSeries> *seriesList, BarSeries *series)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if (chart) {
        series->setParent(chart);
        chart->seriesList.append(series);
        chart->seriesChanged();
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
