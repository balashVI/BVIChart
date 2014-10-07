#include "barchart.h"

BarChart::BarChart(QQuickItem *parent) :
    AbstractChart(parent), pXAxis{this}
{
    connect(this, SIGNAL(seriesChanged()), &pLegend, SLOT(updateLegend()));
    pLegend.setSeriesList((QList<AbstractSeries*>*)(&seriesList));
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

void BarChart::appendSeries(QQmlListProperty<BarSeries> *seriesList, BarSeries *series)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if (chart) {
        series->setParentItem(chart);
        chart->seriesList.append(series);
        connect(series, SIGNAL(nameChanged()), &chart->pLegend, SLOT(updateLegend()));
        connect(series, SIGNAL(colorChanged()), &chart->pLegend, SLOT(updateLegend()));
        connect(series, SIGNAL(enabledChanged()), &chart->pLegend, SLOT(updateLegend()));
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

void BarChart::updateChildrenGeometry()
{
    pHeader.setPosition(QPoint((width()-pHeader.width())/2, pSpacing));
    //Визначення координат та розмірів ChartLegend
    switch (pLegend.location()) {
    case (ChartLegend::RightLocation):
        pLegend.recalculateSize(height()-3*pSpacing-pHeader.height());
        pLegend.setX(x()+width()-pSpacing-pLegend.width());
        pLegend.setY(pHeader.y()+pHeader.height()+pSpacing);

        pXAxis.setX(pSpacing);
        pXAxis.setY(pLegend.y());
        pXAxis.setSize(QSizeF(width()-pLegend.width()-3*pSpacing, height()-pHeader.height()-3*pSpacing));
        break;
    case(ChartLegend::LeftLocation):
        pLegend.recalculateSize(height()-3*pSpacing-pHeader.height());
        pLegend.setX(pSpacing);
        pLegend.setY(pHeader.y()+pHeader.height()+pSpacing);

        pXAxis.setX(pLegend.width()+2*pSpacing);
        pXAxis.setY(pLegend.y());
        pXAxis.setSize(QSizeF(width()-pLegend.width()-3*pSpacing, height()-pHeader.height()-3*pSpacing));
        break;
    case(ChartLegend::TopLocation):
        pLegend.recalculateSize(width()-2*pSpacing);
        pLegend.setX(pSpacing);
        pLegend.setY(pHeader.y()+pHeader.height()+pSpacing);

        pXAxis.setX(pSpacing);
        pXAxis.setY(pLegend.y()+pLegend.height()+pSpacing);
        pXAxis.setSize(QSizeF(width()-2*pSpacing, height()-pLegend.y()-pLegend.height()-2*pSpacing));
        break;
    case(ChartLegend::BottomLocation):
        pLegend.recalculateSize(width()-2*pSpacing);
        pLegend.setX(pSpacing);
        pLegend.setY(y()+height()-pSpacing-pLegend.height());

        pXAxis.setX(pSpacing);
        pXAxis.setY(pHeader.y()+pHeader.height()+pSpacing);
        pXAxis.setSize(QSizeF(width()-2*pSpacing, height()-pLegend.height()-pHeader.height()-4*pSpacing));
        break;
    default:
        pLegend.recalculateSize(0);
        break;
    }
}
